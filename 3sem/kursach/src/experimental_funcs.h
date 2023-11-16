#pragma once

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

void random_insertion_time_experiment();
void sorted_insertion_time_experiment();
void deleting_from_last_time_experiment();
void deleting_from_first_time_experiment();
void random_lookup_time_experiment();
void last_lookup_time_experiment();
void prefix_search_experiment();
double wtime();
void test();