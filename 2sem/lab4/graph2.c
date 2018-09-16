#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

#define N 10
#define NUM 5

int min(int a, int b){
	if(a <= b){
		return a;
	} else{
		return b;
	}
}

int main(int argc, char ** argv){
	int *** mas = (int ***)malloc(N * sizeof(int **));
	for (int i = 0; i < N; ++i){
		mas[i] = (int **)malloc(N * sizeof(int *));
		for (int j = 0; j < N; ++j){
			mas[i][j] = (int *)malloc(N * sizeof(int));
			for (int k = 0; k < N; ++k){
				mas[i][j][k] = 1000;
			}
		}
	}
	
	struct intList *** ways = (struct intList ***)malloc(N * sizeof(struct intList **));
	for (int i = 0; i < N; ++i){
		ways[i] = (struct intList **)calloc(N, sizeof(struct intList *));
		for (int j = 0; j < N; ++j){
			IntList_push(&ways[i][j], i);
		}
	}

	FILE * f = fopen(argv[1], "r");
	if(f == 0){
		printf("Error File\n");
		return -1;
	}

	int d1 = 0, d2 = 0, d3 = 0;
	while(fscanf(f, "%d %d %d", &d1, &d2, &d3) == 3){
		mas[d1][d2][0] = d3;
	}
	fclose(f);

	for (int k = 1; k <= NUM; ++k){
		for (int i = 0; i < N; ++i){
			for (int j = 0; j < N; ++j){
				mas[i][j][k] = min(mas[i][j][k-1], mas[i][k][k-1] + mas[k][j][k-1]);
				printf("%d\t", mas[i][j][k]);
				///////////////////
				if(mas[i][j][k] != mas[i][j][k-1]){
					ways[i][j] = IntList_merge(ways[i][k], ways[k][j]);
				}
			}
			printf("\n");
		}
		printf("\n");
	}

	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j){
			IntList_push(&ways[i][j], j);
		}
	}

	printf("Way : "); IntList_print(ways[1][6]);
	printf("Ansver : %d\n", mas[1][6][5]);

	return 0;
}