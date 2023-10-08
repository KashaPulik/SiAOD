#include <cmath>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

enum { BLACK, RED };

typedef struct rbtree {
    struct rbtree* parent;
    struct rbtree* left;
    struct rbtree* right;
    int key;
    bool color;
} rbtree;

rbtree* null = NULL;

void init_null()
{
    if (null)
        return;
    null = (rbtree*)malloc(sizeof(*null));
    null->parent = NULL;
    null->left = NULL;
    null->right = NULL;
    null->color = BLACK;
    null->key = -1;
}

rbtree* create_node(int key)
{
    rbtree* node = (rbtree*)malloc(sizeof(*node));
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
    rbtree* y = x->left;
    x->left = y->right;

    if (y->right != null)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == null)
        T = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
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

rbtree* insert(rbtree* T, rbtree* z)
{
    rbtree* y = null;
    rbtree* x = T;
    while (x != null) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == null)
        T = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    z->left = null;
    z->right = null;
    z->color = RED;
    return insert_fixup(T, z);
}

std::vector<rbtree*> bfs(rbtree* tree)
{
    std::queue<rbtree*> q;
    std::vector<rbtree*> vector;
    q.push(tree);
    while (q.size() != 0) {
        rbtree* node = q.front();
        vector.push_back(node);
        // printf("%d\n", node->key);
        q.pop();
        if (node->left) {
            q.push(node->left);
        }
        if (node->right) {
            q.push(node->right);
        }
    }
    return vector;
}

void print_space(int n)
{
    printf("%*c", n, ' ');
}

int indent(int n)
{
    return pow(2, n) - 2;
}

void print(rbtree* tree)
{
    std::vector<rbtree*> vector = bfs(tree);
    int size = vector.size();
    int n = 0;
    n = (int)log2(size) + 1;
    int margin_left = indent(n);
    int b = indent(n + 1) - 1;
    int i = 0;
    int cur_level = 1;
    print_space(margin_left);
    while (i < size) {
        if (i == pow(2, cur_level) - 1) {
            cur_level++;
            margin_left = indent(--n);
            b = indent(n + 1) - 1;
            printf("\n");
            print_space(margin_left);
        }
        if (vector[i]->key < 0)
            printf("[-]");
        else if(vector[i]->color == RED)
            printf("\e[38;5;1m[%d]\e[0m", vector[i]->key);
        else
            printf("[%d]", vector[i]->key);
        print_space(b);
        i++;
    }
    printf("\n");
    for (auto& i : vector)
        printf("%d\n", i->key);
}

int main()
{
    rbtree* tree = init_tree(5);
    tree = insert(tree, create_node(3));
    tree = insert(tree, create_node(6));
    tree = insert(tree, create_node(1));
    tree = insert(tree, create_node(2));
    tree = insert(tree, create_node(4));

    // print_space(5);
    // printf("%d\n", tree->key);
    // printf("%d\n", tree->left->key);
    // printf("%d\n", tree->right->key);
    print(tree);
}