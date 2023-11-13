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

tst* tst_delete(tst* tree, char* key)
{
    if (tree == NULL)
        return NULL;
    tst* prev = NULL;
    int indicator = NONE;
    tst* node = start_of_key(tree, *key, &prev, &indicator);
    if (node == NULL)
        return tree;

    tst* key_trace[max_deep];
    int indicators[max_deep];
    for (int i = 0; i < max_deep; i++) {
        key_trace[i] = NULL;
        indicators[i] = NONE;
    }
    indicators[0] = indicator;

    node = end_of_key(node, key_trace, indicators, key);

    if (node == NULL)
        return tree;

    int last_sym = strlen(key) - 1;
    int last_node = 0;
    while (key_trace[last_node + 1] != NULL)
        last_node++;

    node->end = false;
    while (!node->eqkid && !node->hikid && !node->lokid && !node->end
           && last_node && node->ch == key[last_sym]) {
        free(node);
        last_node--;
        last_sym--;
        node = key_trace[last_node];
        switch (indicators[last_node + 1]) {
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
    if (node->ch == key[last_sym] && last_node && !node->eqkid) {
        switch (indicators[last_node]) {
        case LO:
            if (node->hikid) {
                key_trace[last_node - 1]->lokid = node->hikid;
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
                key_trace[last_node - 1]->lokid = node->lokid;
                free(node);
                return tree;
            }
            key_trace[last_node - 1]->lokid = NULL;
            free(node);
            return tree;
            break;
        case HI:
            if (node->hikid) {
                key_trace[last_node - 1]->hikid = node->hikid;
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
                key_trace[last_node - 1]->hikid = node->lokid;
                free(node);
                return tree;
            }
            key_trace[last_node - 1]->hikid = NULL;
            free(node);
            return tree;
            break;
        case EQ:
            if (node->hikid) {
                key_trace[last_node - 1]->eqkid = node->hikid;
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
                key_trace[last_node - 1]->eqkid = node->lokid;
                free(node);
                return tree;
            }
            key_trace[last_node - 1]->hikid = NULL;
            if (!node->end)
                free(node);
            return tree;
            break;
        }
    }
    if (node->ch != key[last_sym] && node->eqkid) {
        switch (indicators[last_node + 1]) {
        case HI:
            node->hikid = NULL;
            break;
        case LO:
            node->lokid = NULL;
            break;
        }
        return tree;
    }
    if (node->end || last_node || node->ch != key[last_sym]) {
        if (node->hikid) {
            node->eqkid = node->hikid;
            node->hikid = NULL;
        } else if (node->lokid) {
            node->eqkid = node->lokid;
            node->lokid = NULL;
        }
        return tree;
    }
    if (prev == NULL) {
        if (node->hikid) {
            tree = node->hikid;
            tst* lo_node = NULL;
            if (node->lokid)
                lo_node = node->lokid;
            else {
                free(node);
                return tree;
            }
            tst* hi_node = tree;
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
        free(node);
        return NULL;
    }
    switch (indicators[0]) {
    case LO:
        if (node->hikid) {
            prev->lokid = node->hikid;
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
            prev->lokid = node->lokid;
            free(node);
            return tree;
        }
        prev->lokid = NULL;
        free(node);
        return tree;
        break;
    case HI:
        if (node->hikid) {
            prev->hikid = node->hikid;
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
            prev->hikid = node->lokid;
            free(node);
            return tree;
        }
        prev->hikid = NULL;
        free(node);
        return tree;
        break;
    }
    free(node);
    return NULL;
}

void tst_print_words_from_start(tst* node, char* word, int indicator)
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
        tst_print_words_from_start(node->eqkid, word_copy, EQ);
    if (node->lokid)
        tst_print_words_from_start(node->lokid, word_copy, LO);
    if (node->hikid)
        tst_print_words_from_start(node->hikid, word_copy, HI);
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
            tst_print_words_from_start(tree->eqkid, word, EQ);
    } else {
        printf("Here is no tree\n");
        return;
    }
    if (tree->lokid)
        tst_print_all_words(tree->lokid);
    if (tree->hikid)
        tst_print_all_words(tree->hikid);
}

void tst_print_one_word(tst* node)
{
    while (node != NULL) {
        printf("%c", node->ch);
        node = node->eqkid;
        if (node == NULL)
            break;
    }
    printf("%c", node->ch);
    printf("\n");
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