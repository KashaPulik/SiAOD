#include "bstree.h"

int main()
{
    bstree *tree = bstree_create("k", 1);
    bstree_add(tree, "e", 2);
    bstree_add(tree, "q", 3);
    bstree_add(tree, "d", 4);
    bstree_add(tree, "f", 5);
    bstree_add(tree, "p", 6);
    bstree_add(tree, "r", 7);
    bstree_print(tree, 0);
    printf("%d\n", bstree_lookup(tree, "f")->value);
    tree = bstree_delete(tree, "f");
    printf("\n");
    bstree_print(tree, 0);
    tree = bstree_delete(tree, "q");
    printf("\n");
    bstree_print(tree, 0);
    printf("%d\n", bstree_min(tree)->value);
    printf("%d\n", bstree_max(tree)->value);
    bstree_delete_tree(tree);
}