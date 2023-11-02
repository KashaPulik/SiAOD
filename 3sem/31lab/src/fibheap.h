#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct fibheap_node {
    int key;
    struct fibheap_node* parent;
    struct fibheap_node* child;
    struct fibheap_node* left;
    struct fibheap_node* right;
    int degree;
    bool mark;
} fibheap_node;

typedef struct fibheap {
    fibheap_node* min;
    int nnodes;
} fibheap;

fibheap* make_fibheap();
fibheap_node* make_fibheap_node(int key);
void fibheap_insert(fibheap* heap, int key);
void fibheap_add_node_to_root_list(fibheap_node* node, fibheap_node* h);
void fibheap_remove_node_from_root_list(fibheap_node* z);
fibheap* fibheap_union(fibheap* heap1, fibheap* heap2);
void fibheap_link_lists(fibheap_node* heap1, fibheap_node* heap2);
fibheap_node* fibheap_delete_min(fibheap* heap);
void fibheap_consolidate(fibheap* heap);
int D(int n);
void fibheap_swap(fibheap_node** x, fibheap_node** y);
void fibheap_link(fibheap* heap, fibheap_node* y, fibheap_node* x);
void fibheap_decrease_key(fibheap* heap, fibheap_node* x, int newkey);
void fibheap_cut(fibheap* heap, fibheap_node* x, fibheap_node* y);
void fibheap_cascading_cut(fibheap* heap, fibheap_node* y);
void fibheap_delete(fibheap* heap, fibheap_node* x);
void fibheap_print(fibheap_node* min);