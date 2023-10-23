#include <stdlib.h>
#include <stdbool.h>

typedef struct tst {
    struct tst *lokid;
    struct tst *eqkid;
    struct tst *hikid;
    char ch;
    bool end;
} tst;

tst* create_node(char ch)
{
    tst *node = NULL;
    if(!(node = malloc(sizeof(node))))
        return NULL;
    node->lokid = NULL;
    node->eqkid = NULL;
    node->hikid = NULL;
    node->ch = ch;
    node->end = 0;
    return node;
}

tst* tst_insert(tst* tree, char* key)
{
    tst* node = tree;
    while(node != NULL)
    {
        if(*key < node->ch) {
            node = node->lokid;
            continue;
        }
        if(*key > node->ch) {
            node = node->hikid;
            continue;
        }
        if(*key == node->ch) {
            node = node->eqkid;
            key++;
            continue;
        }
    }
    for(;*key != '\n'; key++)
    {
        
    }
}