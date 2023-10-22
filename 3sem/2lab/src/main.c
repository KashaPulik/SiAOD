#include <trie.h>

int main()
{
    trie* tree = trie_create();
    tree = trie_insert(tree, "ABOBA", "aboba");
    tree = trie_insert(tree, "ABOB", "aboba");
    tree = trie_insert(tree, "ABOGA", "abob");
    trie_display(tree);
    tree = trie_delete(tree, "ABOBA");
    tree = trie_delete(tree, "ABOB");
    tree = trie_delete(tree, "ABOGA");
    free(tree);
}