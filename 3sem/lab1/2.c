#include <stdio.h>
#include <stdlib.h>

enum { BLACK, RED };

typedef struct rbtree {
    struct rbtree* parent;
    struct rbtree* left;
    struct rbtree* right;
    int key;
    _Bool color;
} rbtree;

rbtree* null = NULL;

void init_null()
{
    if (null)
        return;
    null = malloc(sizeof(*null));
    null->parent = NULL;
    null->left = NULL;
    null->right = NULL;
    null->color = BLACK;
    null->key = -1;
}

rbtree* create_node(int key)
{
    rbtree* node = malloc(sizeof(*node));
    node->parent = null;
    node->left = null;
    node->right = null;
    node->color = RED;
    node->key = key;
    return node;
}

rbtree* init_tree(int key)
{
    init_null();
    rbtree* tree = create_node(key);
    tree->color = BLACK;
    return tree;
}

rbtree* left_rotate(rbtree* T, rbtree* x)
{
    rbtree* y = x->right;
    x->right = y->left;

    if (y->left != null)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == null)
        T = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
    return T;
}

rbtree* right_rotate(rbtree* T, rbtree* x)
{
    rbtree* y = x->right;
    x->left = y->right;

    if (y->right != null)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == null)
        T = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
    return T;
}

rbtree* insert_fixup(rbtree* T, rbtree* z)
{
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            rbtree* y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else if (z == z->parent->right) {
                z = z->parent;
                T = left_rotate(T, z);
            } else {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                T = right_rotate(T, z);
            }
        } else {
            rbtree* y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else if (z == z->parent->left) {
                z = z->parent;
                T = right_rotate(T, z);
            } else {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                T = left_rotate(T, z);
            }
        }
    }
    T->color = BLACK;
    return T;
}

rbtree* insert(rbtree* T, rbtree *z)
{
    rbtree* y = null;
    rbtree* x = T;
    while(x != null) {
        y = x;
        if(z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if(y == null)
        T = z;
    else if(z->key < y->key)
        y->left = z;
    else 
        y->right = z;
    z->left = null;
    z->right = null;
    z->color = RED;
    return insert_fixup(T, z);
}

void PrintTree(rbtree* tree, int n)
{
    if (tree->left)
        PrintTree(tree->left, n + 1);

    for (int i = 0; i < n; i++)
        printf(" ");
    printf("%d\n", tree->key);

    if (tree->right)
        PrintTree(tree->right, n + 1);
}

void print_node(rbtree* node)
{
    printf("[%d] ", node->key);
}

void print_space(int n)
{
    int pow = 2;
    for(int i = 1; i < n; i++)
        pow *= pow;
    for(int i = 0; i < pow - 2; i++)
        printf(" ");
}

int rbh(rbtree* tree)
{
    rbtree* x = tree;
    rbtree* y = tree;
    int n = 0;
    while((x != null) || (y != null)) {
        x = x->left;
        y = y->right;
        n++;
    }
    return n;
}

void print(rbtree* tree)
{
    print_space(rbh(tree));
    print_node(tree);
}

int main()
{
    rbtree *tree = init_tree(5);
    tree = insert(tree, create_node(3));
    tree = insert(tree, create_node(6));
    printf("%d\n", tree->key);
    printf("%d\n", tree->left->key);
    printf("%d\n", tree->right->key);
    PrintTree(tree, 0);
}