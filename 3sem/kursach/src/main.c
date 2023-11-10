#include "tst.h"
#include <stdio.h>

int n_words = 14;

int main()
{
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * n_words);
    for (int i = 0; i < n_words; i++) {
        strings[i] = malloc(11);
    }
    strings[0] = "aboba";
    strings[1] = "babka";
    strings[2] = "abobab";
    strings[3] = "pisa";
    strings[4] = "popa";
    strings[5] = "kisa";
    strings[6] = "pusia";
    strings[7] = "ya";
    strings[8] = "lublu";
    strings[9] = "kakat";
    strings[10] = "i";
    strings[11] = "pafu";
    strings[12] = "kushat";
    strings[13] = "mau";
    for (int i = 0; i < n_words; i++) {
        tree = tst_insert(tree, strings[i]);
    }
    tst_print_all_words(tree);
    printf("\n");

    for (int i = n_words - 1; i >= 0; i--) {
        tree = tst_delete(tree, strings[i]);
        printf("After deleting %s\n", strings[i]);
        tst_print_all_words(tree);
        printf("\n");
    }
    tst_print_all_words(tree);
    if (tree == NULL)
        printf("yey\n");
}