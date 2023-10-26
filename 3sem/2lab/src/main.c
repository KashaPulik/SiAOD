#include <trie.h>

int main()
{
    trie* tree = trie_create();
    tree = trie_insert(tree, "ABOBA", "a");
    tree = trie_insert(tree, "ABOBB", "b");
    tree = trie_insert(tree, "ABOBC", "c");
    tree = trie_insert(tree, "ABOBDA", "d");
    tree = trie_insert(tree, "ABOBDB", "d");
    tree = trie_insert(tree, "ABOBDBA", "d");
    tree = trie_insert(tree, "BABUSHKA", "e");
    tree = trie_insert(tree, "BABA", "e");
    trie_display(tree);
    tree = trie_delete(tree, "ABOBA");
    tree = trie_delete(tree, "ABOBB");
    trie_display(tree);
}