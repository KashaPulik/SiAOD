#include "tst.h"
#include <stdio.h>
#include <sys/time.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int n_words = 1000000;

int main()
{
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("aboba.txt", "r");
    FILE* data1 = fopen("./data/data1.txt", "w");
    FILE* data2 = fopen("./data/data2.txt", "w");
    FILE* data3 = fopen("./data/data3.txt", "w");
    double time = wtime();
    fprintf(data1, "n,t\n");
    fprintf(data2, "n,t\n");
    fprintf(data3, "n,t\n");
    double eliminated_time;
    for (int i = 1; i <= n_words; i++) {
        strings[i] = malloc(11);
        fscanf(dict, "%s", strings[i]);
    }
    for (int i = 1; i <= n_words; i++) {
        tree = tst_insert(tree, strings[i]);
        if (i % 5000 == 0) {
            eliminated_time = wtime() - time;
            fprintf(data1, "%d,%f\n", i, eliminated_time);
        }
    }
    // tst_delete_tree(tree);
    // tree = NULL;
    // for(int i = 1; i <= n_words; i++) {
    //     tree = tst_insert(tree, strings[i]);
    //     if(i % 10000 == 0) {
    //         time = wtime();
    //         for(int j = 0; j < 1000000; j++)
    //             tst_lookup(tree, strings[rand()%(i - 1) + 1]);
    //         fprintf(data3, "%d,%.10lf\n", i, (wtime() - time)/1000000);
    //         fprintf(stdout, "%d,%.10lf\n", i, (wtime() - time)/1000000);
    //     }
    // }
    time = wtime();
    for (int i = n_words; i > 0; i--) {
        tree = tst_delete(tree, strings[i]);
        if (i % 5000 == 0) {
            eliminated_time = wtime() - time;
            fprintf(data2, "%d,%f\n", i, eliminated_time);
        }
    }
    tst_print_all_words(tree);
    for (int i = 1; i <= n_words; i++)
        free(strings[i]);
    free(strings);
    fclose(dict);
    fclose(data1);
    fclose(data2);
    fclose(data3);
}

// #include "tst.h"
// #include <stdio.h>

// int main()
// {
//     tst* tree = NULL;
//     char* strings[14];
//     for (int i = 0; i < 14; i++)
//         strings[i] = malloc(20);
//     strings[0] = "aboba";
//     strings[1] = "babka";
//     strings[2] = "abobab";
//     strings[3] = "pisa";
//     strings[4] = "popa";
//     strings[5] = "kisa";
//     strings[6] = "pusia";
//     strings[7] = "ya";
//     strings[8] = "lublu";
//     strings[9] = "kakat";
//     strings[10] = "i";
//     strings[11] = "pafu";
//     strings[12] = "kushat";
//     strings[13] = "mau";
//     for (int i = 0; i < 14; i++)
//         tree = tst_insert(tree, strings[i]);
//     tst_print_all_words(tree);
//     printf("\n");
//     printf("%d\n", tst_lookup(tree, "aboba"));
//     //     for (int i = 13; i >= 0; i--) {
//     //         tree = tst_delete(tree, strings[i]);
//     //         printf("After delete %s:\n", strings[i]);
//     //         tst_print_all_words(tree);
//     //         printf("\n");
//     //     }
//     //     for(int i = 0; i < 14; i++) {
//     //         free(strings[i]);
//     //         strings[i] = NULL;
//     //     }
// }