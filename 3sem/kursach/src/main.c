#include "experimental_funcs.h"
#include "tst.h"

int main()
{
    srand(time(0));
    char input = 0;
    tst* tree = NULL;
    char string[128];
    double time;
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
            time = wtime();
            tst_delete_tree(tree);
            tree = NULL;
            printf("All tree was deleted in %.7lf seconds\n", wtime() - time);
            getchar();
            break;
        case '2':
            printf("Enter key: ");
            fgets(string, 100, stdin);
            string[strlen(string) - 1] = '\0';
            time = wtime();
            tree = tst_insert(tree, string);
            printf("Key '%s' was added in %.7lf seconds\n",
                   string,
                   wtime() - time);
            getchar();
            break;
        case '3':
            time = wtime();
            tst_print_all_words(tree);
            printf("All keys were printed in %.7lf seconds\n", wtime() - time);
            getchar();
            break;
        case '4':
            printf("Enter key: ");
            fgets(string, 100, stdin);
            string[strlen(string) - 1] = '\0';
            time = wtime();
            tree = tst_delete(tree, string);
            printf("Key '%s' was deleted in %.7lf seconds\n",
                   string,
                   wtime() - time);
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
            time = wtime();
            while (fscanf(file, "%s", key) != EOF) {
                tree = tst_insert(tree, key);
                i++;
            }
            printf("%d keys were added to the tree in %.7lf seconds\n",
                   i,
                   wtime() - time);
            fclose(file);
            getchar();
            break;
        case '6':
            printf("Enter the prefix: ");
            fgets(string, 100, stdin);
            string[strlen(string) - 1] = '\0';
            time = wtime();
            tst_prefix_search(tree, string);
            printf("All keys were finded in %.7lf seconds\n", wtime() - time);
            getchar();
            break;
        case '7':
            time = wtime();
            deleting_from_last_time_random_experiment();
            deleting_from_last_time_sorted_experiment();
            random_insertion_time_experiment();
            sorted_insertion_time_experiment();
            random_lookup_time_random_experiment();
            random_lookup_time_sorted_experiment();
            last_lookup_time_random_experiment();
            last_lookup_time_sorted_experiment();
            printf("Data has been updated in %f seconds\n\n", wtime() - time);
            getchar();
            break;
        }
    }
}