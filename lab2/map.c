#include <stdint.h>
#include <stdio.h>

typedef struct {
    char* key;
    uint32_t value;
    struct map* next;
} map;

struct map *map_create_node(uint32_t value)
{
    map *node = (map*) malloc(sizeof(map));
    if(!node)
        return NULL;
    node->value = value;
    node->next = NULL;
    return node;
}

struct map *map_add_end(map *current_map, uint32_t value)
{
    map *newnode = map_create_node(value);
    if(!current_map)
        return newnode;
    map *node = current_map;
    while(node->next)
        node = node->next;
    node->next = newnode;
    return current_map;
}