#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct trie {
    char* value;
    char ch;
    struct trie* sibling;
    struct trie* child;
} trie;

trie* trie_create();
struct trie* trie_insert(struct trie* root, char* key, char* value);
char* trie_lookup(struct trie* root, char* key);
struct trie* trie_delete(struct trie* root, char* key);
void trie_display(struct trie* root);