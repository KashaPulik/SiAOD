#include "tst.h"
#include <stdio.h>

int main()
{
    tst* tree = NULL;
    tree = tst_insert(tree, "aboba");
    tst_print_one_word(tree);
    tree = tst_insert(tree, "babka");
    tst_print_one_word(tree->hikid);
    tree = tst_insert(tree, "abobab");
    tst_print_one_word(tree);
}