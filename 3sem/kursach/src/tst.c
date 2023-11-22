#include "tst.h"

int max_deep = 128;

tst* create_node(char ch)
{
    tst* node = malloc(sizeof(tst));
    if (!node)
        return NULL;
    node->lokid = NULL;
    node->eqkid = NULL;
    node->hikid = NULL;
    node->ch = ch;
    node->end = false;
    return node;
}

tst* tst_insert(tst* tree, char* key)
{
    tst *node = tree, *prev = NULL;
    int indicator = NONE;
    while (node != NULL) {
        if (*key < node->ch) {
            indicator = LO;
            prev = node;
            node = node->lokid;
        } else if (*key > node->ch) {
            indicator = HI;
            prev = node;
            node = node->hikid;
        } else {
            indicator = EQ;
            prev = node;
            node = node->eqkid;
            key++;
            if (*key == '\0') {
                prev->end = true;
                return tree;
            }
        }
    }
    node = create_node(*key);
    if (tree == NULL)
        tree = node;
    switch (indicator) {
    case NONE:
        break;
    case LO:
        prev->lokid = node;
        break;
    case HI:
        prev->hikid = node;
        break;
    case EQ:
        prev->eqkid = node;
        break;
    }
    prev = node;
    key++;
    while (*key != '\0') {
        node = create_node(*key);
        key++;
        prev->eqkid = node;
        prev = node;
    }
    node->end = true;

    return tree;
}

tst* start_of_key(tst* node, char first_sym, tst** prev, int* indicator)
{
    while (node->ch != first_sym) {
        if (first_sym > node->ch) {
            if (node->hikid) {
                *indicator = HI;
                *prev = node;
                node = node->hikid;
            } else {
                return NULL;
            }
        }
        if (first_sym < node->ch) {
            if (node->lokid) {
                *indicator = LO;
                *prev = node;
                node = node->lokid;
            } else {
                return NULL;
            }
        }
    }
    return node;
}

tst* end_of_key(tst* node, tst** key_trace, int* indicators, char* key)
{
    int indicator = indicators[0];
    bool key_is_part = 1;
    int n_symbol = 0;

    for (int i = 0; i < max_deep; i++) {
        key_trace[i] = node;
        indicators[i] = indicator;
        key_is_part = node->ch == key[n_symbol] ? 1 : 0;
        if (key_is_part)
            n_symbol++;
        while (!key_is_part) {
            if (key[n_symbol] > node->ch) {
                if (node->hikid) {
                    node = node->hikid;
                    indicator = HI;
                    i++;
                    key_trace[i] = node;
                    indicators[i] = indicator;
                } else {
                    return NULL;
                }
            } else if (key[n_symbol] < node->ch) {
                if (node->lokid) {
                    node = node->lokid;
                    indicator = LO;
                    i++;
                    key_trace[i] = node;
                    indicators[i] = indicator;
                } else {
                    return NULL;
                }
            } else {
                n_symbol++;
                key_is_part = true;
            }
        }
        if (key[n_symbol] == '\0') {
            if (node->end)
                return node;
            else
                return NULL;
        }
        if (node->eqkid) {
            node = node->eqkid;
            indicator = EQ;
        } else {
            return NULL;
        }
    }
    return NULL;
}

tst* free_key(
        tst* node,
        tst** key_trace,
        int* indicators,
        int* last_node,
        int* last_sym,
        char* key)
{
    node->end = false;
    while (!node->eqkid && !node->hikid && !node->lokid && !node->end
           && *last_node && node->ch == key[*last_sym]) {
        free(node);
        *last_node -= 1;
        *last_sym -= 1;
        node = key_trace[*last_node];
        switch (indicators[*last_node + 1]) {
        case EQ:
            node->eqkid = NULL;
            break;
        case HI:
            node->hikid = NULL;
            break;
        case LO:
            node->lokid = NULL;
            break;
        }
    }
    return node;
}

void tst_restore_prop_any_case(tst* node, tst** replacement)
{
    if (node->hikid) {
        *replacement = node->hikid;
        tst* lo_node = NULL;
        if (node->lokid)
            lo_node = node->lokid;
        else {
            free(node);
            return;
        }
        tst* hi_node = node->hikid;
        while (hi_node->lokid)
            hi_node = hi_node->lokid;
        hi_node->lokid = lo_node;
        free(node);
        return;
    }
    if (node->lokid) {
        *replacement = node->lokid;
        free(node);
        return;
    }
    free(node);
    *replacement = NULL;
}

void tst_restore_prop(int indicator, tst* node, tst* prev)
{
    switch (indicator) {
    case LO:
        tst_restore_prop_any_case(node, &(prev->lokid));
        break;
    case HI:
        tst_restore_prop_any_case(node, &(prev->hikid));
        break;
    case EQ:
        tst_restore_prop_any_case(node, &(prev->eqkid));
        break;
    }
}

void init_key_trace(tst** key_trace, int* indicators)
{
    for (int i = 0; i < max_deep; i++) {
        key_trace[i] = NULL;
        indicators[i] = NONE;
    }
}

