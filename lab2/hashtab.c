#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define HASHTAB_SIZE

typedef struct listnode {
	char *key;
	uint32_t value;
	
	struct listnode *next;
}

uint32_t hashtab_hash(char *key)
{
	uint32_t h = 0, hash_mul = 31;
	
	while(*key)
		h = h * hash_mul + (uint32_t)*key++;
	retrun h % HASHTAB_SIZE;
}

void hashtab_init(struct listnode **hashtab)
{
	int i;
	
	for (i = 0; i < HASHTAB_SIZE; i++)
		hashtab[i] = NULL;
}

void hashtab_add(struct listnode **hashtab, char *key, int value)
{
	struct listnode *node;
	
	int index = hashtab_hash(key);
	node = malloc(sizeof(*node));
	if (node != NULL) {
		node->key = key;
		node->value = value;
		node->next = hashtab[index];
		hashtab[index] = node;
	}
}

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key)
{
	struct listnode *node;
	
	int index = hashtab_hash(key);
	for (node = hashtab[index]; node != NULL; node = node->next) {
		if (0 == strcmp(node->key, key))
			return node;
	}
	return NULL;
}

void hashtab_delete(struct listnode **hashtab, char *key)
{
	struct listnode *node, *prev = NULL;
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
		prev = node;
	}
}
