#include "experimental_funcs.h"
#include "tst.h"

int n_words = 1000000;
int step = 10000;
int n_iterations = 1000000;

void random_insertion_time_experiment()
{
    int tmp_step = step;
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("./data/aboba.txt", "r");
    FILE* data = fopen(
            "./experimental_data/random_insertion_time.txt", "w");
    double start_time;
    fprintf(data, "n,t\n0,0\n");
    for (int i = 1; i <= n_words; i++) {
        strings[i] = malloc(11);
        fscanf(dict, "%s", strings[i]);
    }
    start_time = wtime();
    for (int i = 1; i <= n_words; i++) {
        tree = tst_insert(tree, strings[i]);
        if (i % tmp_step == 0) {
            fprintf(data, "%d,%lf\n", i, wtime() - start_time);
            tmp_step += step;
            i = 1;
            if (tmp_step > n_words)
                break;
            tst_delete_tree(tree);
            tree = NULL;
            start_time = wtime();
        }
    }
    for (int i = 1; i <= n_words; i++)
        free(strings[i]);
    free(strings);
    fclose(dict);
    fclose(data);
    tst_delete_tree(tree);
}

void sorted_insertion_time_experiment()
{
    int tmp_step = step;
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("./data/sorted_aboba.txt", "r");
    FILE* data = fopen(
            "./experimental_data/sorted_insertion_time.txt", "w");
    double start_time;
    fprintf(data, "n,t\n0,0\n");
    for (int i = 1; i <= n_words; i++) {
        strings[i] = malloc(11);
        fscanf(dict, "%s", strings[i]);
    }
    start_time = wtime();
    for (int i = 1; i <= n_words; i++) {
        tree = tst_insert(tree, strings[i]);
        if (i % tmp_step == 0) {
            fprintf(data, "%d,%lf\n", i, wtime() - start_time);
            tmp_step += step;
            i = 1;
            if (tmp_step > n_words)
                break;
            tst_delete_tree(tree);
            tree = NULL;
            start_time = wtime();
        }
    }
    for (int i = 1; i <= n_words; i++)
        free(strings[i]);
    free(strings);
    fclose(dict);
    fclose(data);
    tst_delete_tree(tree);
}

void deleting_from_last_time_random_experiment()
{
    int tmp_step = step;
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("./data/aboba.txt", "r");
    FILE* data = fopen(
            "./experimental_data/deleting_from_last_time_random.txt",
            "w");
    fprintf(data, "n,t\n0,0\n");
    for (int i = 1; i <= n_words; i++) {
        strings[i] = malloc(11);
        fscanf(dict, "%s", strings[i]);
    }

    double start_time;
    for (int i = 1; i <= n_words; i++) {
        tree = tst_insert(tree, strings[i]);
        if (i % tmp_step == 0) {
            start_time = wtime();
            for (int j = tmp_step; j > 0; j--)
                tree = tst_delete(tree, strings[j]);
            fprintf(data, "%d,%lf\n", i, wtime() - start_time);
            tmp_step += step;
            i = 1;
            if (tmp_step > n_words)
                break;
        }
    }

    for (int i = 1; i <= n_words; i++)
        free(strings[i]);
    free(strings);
    fclose(dict);
    fclose(data);
}

void deleting_from_last_time_sorted_experiment()
{
    int tmp_step = step;
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("./data/sorted_aboba.txt", "r");
    FILE* data = fopen(
            "./experimental_data/deleting_from_last_time_sorted.txt",
            "w");
    fprintf(data, "n,t\n0,0\n");
    for (int i = 1; i <= n_words; i++) {
        strings[i] = malloc(11);
        fscanf(dict, "%s", strings[i]);
    }

    double start_time;
    for (int i = 1; i <= n_words; i++) {
        tree = tst_insert(tree, strings[i]);
        if (i % tmp_step == 0) {
            start_time = wtime();
            for (int j = tmp_step; j > 0; j--)
                tree = tst_delete(tree, strings[j]);            
            fprintf(data, "%d,%lf\n", i, wtime() - start_time);
            tmp_step += step;
            i = 1;
            if (tmp_step > n_words)
                break;
        }
    }

    for (int i = 1; i <= n_words; i++)
        free(strings[i]);
    free(strings);
    fclose(dict);
    fclose(data);
}

void random_lookup_time_random_experiment()
{
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("./data/aboba.txt", "r");
    FILE* data = fopen("./experimental_data/random_lookup_time_random.txt", "w");

    fprintf(data, "n,t\n0,0\n");

    for (int i = 1; i <= n_words; i++) {
        strings[i] = malloc(11);
        fscanf(dict, "%s", strings[i]);
    }

    double start_time;

    for (int i = 1; i <= n_words; i++) {
        tree = tst_insert(tree, strings[i]);
        if (i % step == 0) {
            start_time = wtime();
            for (int j = 1; j <= i; j++)
                tst_lookup(tree, strings[j]);
            fprintf(data,
                    "%d,%.10lf\n",
                    i,
                    (wtime() - start_time) / i);
        }
    }

    for (int i = 1; i <= n_words; i++)
        free(strings[i]);
    free(strings);
    fclose(dict);
    fclose(data);
    tst_delete_tree(tree);
}

void random_lookup_time_sorted_experiment()
{
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("./data/sorted_aboba.txt", "r");
    FILE* data = fopen("./experimental_data/random_lookup_time_sorted.txt", "w");

    fprintf(data, "n,t\n0,0\n");

    for (int i = 1; i <= n_words; i++) {
        strings[i] = malloc(11);
        fscanf(dict, "%s", strings[i]);
    }

    double start_time;

    for (int i = 1; i <= n_words; i++) {
        tree = tst_insert(tree, strings[i]);
        if (i % step == 0) {
            start_time = wtime();
            for (int j = 1; j <= i; j++)
                tst_lookup(tree, strings[j]);
            fprintf(data,
                    "%d,%.10lf\n",
                    i,
                    (wtime() - start_time) / i);
        }
    }

    for (int i = 1; i <= n_words; i++)
        free(strings[i]);
    free(strings);
    fclose(dict);
    fclose(data);
    tst_delete_tree(tree);
}

void last_lookup_time_random_experiment()
{
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("./data/aboba.txt", "r");
    FILE* data = fopen("./experimental_data/last_lookup_time_random.txt", "w");

    fprintf(data, "n,t\n0,0\n");

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
                tst_lookup(tree, strings[i]);
            fprintf(data,
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

void last_lookup_time_sorted_experiment()
{
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("./data/sorted_aboba.txt", "r");
    FILE* data = fopen("./experimental_data/last_lookup_time_sorted.txt", "w");

    fprintf(data, "n,t\n0,0\n");

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
                tst_lookup(tree, strings[i]);
            fprintf(data,
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

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}