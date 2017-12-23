// #include <stdio.h>
// #include <time.h>
// #include <stdlib.h>
// #include <string.h>
#include "mergesort.h"

// void qsortt(void * arr, int size_arr, int size_type,
//  int (*cmp)(void * aa, void * bb),
//  int typesort) {
// 	int i = 0;
// 	int j = size_arr;
// 	if(size_arr >= 1){
// 		while(i <= j){
// 			while(-1 * typesort == cmp((char *)arr + i * size_type, (char *)arr)){
// 				i++;
// 			}
// 			while(1 * typesort == cmp((char *)arr + j * size_type, (char *)arr)){
// 				j--;
// 			}
// 			if(i <= j){
// 				void * c = malloc(size_type);
// 				memcpy(c, arr + i * size_type, size_type);
// 				memcpy(arr + i * size_type, arr + j * size_type, size_type);
// 				memcpy(arr + j * size_type, c, size_type);
// 				free(c);
// 				i++;
// 				j--;
// 			}
// 		}
// 	} else {
// 		return;
// 	}
// 	qsortt(arr, i-1, size_type, cmp, typesort);
// 	qsortt(arr + i * size_type, size_arr - i, size_type, cmp, typesort);
// }

// int read(struct file_list ** head, FILE * f, int count, int typesort, int size_type,
//  void (*swap)(void * arrr, int a, int b),
//  int (*cmp)(void * aa, void * bb),
//  void (*getff)(FILE * f, void * arr_r, int * arr_err, int num_err),
//  void (*putff)(FILE * f, void * a)){

// 	*head = (struct file_list *)malloc(sizeof(struct file_list));
// 	(*head)->next = 0;
// 	int last = 0;
// 	void * arr = malloc(SIZE_FOR_QSORT * size_type);
// 	int stop_read = 0;
// 	int err_r = 0;
// 	int i = 0;
// 	for ( i = 0; i < SIZE_FOR_QSORT; ++i){
// 		getff(f, (char *)arr + i * size_type, &err_r, 0);
// 		if(-1 == err_r){
// 			last = i-1;
// 			stop_read = 1;
// 			break;
// 		}
// 	}
// 	if(!stop_read){
// 		last = SIZE_FOR_QSORT - 1;
// 	}
// 	qsortt(arr, last, size_type, cmp, typesort);
// 	for (int j = 0; j < 8; ++j){
// 		(*head)->name[j] = "sortfile"[j];
// 	}
// 	(*head)->name[6] = '0'+ (count/10000)%10;
// 	(*head)->name[7] = '0'+ (count/1000)%10;
// 	(*head)->name[8] = '0'+ (count/100)%10;
// 	(*head)->name[9] = '0'+ (count/10)%10;
// 	(*head)->name[10] = '0'+ (count)%10;
// 	(*head)->name[11] = '\0';
// 	FILE * fpr = fopen((*head)->name, "w");
// 	for (i = 0; i <= last; ++i){
// 		putff(fpr, (char *)arr + i * size_type);
// 	}
// 	fclose(fpr);
// 	free(arr);
// 	int countt = 1;
// 	if(!stop_read){
// 		countt += read(&((*head)->next), f, count + 1, typesort, size_type, swap, cmp, getff, putff);
// 	}
// 	return countt;
// }

// int find_el_and_write(void * arr_r, int * arr_err, FILE ** arr_f, FILE * result_file, int size_type, int file_count, int typesort,
//  int (*cmp)(void * aa, void * bb),
//  void (*getff)(FILE * f, void * arr_r, int * arr_err, int num_err),
//  void (*putff)(FILE * f, void * a)){

