#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct tst {
    struct tst* lokid;
    struct tst* eqkid;
    struct tst* hikid;
    char ch;
    bool end;
} tst;

tst* create_node(char ch);
tst* tst_insert(tst* tree, char* key);
void tst_print_one_word(tst* node);