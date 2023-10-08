#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

typedef struct rbtree {
    struct rbtree* parent;
    struct rbtree* left;
    struct rbtree* right;
    struct rbtree* root;
    struct rbtree* nil;
    int color;
    int key;
} rbtree;

rbtree* create_nil_node()
{
    rbtree* nil_node;

    nil_node = malloc(sizeof(*nil_node));
    if (nil_node) {
        nil_node->parent = nil_node;
        nil_node->left = nil_node;
        nil_node->right = nil_node;
        nil_node->root = nil_node;
        nil_node->nil = nil_node;
        nil_node->color = BLACK;
        nil_node->key = 0;
    }
    return nil_node;
}

rbtree* create_node(int key, rbtree* nil_node)
{
    if (!nil_node) {
        nil_node = create_nil_node();
        return nil_node;
    }
    rbtree* node;
    node = malloc(sizeof(*node));
    if (node) {
        node->parent = nil_node;
        node->left = nil_node;
        node->right = nil_node;
        node->root = nil_node;
        node->nil = nil_node;
        node->color = RED;
        node->key = key;
    }
    return node;
}

void left_rotate(rbtree* T, rbtree* x)
{
    rbtree* y = x->right;
    x->right = y->left;
    if (y->left != T->nil)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == T->nil)
        T->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void right_rotate(rbtree* T, rbtree* x)
{
    rbtree* y = x->left;
    x->left = y->right;
    if (y->right != T->nil)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == T->nil)
        T->root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void rbtree_add_fixup(rbtree* T, rbtree* z)
{
    rbtree* y = NULL;
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(T, z->parent->parent);
            }
        } else {
            y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = BLACK;
}

void rbtree_add(rbtree* T, rbtree* z)
{
    rbtree* y = T->nil;
    rbtree* x = T->root;
    while (x != T->nil) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == T->nil)
        T->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    z->left = T->nil;
    z->right = T->nil;
    z->color = RED;
    rbtree_add_fixup(T, z);
}

int main()
{
    rbtree* tree = create_node(1, NULL);
    rbtree_add(tree, create_node(5, tree->nil));
    rbtree_add(tree, create_node(6, tree->nil));
    printf("%d\n", tree->key);
    printf("%p %p\n", tree, tree->left);
}