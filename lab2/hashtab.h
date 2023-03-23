#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 200003

typedef struct listnode {
    char* key;
    uint32_t value;

    struct listnode* next;
} listnode;

uint32_t KRHash(char* s);
uint32_t jenkins_hash(char* key);
void hashtab_init(listnode** hashtab);
void hashtab_add(
        listnode** hashtab,
        char* key,
        uint32_t value,
        uint32_t(hashtab_hash)(char*));
struct listnode*
hashtab_lookup(listnode** hashtab, char* key, uint32_t(*hashtab_hash)(char*));
void hashtab_delete(
        listnode** hashtab, char* key, uint32_t(*hashtab_hash)(char*));