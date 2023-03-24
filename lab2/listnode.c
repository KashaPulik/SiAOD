#include <stdint.h>
#include <string.h>
#include <stdio.h>

typedef struct listnode {
    char* key;
    uint32_t value;

    struct listnode* next;
} listnode;

struct listnode *create_node(uint32_t value, char* key)
{
    listnode *node = (listnode*) malloc(sizeof(listnode));
    if(!node)
        return NULL;
    
    node->value = value;
    node->key = key;
    node->next = NULL;
    return node;
}

struct listnode *add_front(listnode *list, uint32_t value, char* key)
{
	listnode *node = create_node(value, key);
	node->next = list;
	return node;
}

struct listnode *add_end(listnode *current_node, uint32_t value)
{
    listnode *newnode = create_node(value);
    if(!current_node)
        return newnode;
    listnode *node = current_node;
    while(node->next)
        node = node->next;
    node->next = newnode;
    return current_map;
}

struct listnode listnode_lookup(listnode *list, char* key)
{
	listnode* curnode = list;
	while(curnode) {
		if(strcmp(curnode->key, key) == 0)
			return curnode;
		curnode = curnode->next;
	}
	return NULL;
}

void free_listnode(listnode list)
{
	listnode *prev;
	while(list) {
		prev = list;
		list = list->next;
		free(prev);
}
