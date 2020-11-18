#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SKIPLIST_MAX_LEVEL 6

typedef struct node node;

typedef struct skiplist skiplist;

skiplist *skiplist_init(skiplist *list);

int rand_level();

int skiplist_insert(skiplist *, int, char *);

node *skiplist_search(skiplist *, char *);

void skiplist_node_free(node *);

int skiplist_delete(skiplist *, char *);

void skiplist_dump(skiplist *);