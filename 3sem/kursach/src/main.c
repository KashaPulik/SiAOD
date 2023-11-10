#include "tst.h"
#include <stdio.h>

int n_words = 1000;

int main()
{
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("aboba.txt", "r");
    for (int i = 1; i <= n_words; i++) {
        strings[i] = malloc(11);
        fscanf(dict, "%s", strings[i]);
    }
    for (int i = 1; i <= n_words; i++) {
        tree = tst_insert(tree, strings[i]);
    }

    for (int i = n_words; i > 0; i--) {
        tree = tst_delete(tree, strings[i]);
    }

    // for (int i = 1; i <= n_words; i++) {
    //     tree = tst_delete(tree, strings[i]);
    // }

    if (tree == NULL)
        printf("yey\n");
    else
        tst_print_all_words(tree);
}