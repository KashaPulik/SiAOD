#include "tst.h"
#include <stdio.h>

int main()
{
    tst* tree = NULL;
    tree = tst_insert(tree, "aboba");
    tree = tst_insert(tree, "babka");
    tree = tst_insert(tree, "abobab");
    tree = tst_insert(tree, "pisa");
    tree = tst_insert(tree, "popa");
    printf("%c\n", tree->hikid->hikid->eqkid->ch);
    tree = tst_insert(tree, "kisa");
    tree = tst_insert(tree, "pusia");
    tree = tst_insert(tree, "ya");
    tree = tst_insert(tree, "lublu");
    tree = tst_insert(tree, "kakat");
    tree = tst_insert(tree, "i");
    tree = tst_insert(tree, "pafu");
    tree = tst_insert(tree, "i");
    tree = tst_insert(tree, "lublu");
    tree = tst_insert(tree, "kushat");
    tree = tst_insert(tree, "mau");
    tst_print_all_words(tree);
}