#include "experimental_funcs.h"
#include "tst.h"

int n_words = 1000000;
int step = 1000;
int n_iterations = 1000000;

void random_insertion_time_experiment()
{
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("./data/aboba.txt", "r");
    FILE* data = fopen("./experimental_data/random_insertion_time.txt", "w");
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

void sorted_insertion_time_experiment()
{
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("./data/sorted_aboba.txt", "r");
    FILE* data = fopen("./experimental_data/sorted_insertion_time.txt", "w");
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

void deleting_from_last_time_experiment()
{
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("./data/aboba.txt", "r");
    FILE* data = fopen("./experimental_data/deleting_from_last_time.txt", "w");
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

    tst_print_all_words(tree);

    for (int i = 1; i <= n_words; i++)
        free(strings[i]);
    free(strings);
    fclose(dict);
    fclose(data);
}

void deleting_from_first_time_experiment()
{
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("./data/aboba.txt", "r");
    FILE* data = fopen("./experimental_data/deleting_from_first_time.txt", "w");
    double start_time = wtime();
    fprintf(data, "n,t\n");
    double eliminated_time;
    for (int i = 1; i <= n_words; i++) {
        strings[i] = malloc(11);
        fscanf(dict, "%s", strings[i]);
    }

    for (int i = 1; i <= n_words; i++)
        tree = tst_insert(tree, strings[i]);

    for (int i = 1; i <= n_words; i++) {
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

void random_lookup_time_experiment()
{
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("./data/aboba.txt", "r");
    FILE* data = fopen("./experimental_data/random_lookup_time.txt", "w");

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

void last_lookup_time_experiment()
{
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("./data/aboba.txt", "r");
    FILE* data = fopen("./experimental_data/last_lookup_time.txt", "w");

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
                tst_lookup(tree, strings[i]);
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

void prefix_search_experiment()
{
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("./data/aboba.txt", "r");

    for (int i = 1; i <= n_words; i++) {
        strings[i] = malloc(11);
        fscanf(dict, "%s", strings[i]);
    }
    for (int i = 1; i <= n_words; i++)
        tree = tst_insert(tree, strings[i]);

    char slovo[11];
    printf("Enter prefix: ");
    while (scanf("%s", slovo)) {
        printf("\n");
        tst_prefix_search(tree, slovo);
        printf("\n");
        printf("Enter prefix: ");
    }

    for (int i = 1; i <= n_words; i++)
        free(strings[i]);
    free(strings);
    fclose(dict);
    tst_delete_tree(tree);
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void test()
{
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("./data/words.txt", "r");
    for (int i = 1; i <= n_words; i++) {
        strings[i] = malloc(50);
        strings[i][0] = '\0';
        fscanf(dict, "%s", strings[i]);
    }
    for (int i = 1; strings[i][0] != '\0'; i++)
        tree = tst_insert(tree, strings[i]);
    for (int i = 1; strings[i][0] != '\0'; i++)
        if(!tst_lookup(tree, strings[i]))
            printf("Oops!\n\n\n\n");
    for (int i = 1; i <= n_words; i++)
        free(strings[i]);
    free(strings);
    fclose(dict);
    tst_delete_tree(tree);
}