#include "tst.h"
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int n_words = 1000000;
int step = 1000;
int n_iterations = 1000000;

void insertion_time_experiment();
void deleting_time_experiment();
void lookup_time_experiment();

int main()
{
    srand(time(0));

    insertion_time_experiment();

    deleting_time_experiment();

    lookup_time_experiment();
}

void insertion_time_experiment()
{
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("aboba.txt", "r");
    FILE* data = fopen("./data/insertion_time.txt", "w");
    double start_time = wtime();
    fprintf(data, "n,t\n");
    double eliminated_time;
    for (int i = 1; i <= n_words; i++) {
        strings[i] = malloc(11);
        fscanf(dict, "%s", strings[i]);
    }
    for (int i = 1; i <= n_words; i++) {
        tree = tst_insert(tree, strings[i]);
        if (i % step == 0) {
            eliminated_time = wtime() - start_time;
            fprintf(data, "%d,%f\n", i, eliminated_time);
        }
    }
    for (int i = 1; i <= n_words; i++)
        free(strings[i]);
    free(strings);
    fclose(dict);
    fclose(data);
    tst_delete_tree(tree);
}

void deleting_time_experiment()
{
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("aboba.txt", "r");
    FILE* data = fopen("./data/deleting_time.txt", "w");
    double start_time = wtime();
    fprintf(data, "n,t\n");
    double eliminated_time;
    for (int i = 1; i <= n_words; i++) {
        strings[i] = malloc(11);
        fscanf(dict, "%s", strings[i]);
    }

    for (int i = 1; i <= n_words; i++)
        tree = tst_insert(tree, strings[i]);

    for (int i = n_words; i > 0; i--) {
        tree = tst_delete(tree, strings[i]);
        if (i % 5000 == 0) {
            eliminated_time = wtime() - start_time;
            fprintf(data, "%d,%f\n", i, eliminated_time);
        }
    }

    for (int i = 1; i <= n_words; i++)
        free(strings[i]);
    free(strings);
    fclose(dict);
    fclose(data);
}

void lookup_time_experiment()
{
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("aboba.txt", "r");
    FILE* data = fopen("./data/lookup_time.txt", "w");

    fprintf(data, "n,t\n");

    for (int i = 1; i <= n_words; i++) {
        strings[i] = malloc(11);
        fscanf(dict, "%s", strings[i]);
    }

    double start_time;

    for (int i = 1; i <= n_words; i++) {
        tree = tst_insert(tree, strings[i]);
        if (i % step == 0) {
            start_time = wtime();
            for (int j = 0; j < n_iterations; j++)
                tst_lookup(tree, strings[rand() % (i - 1) + 1]);
            fprintf(data,
                    "%d,%.10lf\n",
                    i,
                    (wtime() - start_time) / n_iterations);
            fprintf(stdout,
                    "%d,%.10lf\n",
                    i,
                    (wtime() - start_time) / n_iterations);
        }
    }

    for (int i = 1; i <= n_words; i++)
        free(strings[i]);
    free(strings);
    fclose(dict);
    fclose(data);
    tst_delete_tree(tree);
}