#include "bstree.h"

int main()
{
    bstree *tree;
    tree = bstree_create("7", 1);
    bstree_add(tree, "4", 1);
    bstree_add(tree, "9", 1);
    bstree_add(tree, "3", 1);
    bstree_add(tree, "5", 1);
    bstree_add(tree, "8", 1);
    bstree_add(tree, "10", 1);
    bstree_print(tree, 10);
    bstree_delete_tree(tree);
}