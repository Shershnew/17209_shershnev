#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_map(unsigned char ** map, int s, int n){
	for (int i = 0; i < s; ++i){
		for (int j = 0; j < n; ++j){
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

double h(int x, int y, int rx, int ry){
	return sqrt(pow(x - rx, 2) + pow(y - ry, 2));
}

int main(){
	FILE * f = fopen("input.txt", "r");
	int s,n;
	fscanf(f, "%d %d\n", &s, &n);
	unsigned char ** map = (unsigned char **)calloc(s, sizeof(unsigned char *));
	for (int i = 0; i < s; ++i){
		map[i] = (unsigned char *)calloc(n, sizeof(unsigned char));
	}
	for (int i = 0; i < s; ++i){
		for (int j = 0; j < n; ++j){
			fscanf(f, "%c", &map[i][j]);
			if(map[i][j] != '1' && map[i][j] != '0'){
				// j--;
				printf("%d %d\n", i,j);
			}
		}
		char m;
		fscanf(f, "%c", &m);
	}
	fclose(f);

	int ** map_d = (int **)malloc(s * sizeof(int *));
	for (int i = 0; i < s; ++i){
		map_d[i] = (int *)malloc(n * sizeof(int));
		for (int j = 0; j < n; ++j){
			map_d[i][j] = -1;
		}
	}

	print_map(map, s, n);
	printf("%lf\n", h(9, 0, 0 ,9));
	return 0;
}