#include <rbtree_hidden.hpp>

rbtree* null = NULL;

int tree_count = 0;

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

rbtree* transplant(rbtree* T, rbtree* u, rbtree* v)
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

rbtree* rbtree_delete_fixup(rbtree* T, rbtree* x)
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
