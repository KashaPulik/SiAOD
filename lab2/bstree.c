#include "bstree.h"

struct bstree *bstree_create(char *key, int value)
{
    bstree *node;
    node = (bstree*) malloc(sizeof(bstree));
    if(node) {
        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void bstree_add(bstree* tree, char* key, int value)
{
    bstree* parent = NULL;
    while (tree) {
        parent = tree;
        if (strcmp(key, tree->key) < 0) {
            tree = tree->left;
        } else if (strcmp(key, tree->key) > 0) {
            tree = tree->right;
        } else {
            return;
        }
    }
    bstree* node = bstree_create(key, value);
    if (strcmp(key, parent->key) < 0) {
        parent->left = node;
    } else {
        parent->right = node;
    }
}

struct bstree* bstree_lookup(bstree* tree, char* key)
{
    while (tree) {
        if (strcmp(key, tree->key) < 0) {
            tree = tree->left;
        } else if (strcmp(key, tree->key) > 0) {
            tree = tree->right;
        } else {
            return tree;
        }
    }
    return NULL;
}

void bstree_replace_node(bstree *parent, bstree *node, bstree *child)
{
    if (parent) {
        if (strcmp(node->key, parent->key) < 0) {
            parent->left = child;
        } else {
            parent->right = child;
        }
    }
}

struct bstree* bstree_delete_node(bstree* tree, bstree* node, bstree* parent)
{
    bstree *min, *minparent;
    if (!node->left) {
        bstree_replace_node(parent, node, node->right);
        if (!parent) {
            tree = node->right;
        }
    } else if (!node->right) {
        bstree_replace_node(parent, node, node->left);
        if (!parent) {
            tree = node->left;
        }
    } else {
        min = node->right;
        minparent = min;
        while (min->left) {
            minparent = min;
            min = min->left;
        }
        bstree_replace_node(parent, node, min);
        if (!parent) {
            tree = min;
        }
        if (node->right != min) {
            minparent->left = min->right;
            min->left = node->left;
            min->right = node->right;
        } else {
            min->left = node->left;
        }
    }
    free(node);
    return tree;
}

struct bstree* bstree_delete(bstree* tree, char* key)
{
    bstree* parent = NULL;
    bstree* node = tree;
    while (node && (strcmp(node->key, key) != 0)) {
        parent = node;
        if (strcmp(key, node->key) < 0) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    if (!node)
        return tree;
    return bstree_delete_node(tree, node, parent);
}

struct bstree* bstree_min(bstree* tree)
{
    while (tree->left) {
        tree = tree->left;
    }
    return tree;
}

struct bstree* bstree_max(bstree* tree)
{
    while (tree->right) {
        tree = tree->right;
    }
    return tree;
}

void bstree_traverse_in_order(bstree *tree, void (*bstree_process_node)(bstree *tree))
{
	if(tree) {
		bstree_traverse_in_order(tree->left, bstree_process_node);
		bstree_process_node(tree);
		bstree_traverse_in_order(tree->right, bstree_process_node);
	}
}

void bstree_delete_tree(bstree *tree)
{
	if(tree) {
		bstree_delete_tree(tree->left);
		bstree_delete_tree(tree->right);
		free(tree);
	}
}
