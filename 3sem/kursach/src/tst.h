#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { NONE = -1, LO, HI, EQ };

typedef struct tst {
    struct tst* lokid;
    struct tst* eqkid;
    struct tst* hikid;
    char ch;
    bool end;
} tst;

extern int max_deep;

tst* create_node(char ch);
tst* tst_insert(tst* tree, char* key);
tst* tst_delete(tst* tree, char* key);
void tst_print_one_word(tst* node);
void tst_print_all_words(tst* tree);
void tst_delete_tree(tst* tree);
bool tst_lookup(tst* tree, char* key);