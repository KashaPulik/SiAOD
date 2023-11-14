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
void prefix_search_experiment();

int main()
{
    char input = 0;
    tst* tree = NULL;
    char string[128];
    while (input != '0') {
        printf("It's my super program to demonstrate ternary search tree\n");
        printf("Choose option or press 0 to exit\n");
        printf("(Press 'Enter' for the second time after every operation)\n");
        printf("Option list:\n");
        printf("1. Create new tree (your old tree will be deleted)\n");
        printf("2. Insert key to your tree\n");
        printf("3. Print all inserted keys\n");
        printf("4. Delete key\n");
        printf("5. Load keys to tree from file\n");
        printf("6. Make prefix search\n");
        printf("7. Update experimental data\n");
        input = getchar();
        while (getchar() != '\n')
            ;
        switch (input) {
        case '0':
            tst_delete_tree(tree);
            break;
        case '1':
            tst_delete_tree(tree);
            tree = NULL;
            break;
        case '2':
            printf("Enter key: ");
            fgets(string, 100, stdin);
            string[strlen(string) - 1] = '\0';
            tree = tst_insert(tree, string);
            getchar();
            break;
        case '3':
            tst_print_all_words(tree);
            getchar();
            break;
        case '4':
            printf("Enter key: ");
            fgets(string, 100, stdin);
            string[strlen(string) - 1] = '\0';
            tree = tst_delete(tree, string);
            getchar();
            break;
        case '5':
            printf("Enter filename: ");
            fgets(string, 100, stdin);
            string[strlen(string) - 1] = '\0';
            FILE* file = fopen(string, "r");
            if (file == NULL) {
                printf("Can't open file :(\n");
                getchar();
                break;
            }
            char key[128];
            int i = 0;
            while (fscanf(file, "%s", key) != EOF) {
                tree = tst_insert(tree, key);
                i++;
            }
            fclose(file);
            printf("%d keys were added to the tree\n", i);
            getchar();
            break;
        case '6':
            printf("Enter the prefix: ");
            fgets(string, 100, stdin);
            string[strlen(string) - 1] = '\0';
            tst_prefix_search(tree, string);
            getchar();
            break;
        case '7':
            insertion_time_experiment();
            deleting_time_experiment();
            lookup_time_experiment();
            printf("Data has been updated\n\n");
            break;
        }
    }
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

void prefix_search_experiment()
{
    tst* tree = NULL;
    char** strings = malloc(sizeof(char*) * (n_words + 1));
    FILE* dict = fopen("aboba.txt", "r");

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