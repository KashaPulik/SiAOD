#include <cmath>
#include <iostream>
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
                T = right_rotate(T, z->parent->parent);
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
                T = left_rotate(T, z->parent->parent);
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

rbtree* rb_transplant(rbtree* T, rbtree* u, rbtree* v)
{
    if (u->parent == null)
        T = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
    return T;
}

rbtree* rb_delete_fixup(rbtree* T, rbtree* x)
{
    while (x != T && x->color == BLACK) {
        if (x == x->parent->left) {
            rbtree* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                T = left_rotate(T, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    T = right_rotate(T, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                T = left_rotate(T, x->parent);
                x = T;
            }
        } else {
            rbtree* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                T = right_rotate(T, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    T = left_rotate(T, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                T = right_rotate(T, x->parent);
                x = T;
            }
        }
    }
    x->color = BLACK;
    return T;
}

rbtree* tree_minimum(rbtree* T)
{
    rbtree* min = T;
    while (min->left != null)
        min = min->left;
    return min;
}

rbtree* tree_maximum(rbtree* T)
{
    rbtree* max = T;
    while (max->right != null)
        max = max->right;
    return max;
}

rbtree* rb_delete(rbtree* T, rbtree* z)
{
    rbtree* y = z;
    rbtree* x = NULL;
    bool y_original_color = y->color;
    if (z->left == null) {
        x = z->right;
        T = rb_transplant(T, z, z->right);
    } else if (z->right == null) {
        x = z->left;
        T = rb_transplant(T, z, z->left);
    } else {
        y = tree_minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            T = rb_transplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        T = rb_transplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == BLACK)
        T = rb_delete_fixup(T, x);
    return T;
}

std::vector<rbtree*> bfs(rbtree* tree)
{
    std::queue<rbtree*> q;
    std::vector<rbtree*> vector;
    q.push(tree);
    while (q.size() != 0) {
        rbtree* node = q.front();
        vector.push_back(node);
        q.pop();

        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
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
    n = (int)log2(size) + 2;
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
            printf("   ");
        else if (vector[i]->color == RED)
            printf("\e[38;5;1m[%d]\e[0m", vector[i]->key);
        else
            printf("[%d]", vector[i]->key);
        print_space(b);
        i++;
    }
    printf("\n");
}

int main()
{
    // rbtree* tree = init_tree(5);
    // tree = insert(tree, create_node(3));
    // tree = insert(tree, create_node(6));
    // tree = insert(tree, create_node(1));
    // tree = insert(tree, create_node(2));
    // tree = insert(tree, create_node(4));
    // tree = insert(tree, create_node(7));
    // tree = insert(tree, create_node(8));
    // tree = insert(tree, create_node(9));
    // tree = insert(tree, create_node(0));
    rbtree* tree = init_tree(0);
    rbtree* node1 = create_node(1);
    rbtree* node2 = create_node(2);
    rbtree* node3 = create_node(3);
    tree = insert(tree, node1);
    tree = insert(tree, node2);
    tree = insert(tree, node3);
    // tree = insert(tree, create_node(4));
    // tree = insert(tree, create_node(5));
    // tree = insert(tree, create_node(6));
    // tree = insert(tree, create_node(7));
    // tree = insert(tree, create_node(8));
    // tree = insert(tree, create_node(9));

    // print_space(5);
    // printf("%d\n", tree->key);
    // printf("%d\n", tree->left->key);
    // printf("%d\n", tree->right->key);
    print(tree);
    tree = rb_delete(tree, node3);
    std::cout << "-------------------------" << std::endl;
    print(tree);
    tree = rb_delete(tree, node2);
    std::cout << "-------------------------" << std::endl;

    print(tree);
    tree = rb_delete(tree, node1);
    std::cout << "-------------------------" << std::endl;

    print(tree);

    tree = rb_delete(tree, tree);
    std::cout << "-------------------------" << std::endl;
    print(tree);

}