#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int getrand(int a, int b){
	return a + (rand() % (b - a));
}

int main(){
	srand(time(NULL));
	FILE *f = fopen("dbff.txt", "w");//97 122
	// for (long long i = 0; i < 1000000; ++i){
	// 	for (int j = 0; j < getrand(2, 10); ++j){
	// 		fprintf(f, "%c", (char)getrand(97, 122));
	// 	}
	// 	fprintf(f, " %d %d\n", getrand(0, 100), getrand(0, 100));
	// }
	for (int i = 0; i < 1000000; ++i){
		fprintf(f, "%lf ", (double)getrand(0, 10000) / 100.0);
	}
	fclose(f);
	return 0;
}