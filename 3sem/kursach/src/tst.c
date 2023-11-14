#include "tst.h"

int max_deep = 64;

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

// Вставка ключа-строки в дерево
tst* tst_insert(tst* tree, char* key)
{
    // Создаются указатели на текущий и предшествующий узел
    tst *node = tree, *prev = NULL;
    // Индикатор хранит в себе информацию о последнем шаге от родительского узла
    // к дочернему
    int indicator = NONE;
    // В цикле происходит поиск места, с которого следует начать вставку ключа
    while (node != NULL) {
        // Если символ из ключа ближе к началу алфавита, чем тот, что уже есть в
        // дереве, то он ставится слева от существующего узла
        if (*key < node->ch) {
            indicator = LO;
            prev = node;
            node = node->lokid;
            // Если символ из ключа дальше от начала алфавита, чем тот, что уже
            // есть в дереве, то он ставится справа от существующего узла
        } else if (*key > node->ch) {
            indicator = HI;
            prev = node;
            node = node->hikid;
            // Если символ совпадает с тем, что уже есть в дереве, то его не
            // нужно вставлять повторно, требуется лишь добавить недостающие
            // символы, поэтому наблюдение переходит к следующему символу, а
            // указатель перемещается вниз по центру
        } else {
            indicator = EQ;
            prev = node;
            node = node->eqkid;
            key++;
        }
    }
    if (*key == '\0')
        return tree;
    // Под новый узел выделяется память
    node = create_node(*key);
    // Если корня дерева не существует, то новый узел становится корнем
    if (tree == NULL)
        tree = node;
    // Далее узел вставляется в правильное место в дереве, если в дереве уже
    // были узлы
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
    // После этого узел помечается как предшествующий и происходит смещении к
    // следующему символу из ключа
    prev = node;
    key++;
    // Цикл выполняется до тех пор, пока не будет достигнут конец ключа.
    // Если ключ уже подошёл к концу в предыдущем шаге, то цикл не будет
    // выполнятся и новые узлы создаваться не будут.
    // В цикле создаются узлы под оставшиеся буквы, чтобы вставить их в дерево.
    while (*key != '\0') {
        node = create_node(*key);
        key++;
        prev->eqkid = node;
        prev = node;
    }
    // В самом конце последний вставленный узел помечается как узел, который
    // хранит в себе последний символ ключа и функция возвращает указатель на
    // корень дерева
    node->end = true;

    return tree;
}

tst* find_next_sym(tst* node, char key)
{
    tst* tmp = node;
    while (tmp->lokid) {
        tmp = tmp->lokid;
        if (tmp->ch == key)
            return tmp;
    }
    tmp = node;
    while (tmp->hikid) {
        tmp = tmp->hikid;
        if (tmp->ch == key)
            return tmp;
    }
    return NULL;
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

tst* end_of_key(tst* node, tst** key_nodes, int* indicators, char* key)
{
    int indicator = indicators[0];
    bool key_is_part = 1;
    int n_symbol = 0;

    for (int i = 0; i < max_deep; i++) {
        key_nodes[i] = node;
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
                    key_nodes[i] = node;
                    indicators[i] = indicator;
                } else {
                    return NULL;
                }
            } else if (key[n_symbol] < node->ch) {
                if (node->lokid) {
                    node = node->lokid;
                    indicator = LO;
                    i++;
                    key_nodes[i] = node;
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
    return node;
}

tst* free_key(
        tst* node,
        tst** key_nodes,
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
        node = key_nodes[*last_node];
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

void tst_restore_prop(int indicator, tst* node, tst* prev)
{
    switch (indicator) {
    case LO:
        if (node->hikid) {
            prev->lokid = node->hikid;
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
            prev->lokid = node->lokid;
            free(node);
            return;
        }
        prev->lokid = NULL;
        free(node);
        return;
        break;
    case HI:
        if (node->hikid) {
            prev->hikid = node->hikid;
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
            prev->hikid = node->lokid;
            free(node);
            return;
        }
        prev->hikid = NULL;
        free(node);
        return;
        break;
    case EQ:
        if (node->hikid) {
            prev->eqkid = node->hikid;
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
            prev->eqkid = node->lokid;
            free(node);
            return;
        }
        prev->eqkid = NULL;
        free(node);
        return;
        break;
    }
}

tst* tst_root_restore_prop(tst* tree, tst* node)
{
    if (node->hikid) {
        tree = node->hikid;
        tst* lo_node = NULL;
        if (node->lokid)
            lo_node = node->lokid;
        else {
            free(node);
            return tree;
        }
        tst* hi_node = node->hikid;
        while (hi_node->lokid)
            hi_node = hi_node->lokid;
        hi_node->lokid = lo_node;
        free(node);
        return tree;
    }
    if (node->lokid) {
        tree = node->lokid;
        free(node);
        return tree;
    }
    tree = NULL;
    free(node);
    return tree;
}

void init_key_nodes(tst** key_nodes, int* indicators)
{
    for (int i = 0; i < max_deep; i++) {
        key_nodes[i] = NULL;
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
    init_key_nodes(key_trace, indicators);
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

    if (prev == NULL && !last_node && !node->end)
        return tst_root_restore_prop(tree, node);

    if (node->end && !node->hikid && !node->lokid)
        return tree;

    if (node->ch == key[last_sym] && last_node) {
        tst_restore_prop(indicators[last_node], node, key_trace[last_node - 1]);
        return tree;
    }

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

void tst_print_all_words_with_prefix(tst* node, char* prefix)
{
    // if (!node) {
    //     printf("Here is no tree\n");
    //     return;
    // }
    char word[max_deep];
    word[0] = '\0';
    strcat(word, prefix);
    if (node->end)
        printf("%s\n", word);
    if (node->eqkid)
        tst_print_words_from_node(node->eqkid, word, EQ);
}

void tst_prefix_search(tst* tree, char* prefix)
{
    char prefix_copy[max_deep];
    strcpy(prefix_copy, prefix);
    if (tree == NULL) {
        printf("Here is no keys\n");
        return;
    }
    tree = tst_find_sym(tree, *prefix);
    if (tree == NULL) {
        printf("Here is no keys with prefix '%s'\n", prefix);
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
            printf("Here is no keys with prefix '%s'\n", prefix);
            return;
        }
        tree = tst_find_sym(tree, *prefix);
        if (tree == NULL) {
            printf("Here is no keys with prefix '%s'\n", prefix);
            return;
        }
        prefix++;
    }
    tst_print_all_words_with_prefix(tree, prefix_copy);
}