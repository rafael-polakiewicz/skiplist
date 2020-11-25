#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SMALLEST_WORD "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
#define SKIP_LIST_HEADER_MEANING "a"
#define SKIPLIST_MAX_LEVEL 6


struct node {
    char meaning[140];
    char word[50];
    struct node **forward;
};

struct skiplist {
    int level;
    struct node *header;
};

typedef struct node node;

typedef struct skiplist skiplist;


skiplist *skiplist_init();

int rand_level();

int skiplist_insert(skiplist *, char *, char *);

node *skiplist_search_by_word(skiplist *, char *);

int skiplist_search_by_letter(skiplist *, char);

int skiplist_word_meaning_change(skiplist *, char *, char *);

void skiplist_node_free(node *);

int skiplist_delete_by_word(skiplist *, char *);

void skiplist_dump(skiplist *);

void skiplist_free(skiplist **list);