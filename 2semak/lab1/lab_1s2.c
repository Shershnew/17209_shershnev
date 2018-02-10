#include <stdio.h>

#define WIDTH 9

int find(int gr[][WIDTH]){
	int t = 0;
	for (int i = 0; i < WIDTH; ++i){
		t = 0;
		for (int j = 0; j < WIDTH; ++j){    
			if(gr[j][i] != 0){              
				t = 1;                     
				break;
			}
		}
		if(t == 0){
			return i;
		}
	}
	return -1;
}

void delandprint(int gr[][WIDTH], int col){
	printf("%d ", col);
	for (int i = 0; i < WIDTH; ++i){
		gr[i][col] = -1;
	}
	for (int i = 0; i < WIDTH; ++i){
		if(gr[col][i] != -1){
			gr[col][i] = 0;	
		}
	}
}

int main(){
	int graph[WIDTH][WIDTH] = {0};
	int tec = 0;
	graph[0][3] = 1;
	graph[1][2] = 1;
	graph[3][2] = 1;
	graph[3][7] = 1;
	graph[4][0] = 1;
	graph[4][3] = 1;
	graph[5][1] = 1;
	graph[6][2] = 1;
	graph[7][5] = 1;
	graph[8][3] = 1;
	graph[8][6] = 1;  
	// graph[6][8] = 1;  
	int t = 1;
		while((tec = find(graph)) != -1){
			delandprint(graph, tec);
			t++;
		}
	if(t < WIDTH){
		printf("\n cikl");
	}
	return 0;
}