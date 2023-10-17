#pragma once

enum { BLACK, RED };

typedef struct rbtree {
    struct rbtree* parent;
    struct rbtree* left;
    struct rbtree* right;
    int key;
    bool color;
} rbtree;

rbtree* create_node(int key);
rbtree* init_tree(int key);
rbtree* rbtree_insert(rbtree* T, rbtree* z);
rbtree* rbtree_minimum(rbtree* T);
rbtree* rbtree_maximum(rbtree* T);
rbtree* rbtree_lookup(rbtree* T, int key);
rbtree* rbtree_delete(rbtree* T, int key);
void rbtree_free(rbtree* T);
void rbtree_print(rbtree* tree);
void rbtree_print_dfs(rbtree* T);