#include "tst.h"

tst* create_node(char ch)
{
    tst* node = malloc(sizeof(tst));
    if (!node)
        return NULL;
    node->lokid = NULL;
    node->eqkid = NULL;
    node->hikid = NULL;
    node->ch = ch;
    node->end = false;
    return node;
}

tst* tst_insert(tst* tree, char* key)
{
    tst *node = tree, *prev = NULL;
    int indicator = -1;
    while (node != NULL) {
        if (*key < node->ch) {
            indicator = 0;
            prev = node;
            node = node->lokid;
        } else if (*key > node->ch) {
            indicator = 1;
            prev = node;
            node = node->hikid;
        } else {
            indicator = 2;
            prev = node;
            node = node->eqkid;
            key++;
        }
    }

    node = create_node(*key);

    if (tree == NULL)
        tree = node;

    switch (indicator) {
    case -1:
        break;
    case 0:
        prev->lokid = node;
        break;
    case 1:
        prev->hikid = node;
        break;
    case 2:
        prev->eqkid = node;
        break;
    }

    prev = node;
    key++;

    while (*key != '\0') {
        node = create_node(*key);
        key++;
        prev->eqkid = node;
        prev = node;
    }
    node->end = true;

    return tree;
}

void tst_print_one_word(tst* node)
{
    while (node != NULL) {
        printf("%c", node->ch);
        node = node->eqkid;
        if(node == NULL)
            break;
    }
    printf("%c", node->ch);
    printf("\n");
}