// 	int err_r = 0;
// 	void * min_or_max = calloc(size_type, 1);
// 	int first = 0;
// 	int num_el_for_push = -1;
// 	for (first = 0; first < file_count; ++first){
// 		if(arr_err[first] == 0){
// 			memcpy(min_or_max, (char *)arr_r + first * size_type, size_type);
// 			num_el_for_push = first;
// 			break;
// 		}
// 	}
// 	for (int i = first + 1; i < file_count; ++i){
// 		if(arr_err[i] == 0){
// 			if(cmp(min_or_max, (char *)arr_r + i * size_type) == typesort){
// 				memcpy(min_or_max, (char *)arr_r + i * size_type, size_type);
// 				num_el_for_push = i;
// 			}
// 		}
// 	}
// 	if(-1 == num_el_for_push){
// 		free(min_or_max);
// 		return -1;
// 	}
// 	putff(result_file, min_or_max);
// 	getff(arr_f[num_el_for_push], (char *)arr_r + num_el_for_push * size_type, arr_err, num_el_for_push);
// 	free(min_or_max);
// 	return 0;
// }

// void merge_sortt(FILE * f, int typesort, int size_type,
//  void (*swap)(void * arrr, int a, int b),
//  int (*cmp)(void * aa, void * bb),
//  void (*getff)(FILE * f, void * arr_r, int * arr_err, int num_err),
//  void (*putff)(FILE * f, void * a)){

// 	struct file_list * file_base = 0;
// 	int file_count = read(&file_base, f, 0, typesort, size_type, swap, cmp, getff, putff);
// 	FILE * result_file = fopen("result.txt", "w");
// 	struct file_list * pointer = file_base;
// 	void * arr_r = malloc(file_count * size_type);
// 	int * arr_err = (int *)calloc(file_count, sizeof(int));
// 	FILE ** arr_f = (FILE **)malloc(file_count * sizeof(FILE *));
// 	int i = 0;
// 	while(pointer != 0){
// 		arr_f[i] = fopen(pointer->name, "r");
// 		getff(arr_f[i], (char *)arr_r + i * size_type, arr_err, i);
// 		i++;
// 		pointer = pointer->next;
// 	}
// 	int find_stat = 0;
// 	while(0 == find_stat){
// 		find_stat = find_el_and_write(arr_r, arr_err, arr_f, result_file, size_type, file_count, typesort, cmp, getff, putff);
// 	}
// 	for(int k = 0; k < file_count; k++){
// 		fclose(arr_f[k]);
// 	}
// 	pointer = file_base;
// 	while(pointer != 0){
// 		remove(pointer->name);
// 		struct file_list * for_del = pointer;
// 		pointer = pointer->next;
// 		free(for_del);
// 	}
// 	fclose(result_file);
// 	free(arr_r);
// 	free(arr_err);
// 	free(arr_f);
// }

void swap(void * arrr, int a, int b){
	double * arr = (double *)arrr;
	double c = arr[a];
	arr[a] = arr[b];
	arr[b] = c;
}

int cmp(void * aa, void * bb){
	double * a = (double *)aa;
	double * b = (double *)bb;
	unsigned char * z1 = (unsigned char *)a;
	unsigned char * z2 = (unsigned char *)b;
	if(*(z1+7) >> 7 == *(z2+7) >> 7){
		if(*a > *b)
			return 1;
		else if(*a < *b)
			return -1;
		else
			return 0;
	} else{
		return (*(z2+7) >> 7) - (*(z1+7) >> 7);
	}
}

void getff(FILE * f, void * arr_r, int * arr_err, int num_err){
	int err = fscanf(f, "%lf", (double *)arr_r);
	if(-1 == err){
		arr_err[num_err] = -1;
	}
}

void putff(FILE * f, void * a){
	double * r = (double *)a;
	fprintf(f, "%lf ", *r);
}

int main(int argc, char **argv){
	FILE * f = fopen(argv[1], "r");
	if(NULL == f){
		printf("error read\n");
		return -1;
	}
	int typesort = 1;
	if(argv[2][0] == '>'){
		typesort = -1;
	}
	clock_t start = clock();
	merge_sortt(f, typesort, sizeof(double), &swap, &cmp, &getff, &putff);
	clock_t finish = clock();
	printf("Read %f seconds\n", ((float)(finish - start)) / CLOCKS_PER_SEC);
	return 0;
}