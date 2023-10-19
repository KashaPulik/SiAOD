#include <fstream>
#include <iostream>
#include <sched.h>

#include <experimental_funcs.hpp>
// #include <rbtree_hidden.hpp>
#include <rbtree_api.hpp>

#define N_ITERATIONS 1000
#define N_KEYS 50000
#define STEP 5

rbtree* rbtree_delete_fixup(rbtree* T, rbtree* x);

void first_case()
{
    rbtree* tree = init_tree(0);
    for (int i = 1; i < 30; i++)
        tree = rbtree_insert(tree, create_node(i));
    std::cout << "first_case-----------------------------------------------\n";
    // rbtree_print(tree->left);
    tree->left->color = BLACK;
    tree->left->right->color = RED;
    // std::cout << "-------------------------------------------\n";
    rbtree_print(tree->left);
    tree = rbtree_delete_fixup(tree, tree->left->left);
    std::cout << "---------------------------------------------------------\n";
    rbtree_print(tree->left);
    rbtree_free(tree);
}

void second_case()
{
    rbtree* tree = init_tree(0);
    for (int i = 1; i < 30; i++)
        tree = rbtree_insert(tree, create_node(i));
    std::cout << "second_case----------------------------------------------\n";
    // rbtree_print(tree->left);
    tree->left->color = RED;
    // std::cout << "-------------------------------------------\n";
    rbtree_print(tree->left);
    tree = rbtree_delete_fixup(tree, tree->left->left);
    std::cout << "---------------------------------------------------------\n";
    rbtree_print(tree->left);
    rbtree_free(tree);
}

void third_case()
{
    rbtree* tree = init_tree(0);
    for (int i = 1; i < 20; i++)
        tree = rbtree_insert(tree, create_node(i));
    std::cout << "third_case-----------------------------------------------\n";
    // rbtree_print(tree->left);
    tree->left->color = RED;
    tree->left->right->left->color = RED;
    // std::cout << "-------------------------------------------\n";
    rbtree_print(tree->left);
    tree = rbtree_delete_fixup(tree, tree->left->left);
    std::cout << "---------------------------------------------------------\n";
    rbtree_print(tree->left);
    rbtree_free(tree);
}

void fourth_case()
{
    rbtree* tree = init_tree(0);
    for (int i = 1; i < 30; i++)
        tree = rbtree_insert(tree, create_node(i));
    std::cout << "fourth_case----------------------------------------------\n";
    // rbtree_print(tree->left);
    tree->left->color = RED;
    tree->left->right->left->color = RED;
    tree->left->right->right->color = RED;
    // std::cout << "-------------------------------------------\n";
    rbtree_print(tree->left);
    tree = rbtree_delete_fixup(tree, tree->left->left);
    std::cout << "---------------------------------------------------------\n";
    rbtree_print(tree->left);
    rbtree_free(tree);
}

void rbtree_insert_demonstrate()
{
    rbtree* tree = init_tree(11);
    tree = rbtree_insert(tree, create_node(2));
    tree = rbtree_insert(tree, create_node(14));
    tree = rbtree_insert(tree, create_node(1));
    tree = rbtree_insert(tree, create_node(7));
    tree = rbtree_insert(tree, create_node(15));
    tree = rbtree_insert(tree, create_node(5));
    tree = rbtree_insert(tree, create_node(8));
    rbtree_print(tree);
    tree = rbtree_insert(tree, create_node(4));
    rbtree_print(tree);
    tree = rbtree_delete(tree, 11);
    rbtree_print(tree);
    rbtree_free(tree);
}

void rbtree_delete_demonstrate()
{
}

int main()
{
    double program_time = wtime();
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);

    if (sched_setaffinity(0, sizeof(mask), &mask) == -1) {
        perror("sched_setaffinity");
        return 1;
    }

    srand(time(0));

    rbtree* tree = init_tree(1);

    std::ofstream file("./data/data.csv");

    file << "n,t\n";

    double time;

    for (int i = 2; i <= N_KEYS; i++) {
        tree = rbtree_insert(tree, create_node(i));
        if (i % STEP == 0) {
            time = wtime();
            for (int j = 0; j < N_ITERATIONS; j++) {
                // rbtree_lookup(tree, getrand(1, i));
                rbtree_lookup(tree, i);
            }
            time = (wtime() - time) / N_ITERATIONS;
            file << i << "," << time << "\n";
        }
    }
    rbtree_free(tree);
    std::cout << wtime() - program_time << std::endl;
    first_case();
    second_case();
    third_case();
    fourth_case();
    rbtree_insert_demonstrate();
}