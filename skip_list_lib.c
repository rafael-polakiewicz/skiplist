#include "skip_list_lib.h"

node * node_init(char *word, char * meaning, int level) {
    node *new_node = malloc(sizeof(node));

    strcpy(new_node->word, word);
    strcpy(new_node->meaning, meaning);
    new_node->forward = (node **) calloc(level + 1, sizeof(node *));

    return new_node;
}

skiplist *skiplist_init() {
    int i;
    skiplist *list = malloc(sizeof(list));
    
    list->header = node_init(SMALLEST_WORD, SKIP_LIST_HEADER_MEANING, SKIPLIST_MAX_LEVEL);
    list->level = 0;
    
    return list;
}

int rand_level() {
    int level = 0;

    while (rand() < RAND_MAX / 2 && level < SKIPLIST_MAX_LEVEL)
        level++;

    return level;
}

int skiplist_insert(skiplist *list, char *word, char *meaning) {
    node *update[SKIPLIST_MAX_LEVEL + 1];
    node *current = list->header;
    int i, level;

    for (i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && 
                strcmp(current->forward[i]->word, word) < 0)
            current = current->forward[i];
        update[i] = current;
    }
    current = current->forward[0];

    if(current == NULL || strcmp(current->word, word) != 0) {
        level = rand_level();
        
        if (level > list->level) {
            for (i = level; i > list->level; i--) {
                update[i] = list->header;
            }
            list->level = level;
        }

        current = node_init(word, meaning, level);

        for (i = 0; i <= level; i++) {
            current->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = current;
        }
        return 1;
    }

    return 0;
}

int skiplist_word_meaning_change(skiplist *list, char * word, char * meaning) {
    node *result_of_search = skiplist_search_by_word(list, word);

    if(result_of_search != NULL) {
        strcpy(result_of_search->meaning, meaning);
        return 1;
    }
    else return 0;
}

node *skiplist_search_by_word(skiplist *list, char *word) {
    node *current = list->header;
    int i;

    for (i = list->level; i >= 0; i--) {
        while(current->forward[i] != NULL && strcmp(current->forward[i]->word, word) < 0)
            current = current->forward[i];
    }
    
    if(current->forward[0] != NULL && strcmp(current->forward[0]->word, word) == 0)
        return current->forward[0];
    else return NULL;
}

int skiplist_search_by_letter(skiplist *list, char initial_letter) {
    node *current = list->header;
    int i;

    for (i = list->level; i >= 0; i--) {
        while(current->forward[i] != NULL && current->forward[i]->word[0] < initial_letter)
            current = current->forward[i];
    }

    current = current->forward[0];

    if(current == NULL || current->word[0] != initial_letter) return 0;
    else {
        while(current != NULL && current->word[0] == initial_letter) {
            printf("%s %s\n", current->word, current->meaning);
            current = current->forward[0];
        }
        return 1;
    }
}

void skiplist_node_free(node *list_node) {
    if (list_node) {
        free(list_node->forward);
        free(list_node);
    }
}

int skiplist_delete_by_word(skiplist *list, char *word) {
    int i;
    node *update[SKIPLIST_MAX_LEVEL + 1];
    node *current = list->header;

    for(i = list->level; i >= 0; --i) {
        while(current->forward[i] != NULL && strcmp(current->forward[i]->word, word) < 0) 
            current = current->forward[i];
        update[i] = current;
    }
    current = current->forward[0];


    if (current != NULL && strcmp(current->word, word) == 0) {
        for (i = list->level; i >= 0; i--) {
            // caso o proximo valor do item anterior nao precisa atualizar.
            if(update[i]->forward[i] != current) continue;

            update[i]->forward[i] = current->forward[i];
        }

        skiplist_node_free(current);
        
        // Limpando levels que nao tem nenhum elemento
        while(list->level>0 && list->header->forward[list->level] == NULL) 
            list->level--; 

        return 1;
    }
    else return 0;
}

void skiplist_free(skiplist **list) {
    node *current = (*list)->header->forward[0];
    node *aux;
    
    while (current != NULL) {
        aux = current;
        current = current->forward[0];
        skiplist_delete_by_word(*list, aux->word);
        
    }

    free((*list)->header);
    free(*list);
}