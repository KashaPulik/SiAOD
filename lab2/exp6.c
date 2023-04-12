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
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
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

    listnode* KRtab[HASH_SIZE];
    listnode* Jtab[HASH_SIZE];

    hashtab_init(KRtab);
    hashtab_init(Jtab);
    
    for(int i = 0; i < 200000; i++) {
        hashtab_add(KRtab, words[i], i, KRHash);
        hashtab_add(Jtab, words[i], i, jenkins_hash);
        
        if ((i + 1) % 10000 == 0) {
            char* word = words[getrand(0, i)];
            double KRt = wtime();
            listnode* node = hashtab_lookup(KRtab, word, KRHash);
            usleep(500);
            KRt = wtime() - KRt;
            double Jt = wtime();
            node = hashtab_lookup(Jtab, word, jenkins_hash);
            usleep(500);
            Jt = wtime() - Jt;
            
            node = node;
            printf("%d %.6lf %d %.6lf %d\n", i + 1, KRt, collisuim_cnt(KRtab, HASH_SIZE), Jt, collisuim_cnt(Jtab, HASH_SIZE));
        }
    }
}
