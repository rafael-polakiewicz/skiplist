#include <stdio.h>
#include <stdlib.h>
#include "skip_list_lib.h"

int main() {
    char operation[20], initial_letter, word[50], meaning[140];
    skiplist * list = skiplist_init();
    node *search_result;

    while(scanf(" %s", operation) != EOF) {
        if(!strcmp(operation, "insercao")) {
            scanf(" %s", word);
            scanf(" %[^\n]", meaning); getchar();
            if(!skiplist_insert(list, word, meaning))
                printf("OPERACAO INVALIDA\n");
        }
        else if(!strcmp(operation, "remocao")) {
            scanf(" %s", word);
            if(!skiplist_delete_by_word(list, word))
                printf("OPERACAO INVALIDA\n");
        }
        else if(!strcmp(operation, "busca")) {
            scanf(" %s", word);
            search_result = skiplist_search_by_word(list, word);
            if(search_result) 
                printf("%s %s\n", search_result->word, search_result->meaning);
            else
                printf("OPERACAO INVALIDA\n");
        }
        else if(!strcmp(operation, "alteracao")) {
            scanf(" %s", word);
            scanf(" %[^\n]", meaning); getchar();
            if(!skiplist_word_meaning_change(list, word, meaning))
                printf("OPERACAO INVALIDA\n");
        }
        else if(!strcmp(operation, "impressao")) {
            scanf(" %c", &initial_letter);
            if(!skiplist_search_by_letter(list, initial_letter))
                printf("OPERACAO INVALIDA\n");
        }
        fflush(stdout);
        strcpy(operation, "");
        strcpy(word, "");
        strcpy(meaning, "");
    }

    skiplist_free(&list);

    return 0;
}