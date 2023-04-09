#include "hashtab.h"

int collisuim_cnt(listnode** hashtab, int size)
{
    int q = 0;
    for (int i = 0; i < size; i++) {
        if (hashtab[i] != NULL && hashtab[i]->next != NULL)
            while (hashtab[i] != NULL) {
                hashtab[i] = hashtab[i]->next;
                q++;
            }
    }

    return q;
}

uint32_t KRHash(char* s)
{
    uint32_t h = 0, hash_mul = 31;

    while (*s)
        h = h * hash_mul + (uint32_t)*s++;
    return h % HASH_SIZE;
}

uint32_t jenkins_hash(char* s)
{
    uint32_t h = 0;
    while (*s) {
        h += (uint32_t)*s++;
        h += (h << 10);
        h ^= (h >> 6);
    }
    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);
    return h % HASH_SIZE;
}

void hashtab_init(listnode** hashtab)
{
    int i;

    for (i = 0; i < HASH_SIZE; i++)
        hashtab[i] = NULL;
}

void hashtab_add(
        listnode** hashtab,
        char* key,
        uint32_t value,
        uint32_t(hashtab_hash)(char*))
{
    listnode* node;

    uint32_t index = hashtab_hash(key);
    node = (listnode*)malloc(sizeof(*node));
    if (node) {
        node->key = key;
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}

struct listnode*
hashtab_lookup(listnode** hashtab, char* key, uint32_t (*hashtab_hash)(char*))
{
    listnode* node;

    int index = hashtab_hash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (0 == strcmp(node->key, key))
            return node;
    }
    return NULL;
}

void hashtab_delete(
        listnode** hashtab, char* key, uint32_t (*hashtab_hash)(char*))
{
    listnode *node, *prev = NULL;
    int index = hashtab_hash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (0 == strcmp(node->key, key)) {
            if (prev == NULL)
                hashtab[index] = node->next;
            else
                prev->next = node->next;
            free(node);
            return;
        }
    }
    prev = node;
}