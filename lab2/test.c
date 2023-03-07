#include "bstree.h"

int main()
{
    bstree *tree;
    tree = bstree_create("10", 54);
    bstree_add(tree, "2", 15);
    bstree_add(tree, "43", 15);
    bstree_add(tree, "14", 15);
    bstree_add(tree, "50", 15);
    bstree_add(tree, "6", 15);
    bstree_add(tree, "7", 15);
    bstree_print(tree, 10);
    bstree_delete_tree(tree);
}