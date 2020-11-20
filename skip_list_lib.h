#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SMALLEST_WORD "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
#define SKIPLIST_MAX_LEVEL 6


struct node {
    int key;
    char *word;
    struct node **forward;
};

struct skiplist {
    int level;
    int size;
    struct node *header;
};

typedef struct node node;

typedef struct skiplist skiplist;


skiplist *skiplist_init();

int rand_level();

int skiplist_insert(skiplist *, int, char *);

node *skiplist_search(skiplist *, char *);

void skiplist_node_free(node *);

int skiplist_delete(skiplist *, char *);

void skiplist_dump(skiplist *);