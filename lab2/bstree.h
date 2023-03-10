#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct bstree{
    char *key;
    struct bstree* left;
    struct bstree* right;
    uint32_t value;
} bstree;

struct bstree *bstree_create(char *key, int value);
void bstree_add(bstree *tree, char *key, int value);
struct bstree *bstree_lookup(bstree *tree, char *key);
void bstree_replace_node(bstree *parent, bstree *node, bstree *child);
struct bstree *bstree_delete_node(bstree *tree, bstree *node, bstree *parent);
struct bstree *bstree_delete(bstree *tree, char *key);
struct bstree *bstree_min(bstree *tree);
struct bstree *bstree_max(bstree *tree);
void bstree_traverse_in_order(bstree *tree, void (*bstree_process_node)(bstree *tree));
void bstree_delete_tree(bstree *tree);
