#include <rbtree_hidden.hpp>

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
    tree_count++;
    rbtree* tree = create_node(key);
    tree->color = BLACK;
    return tree;
}

rbtree* rbtree_insert(rbtree* T, rbtree* z)
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

rbtree* rbtree_minimum(rbtree* T)
{
    rbtree* min = T;
    while (min->left != null)
        min = min->left;
    return min;
}

rbtree* rbtree_maximum(rbtree* T)
{
    rbtree* max = T;
    while (max->right != null)
        max = max->right;
    return max;
}

rbtree* rbtree_lookup(rbtree* T, int key)
{
    while (T->key != key) {
        if (T == null)
            return NULL;
        if (key > T->key)
            T = T->right;
        if (key < T->key)
            T = T->left;
    }
    return T;
}

rbtree* rbtree_delete(rbtree* T, int key)
{
    rbtree* z = rbtree_lookup(T, key);
    rbtree* y = z;
    rbtree* x = NULL;
    bool y_original_color = y->color;
    if (z->left == null) {
        x = z->right;
        T = transplant(T, z, z->right);
    } else if (z->right == null) {
        x = z->left;
        T = transplant(T, z, z->left);
    } else {
        y = rbtree_minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            T = transplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        T = transplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == BLACK)
        T = rbtree_delete_fixup(T, x);
    free(z);
    return T;
}

void rbtree_free(rbtree* T)
{
    delete_tree(T);
    if (tree_count-- == 1) {
        free(null);
        null = NULL;
    }
}

void rbtree_print(rbtree* tree)
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

void rbtree_print_dfs(rbtree* T)
{
    if (T->color == RED)
        printf("\e[38;5;1m[%d]\e[0m ", T->key);
    else
        printf("[%d] ", T->key);
    if (T->left != null)
        rbtree_print_dfs(T->left);
    if (T->right != null)
        rbtree_print_dfs(T->right);
}