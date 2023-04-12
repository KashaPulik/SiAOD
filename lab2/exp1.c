#include "bstree.h"
#include "hashtab.h"
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    //printf("%.f\n", (double)t.tv_sec + (double)t.tv_usec * 1E-6);
    return (double)t.tv_usec;
}

bstree* fill_bstree_from_file(bstree* tree, char* filename, uint32_t amount)
{
    FILE* file = fopen(filename, "r");
    char* keys[amount];
    keys[0] = malloc(9);
    fscanf(file, "%s", keys[0]);
    tree = bstree_create(keys[0], 0);
    for (int i = 1; i < amount; i++) {
        keys[i] = malloc(9);
        fscanf(file, "%s", keys[i]);
        bstree_add(tree, keys[i], i);
    }
    fclose(file);
    return tree;
}

void read_file(char* filename, char** words)
{
    FILE* file = fopen(filename, "r");
    for (int i = 0; i < HASH_SIZE; i++) {
        words[i] = malloc(9);
        fscanf(file, "%s", words[i]);
    }
    fclose(file);
}

int main()
{
    char* words[HASH_SIZE];
    read_file("txt/slova.txt", words);
    bstree* tree = bstree_create(words[0], 0);
    listnode* hashtab[HASH_SIZE];
    hashtab_init(hashtab);
    hashtab_add(hashtab, words[0], 0, KRHash);
    for (int i = 1; i < 200000; i++) {
        bstree_add(tree, words[i], i);
        hashtab_add(hashtab, words[i], i, KRHash);
        if ((i + 1) % 10000 == 0) {
            printf("%d ", i + 1);
            char* word = words[getrand(0, i)];
            double t = wtime();
            bstree* node = bstree_lookup(tree, word);
            //printf("%s ", node->key);
            //sleep(1);
            usleep(1000);
            double t2 = wtime();
            t = t2 - t;
            printf("%.6lf ", t * 0.000001);
            //sleep(1);
            t = wtime();
            listnode* lnode = hashtab_lookup(hashtab, word, KRHash);
            //printf("%s ", lnode->key);
            //sleep(1);
            usleep(500);
            t2 = wtime();
            t = t2 - t;
            printf("%.6lf\n", t * 0.000001);
            node = node;
            lnode = lnode;
        }
    }
}
