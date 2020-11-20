#include "skip_list_lib.h"

skiplist *skiplist_init() {
    int i;
    skiplist *list = malloc(sizeof(list));
    node *header = (node *) malloc(sizeof(struct node));

    list->header = header;
    /*
    =======================================================*/
    header->key = 12367; 
    // posso deletar???
    /*
    =======================================================*/
    header->forward = (node **) malloc(sizeof(node*) * (SKIPLIST_MAX_LEVEL));
    
    for (i = 0; i < SKIPLIST_MAX_LEVEL; i++) {
        header->forward[i] = list->header;
    }
    
    list->level = 0;
    list->size = 0;
    
    return list;
}

int rand_level() {
    int level = 0;

    while (rand() < RAND_MAX / 2 && level < SKIPLIST_MAX_LEVEL)
        level++;

    return level;
}

int skiplist_insert(skiplist *list, int key, char* word) {
    node *update[SKIPLIST_MAX_LEVEL];
    node *aux = list->header;
    int i, level;

    for (i = list->level; i >= 0; i--) {
        while (aux->word != NULL && strcmp(aux->word, word) < 0)
            aux = aux->forward[i];
        update[i] = aux;
    }
    aux = aux->forward[0];

    if (aux->word != NULL && strcmp(aux->word, word) == 0) {
        aux->word = word;
        return 0;
    } 
    else {
        level = rand_level();

        if (level > list->level) {
            for (i = level; i > list->level; i--) {
                update[i] = list->header;
            }
            list->level = level;
        }
        aux = (node *) malloc(sizeof(node));
        aux->forward = (node **) calloc(level, sizeof(node*));

        aux->key = key;
        aux->word = word;
        
        for (i = 0; i <= level; i++) {
            aux->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = aux;
        }
    }

    return 0;
}

node *skiplist_search(skiplist *list, char *word) {
    node *aux = list->header;
    int i;

    for (i = list->level; i >= 0; i--) {
        // while (aux->forward[i]->key < key)
        while(strcmp(aux->word, word) < 0)
            aux = aux->forward[i];
    }

    return aux;
}

void skiplist_node_free(node *list_node) {
    if (list_node) {
        free(list_node->forward);
        free(list_node);
    }
}

int skiplist_delete(skiplist *list, char *word) {
    int i;
    node *update[SKIPLIST_MAX_LEVEL];
    node *aux;

    aux = skiplist_search(list, word);

    if (strcmp(word, aux->word) == 0) {
        for (i = 0; i < list->level; i++) {
            if (update[i]->forward[i] != aux)
                break;
            update[i]->forward[0] = aux->forward[0];
        }
        skiplist_node_free(aux);

        while (list->level > 0 && 
               list->header->forward[list->level] == list->header)
            list->level--;
    
        return 0;
    }
    
    return 1;
}

void skiplist_dump(skiplist *list) {
    node *aux = list->header;

    while (aux && aux->forward[0] != list->header) {
        printf("%d[%s]->", aux->forward[0]->key, aux->forward[0]->word);
        aux = aux->forward[0];
    }
    printf("NIL\n");
}