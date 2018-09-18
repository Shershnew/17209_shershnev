#ifndef sdf
#define sdf

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_FOR_QSORT 3

void qsortt(void * arr, int size_arr, int size_type,
 int (*cmp)(void * aa, void * bb),
 int typesort);

void merge_sortt(FILE * f, int typesort, int size_type,
 void (*swap)(void * arrr, int a, int b),
 int (*cmp)(void * aa, void * bb),
 void (*getff)(FILE * f, void * arr_r, int * arr_err, int num_err),
 void (*putff)(FILE * f, void * a));

#endif