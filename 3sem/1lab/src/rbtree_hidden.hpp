#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <queue>

enum { BLACK, RED };

typedef struct rbtree {
    struct rbtree* parent;
    struct rbtree* left;
    struct rbtree* right;
    int key;
    bool color;
} rbtree;

extern rbtree* null;

extern int tree_count;

void init_null();
rbtree* left_rotate(rbtree* T, rbtree* x);
rbtree* right_rotate(rbtree* T, rbtree* x);
rbtree* insert_fixup(rbtree* T, rbtree* z);
rbtree* transplant(rbtree* T, rbtree* u, rbtree* v);
rbtree* rbtree_delete_fixup(rbtree* T, rbtree* x);
std::vector<rbtree*> bfs(rbtree* tree);
void print_space(int n);
int indent(int n);