tst* tst_delete(tst* tree, char* key)
{
    if (tree == NULL)
        return NULL;
    tst* prev = NULL;
    int indicator = NONE;
    tst* node = tree;
    node = start_of_key(node, *key, &prev, &indicator);
    if (node == NULL)
        return tree;

    tst* key_trace[max_deep];
    int indicators[max_deep];
    init_key_trace(key_trace, indicators);
    indicators[0] = indicator;

    node = end_of_key(node, key_trace, indicators, key);

    if (node == NULL)
        return tree;

    int last_sym = strlen(key) - 1;
    int last_node = 0;
    while (key_trace[last_node + 1] != NULL)
        last_node++;

    node = free_key(node, key_trace, indicators, &last_node, &last_sym, key);

    if (node->eqkid)
        return tree;

    if (prev == NULL && !last_node && !node->end) {
        tst_restore_prop_any_case(node, &tree);
        return tree;
    }

    if (node->end && !node->hikid && !node->lokid)
        return tree;

    if (last_node)
        // if (node->ch == key[last_sym] && last_node) {
        tst_restore_prop(indicators[last_node], node, key_trace[last_node - 1]);
    else
        tst_restore_prop(indicators[0], node, prev);

    return tree;
}

void tst_print_words_from_node(tst* node, char* word, int indicator)
{
    char word_copy[max_deep];
    strcpy(word_copy, word);
    if (indicator == LO || indicator == HI)
        word_copy[strlen(word_copy) - 1] = '\0';
    char symbol[2] = {node->ch, '\0'};
    strcat(word_copy, symbol);
    if (node->end)
        printf("%s\n", word_copy);
    if (node->eqkid)
        tst_print_words_from_node(node->eqkid, word_copy, EQ);
    if (node->lokid)
        tst_print_words_from_node(node->lokid, word_copy, LO);
    if (node->hikid)
        tst_print_words_from_node(node->hikid, word_copy, HI);
}

void tst_print_all_words(tst* tree)
{
    if (tree) {
        char word[max_deep];
        word[0] = '\0';
        char symbol[2] = {tree->ch, '\0'};
        strcat(word, symbol);
        if (tree->end)
            printf("%s\n", word);
        if (tree->eqkid)
            tst_print_words_from_node(tree->eqkid, word, EQ);
    } else {
        printf("Here is no tree\n");
        return;
    }
    if (tree->lokid)
        tst_print_all_words(tree->lokid);
    if (tree->hikid)
        tst_print_all_words(tree->hikid);
}

void tst_delete_tree(tst* tree)
{
    if (tree == NULL)
        return;
    if (tree->eqkid)
        tst_delete_tree(tree->eqkid);
    if (tree->lokid)
        tst_delete_tree(tree->lokid);
    if (tree->hikid)
        tst_delete_tree(tree->hikid);
    free(tree);
}

tst* tst_find_sym(tst* node, char symbol)
{
    if (node == NULL)
        return NULL;
    while (symbol != node->ch) {
        if (symbol < node->ch) {
            if (node->lokid) {
                node = node->lokid;
                continue;
            } else {
                return NULL;
            }
        }
        if (symbol > node->ch) {
            if (node->hikid) {
                node = node->hikid;
                continue;
            } else {
                return NULL;
            }
        }
    }
    return node;
}

bool tst_lookup(tst* tree, char* key)
{
    if (tree == NULL)
        return false;
    tree = tst_find_sym(tree, *key);
    if (tree == NULL)
        return false;
    key++;
    while (*key != '\0') {
        if (tree->eqkid) {
            if (tree->eqkid->ch == *key) {
                tree = tree->eqkid;
                key++;
                continue;
            }
            tree = tree->eqkid;
        } else {
            return false;
        }
        tree = tst_find_sym(tree, *key);
        if (tree == NULL)
            return false;
        key++;
    }
    return tree->end;
}

void tst_prefix_search(tst* tree, char* prefix)
{
    if (tree == NULL) {
        printf("Here is no keys\n");
        return;
    }
    char prefix_copy[max_deep];
    strcpy(prefix_copy, prefix);
    tree = tst_find_sym(tree, *prefix);
    if (tree == NULL) {
        printf("Here is no keys with prefix '%s'\n", prefix_copy);
        return;
    }
    prefix++;
    while (*prefix != '\0') {
        if (tree->eqkid) {
            if (tree->eqkid->ch == *prefix) {
                tree = tree->eqkid;
                prefix++;
                continue;
            }
            tree = tree->eqkid;
        } else {
            printf("Here is no keys with prefix '%s'\n", prefix_copy);
            return;
        }
        tree = tst_find_sym(tree, *prefix);
        if (tree == NULL) {
            printf("Here is no keys with prefix '%s'\n", prefix_copy);
            return;
        }
        prefix++;
    }
    if(tree->end)
        printf("%s\n", prefix_copy);
    if(tree->eqkid)
        tst_print_words_from_node(tree->eqkid, prefix_copy, EQ);
}