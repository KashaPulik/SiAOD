#include "tst.h"

int max_dict_size = 1000;
int max_word_len = 64;

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

void tst_print_words_from_start(tst* node, char* word)
{
    char word_copy[max_word_len];
    strcpy(word_copy, word);
    char symbol[2] = {node->ch, '\0'};
    strcat(word_copy, symbol);
    if (node->end)
        printf("%s\n", word_copy);
    if (node->eqkid) {
        tst_print_words_from_start(node->eqkid, word_copy);
        word_copy[strlen(word)] = '\0';
    }
    if (node->lokid) {
        tst_print_words_from_start(node->lokid, word_copy);
        word_copy[strlen(word)] = '\0';
    }
    if (node->hikid) {
        tst_print_words_from_start(node->hikid, word_copy);
        word_copy[strlen(word)] = '\0';
    }
}

void tst_print_all_words(tst* tree)
{
    if (tree->eqkid) {
        char word[max_word_len];
        word[0] = '\0';
        char symbol[2] = {tree->ch, '\0'};
        strcat(word, symbol);
        tst_print_words_from_start(tree->eqkid, word);
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

void printTernaryTree(tst* root, int depth, char* branch)
{
    if (root == NULL) {
        return;
    }

    // Рекурсивно вызываем функцию для правого узла
    printTernaryTree(root->hikid, depth + 1, "r");

    // Выводим узел и ветви с соответствующим отступом
    for (int i = 0; i < depth; i++) {
        printf("   ");
    }
    printf("|--%c\n", root->ch);

    // Рекурсивно вызываем функцию для среднего узла
    printTernaryTree(root->eqkid, depth + 1, "m");

    // Рекурсивно вызываем функцию для левого узла
    printTernaryTree(root->lokid, depth + 1, "l");
}