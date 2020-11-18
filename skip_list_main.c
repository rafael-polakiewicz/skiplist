#include <stdio.h>
#include <stdlib.h>
#include "skip_list_lib.h"

int main() {
    int i;
    char *arr[] = { "testando", "tomara", "que", "de", "certo"};
    skiplist *list;
    node *aux;

    skiplist_init(list);
    printf("Insert:--------------------\n");
    for (i = 0; i < 5; i++) {
        skiplist_insert(list, i, arr[i]);
    }
    skiplist_dump(list);
    printf("Search:--------------------\n");
    // int keys[] = { 3, 4, 7, 10, 111 };

    for (i = 0; i < 5; i++) {
        aux = skiplist_search(list, arr[i]);
        if (aux) {
            printf("key = %d, value = %s\n", i, aux->word);
        } else {
            printf("key = %d, not fuound\n", arr[i]);
        }
    }

    printf("Search:--------------------\n");
    skiplist_delete(list, "testando");
    skiplist_delete(list, "que");
    skiplist_dump(list);

    return 0;
}