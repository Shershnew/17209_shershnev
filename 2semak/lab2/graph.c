#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "graphlib.h"

int main(int argc, char ** argv){
	FILE * f = fopen(argv[1], "r");
	clock_t start = clock();
	struct graph_base * gr = read_graph(f);
	fclose(f);
	if(gr->ht->buf_size == 0){
		printf("error read\n");
		return -1;
	} else{
		clock_t finish = clock();
		printf("Read %f seconds\n", ((float)(finish - start)) / CLOCKS_PER_SEC);
	}
	printGraphToWidth(gr);
	return 0;
}