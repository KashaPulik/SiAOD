// #include "tst.h"
// #include <stdio.h>

// int n_words = 1000000;

// int main()
// {
//     tst* tree = NULL;
//     char** strings = malloc(sizeof(char*) * (n_words + 1));
//     FILE* dict = fopen("aboba.txt", "r");
//     for (int i = 1; i <= n_words; i++) {
//         strings[i] = malloc(11);
//         fscanf(dict, "%s", strings[i]);
//     }
//     for (int i = 1; i <= n_words; i++) {
//         tree = tst_insert(tree, strings[i]);
//     }

//     for (int i = 1; i <= n_words; i++) {
//         tree = tst_delete(tree, strings[i]);
//     }
//     tst_print_all_words(tree);
// }

#include "tst.h"
#include <stdio.h>

int main()
{
    tst* tree = NULL;
    char* strings[14];
    for (int i = 0; i < 14; i++)
        strings[i] = malloc(10);
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
    for (int i = 0; i < 14; i++)
        tree = tst_insert(tree, strings[i]);
    tst_print_all_words(tree);
    printf("\n");
    for (int i = 0; i < 14; i++) {
        tree = tst_delete(tree, strings[i]);
        printf("After delete %s:\n", strings[i]);
        printf("%c\n", tree->ch);
        tst_print_all_words(tree);
        printf("\n");
    }
}