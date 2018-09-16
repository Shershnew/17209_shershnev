#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

struct graph{
	int ** graph;
	int ** graphnow;
	int x;
	int ist;
	int stk;
};

struct graph * readgraph(char * str){
	struct graph * g = (struct graph *)malloc(sizeof(struct graph));
	FILE * f = fopen(str, "r");
	int x,y;
	fscanf(f,"%d%d",&(g->ist),&(g->stk));
	fscanf(f,"%d",&x);
	g->x = x;
	g->graph = (int **)calloc(x, sizeof(int *));
	g->graphnow = (int **)calloc(x, sizeof(int *));
	for (int i = 0; i < x; ++i){
		g->graph[i] = (int *)calloc(x, sizeof(int));
		g->graphnow[i] = (int *)calloc(x, sizeof(int));
	}
	int a,b,c;
	while(3 == fscanf(f,"%d%d%d",&a,&b,&c)){
		g->graph[a][b] = c;
	}
	fclose(f);
	return g;
}

void printgraph(struct graph * g){
	for (int i = 0; i < g->x; ++i){
		for (int j = 0; j < g->x; ++j){
			printf("%d ", g->graph[j][i]);
		}
		printf("\n");
	}
	printf("\n----------\n");
	for (int i = 0; i < g->x; ++i){
		for (int j = 0; j < g->x; ++j){
			printf("%d ", g->graphnow[j][i]);
		}
		printf("\n");
	}
}

struct intList * getway(struct graph * g){
	struct intList * queue = 0;
	int * map = (int *)calloc(g->x, sizeof(int));
	IntList_push(&queue, g->ist);
	while(queue){
		int tec = IntList_pop_first(&queue);
		if(tec == g->stk){
			break;
		}
		for (int i = 0; i < g->x; ++i){
			if((g->graph[tec][i] != 0 || g->graph[i][tec] != 0) && map[i] == 0){
				if(g->graph[tec][i] != 0){
					if(g->graph[tec][i] - g->graphnow[tec][i] > 0){
						IntList_push(&queue, i);
						map[i] = tec;		
					}
				} else{
					if(g->graphnow[tec][i] > 0){
						IntList_push(&queue, i);
						map[i] = tec;	
					}
				}
			}
		}
	}
	if(map[g->stk] == 0){
		return 0;
	}
	struct intList * r = 0;
	int p = g->stk;
	IntList_push(&r, g->stk);
	while(1){
		IntList_push(&r, map[p]);
		p = map[p];
		if(p == g->ist){
			break;
		}
	}
	return r;
}

void fill_graph(struct graph * g, struct intList * l){
	int min = 99999;
	int tec = 0;
	struct intList * p = l;
	while(p->next != 0){
		if(g->graph[p->next->data][p->data] != 0){
			tec = g->graph[p->next->data][p->data] - g->graphnow[p->next->data][p->data];	
		} else{
			tec = g->graphnow[p->data][p->next->data];
		}
		if(min > tec){
			min = tec;
		}
		p = p->next;
	}
	p = l;
	while(p->next != 0){
		if(g->graph[p->next->data][p->data] != 0){
			g->graphnow[p->next->data][p->data] += min;
		} else{
			g->graphnow[p->next->data][p->data] -= min;
		}
		p = p->next;
	}
}

int main(int argc, char ** argv){
	struct graph * graph = readgraph(argv[1]);
	struct intList * l = getway(graph);
	while(l != 0){
		IntList_print(l);
		fill_graph(graph, l);
		l = getway(graph);
	}
	
	printgraph(graph);
	int sum = 0;
	for (int i = 0; i < graph->x; ++i){
		sum += graph->graphnow[i][graph->stk];
	}
	printf("ansver : %d\n", sum);
	return 0;
}