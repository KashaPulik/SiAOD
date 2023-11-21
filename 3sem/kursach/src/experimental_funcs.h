#pragma once

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

void random_insertion_time_experiment();
void sorted_insertion_time_experiment();
void deleting_from_last_time_random_experiment();
void deleting_from_last_time_sorted_experiment();
void random_lookup_time_random_experiment();
void random_lookup_time_sorted_experiment();
double wtime();