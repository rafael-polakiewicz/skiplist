#include "skip_list_lib.h"

node * node_init(char *word, int level) {
    node *new_node = malloc(sizeof(node));

    new_node->word = word;
    new_node->forward = (node **) malloc(sizeof(node *) * level + 1);
    memset(new_node->forward, 0, sizeof(node *) * (level+1));

    return new_node;
}

skiplist *skiplist_init() {
    int i;
    skiplist *list = malloc(sizeof(list));
    
    list->header = node_init(SMALLEST_WORD, SKIPLIST_MAX_LEVEL);
    
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
    node *update[SKIPLIST_MAX_LEVEL + 1];
    node *current = list->header;
    int i, level;

    memset(update, 0, sizeof(node*)*SKIPLIST_MAX_LEVEL+1);

    for (i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && strcmp(current->forward[i]->word, word) < 0)
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

        current = node_init(word, level);

        for (i = 0; i <= level; i++) {
            current->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = current;
        }
    }

    return 0;
}

node *skiplist_search(skiplist *list, char *word) {
    node *current = list->header->forward[list->level];
    int i;

    for (i = list->level; i >= 0; i--) {
        while(current != NULL && strcmp(current->word, word) < 0)
            current = current->forward[i];
    }

    return current;
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
    node *current;

    current = skiplist_search(list, word);

    if (current->word != NULL && strcmp(word, current->word) == 0) {
        for (i = 0; i < list->level; i++) {
            if (update[i]->forward[i] != current)
                break;
            update[i]->forward[0] = current->forward[0];
        }
        skiplist_node_free(current);

        while (list->level > 0 && 
               list->header->forward[list->level] == list->header)
            list->level--;
    
        return 0;
    }
    
    return 1;
}

void skiplist_dump(skiplist *list) {
    node *current = list->header->forward[0];

    while (current != NULL) {
        printf("%d[%s]->", current->key, current->word);
        current = current->forward[0];
    }
    printf("NIL\n");
}