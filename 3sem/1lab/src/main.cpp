#include <iostream>
#include <fstream>

#include <experimental_funcs.hpp>
#include <rbtree_api.hpp>

#define N_ITERATIONS 1000
#define N_KEYS 1000000
#define STEP 1000

int main()
{
    srand(time(0));

    rbtree* tree = init_tree(1);

    std::ofstream file("./data/data.csv");

    file << "n,t\n";

    double time;

    for(int i = 2; i <= N_KEYS; i++) {
        tree = rbtree_insert(tree, create_node(i));
        if(i % STEP == 0) {
            time = wtime();
            for(int j = 0; j < N_ITERATIONS; j++) {
                rbtree_lookup(tree, getrand(1, i));
            }
            time = (wtime() - time) / N_ITERATIONS;
            file << i << "," << time << "\n";
        }
    }
    rbtree_free(tree);
}