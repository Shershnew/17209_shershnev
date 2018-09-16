#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct queue{
	unsigned long long cost;
	unsigned long long priority;
	int x;
	int y;
	struct queue * next;
	struct queue ** neighbors;
	struct queue * from;
};

void print_queue(struct queue * head){
	if(head == 0){
		printf("NULL\n");
		return;
	}
	while(head != 0){
		printf("%d -- ", head->cost);
		head = head->next;
	}
	printf("\n");
}

void queue_put(struct queue ** head, struct queue * el){
	if(*head == 0){
		*head = el;
		return;
	} else{
		if((*head)->priority > el->priority){
			el->next = *head;
			*head = el;
			return;
		}
	}
	struct queue * p = *head;
	while(p->next != 0){
		if(p->next->priority > el->priority){
			el->next = p->next;
			p->next = el;
			return;
		}	
		p = p->next;
	}
	p->next = el;
	return;
}

struct queue * queue_pop(struct queue ** head){
	if(*head == 0){
		return 0;
	}
	struct queue * r = *head;
	*head = (*head)->next;
	return r;
}

void print_map(unsigned char ** map, int s, int n){
	for (int i = 0; i < s; ++i){
		for (int j = 0; j < n; ++j){
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

int heuristic(int x, int y, int rx, int ry){
	return abs(rx - x) + abs(ry - y);
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
		}
		char m;
		fscanf(f, "%c", &m);
	}
	fclose(f);
	print_map(map, s, n);

	struct queue *** graph = (struct queue ***)calloc(s, sizeof(struct queue **));
	for (int i = 0; i < s; ++i){
		graph[i] = (struct queue **)calloc(n, sizeof(struct queue *));
		for (int j = 0; j < n; ++j){
			graph[i][j] = (struct queue *)calloc(1, sizeof(struct queue));
			graph[i][j]->neighbors = (struct queue **)calloc(4, sizeof(struct queue *));
			graph[i][j]->cost = 9999;
			graph[i][j]->x = i;
			graph[i][j]->y = j;
		}
	}
	for (int i = 0; i < s; ++i){
		for (int j = 0; j < n; ++j){
			if(i > 0 && map[i-1][j] != '#')
			graph[i][j]->neighbors[0] = graph[i-1][j];
			if(i < s - 1 && map[i+1][j] != '#')
			graph[i][j]->neighbors[1] = graph[i+1][j];
			if(j > 0 && map[i][j-1] != '#')
			graph[i][j]->neighbors[2] = graph[i][j-1];
			if(j < n - 1 && map[i][j+1] != '#')
			graph[i][j]->neighbors[3] = graph[i][j+1];
		}
	}

	long long iter = 0;

	struct queue * frointer = 0;
	struct queue * current = 0;
	struct queue * goal = graph[7][9];
	struct queue * start = graph[0][0];
	start->cost = 0;
	queue_put(&frointer, start);
	while(frointer != 0){
		iter++;
		current = queue_pop(&frointer);
		if(current == goal){
			break;
		}
		for (int i = 0; i < 4; ++i){
			if(current->neighbors[i] != 0){
				unsigned long long new_cost = current->cost + map[current->neighbors[i]->x][current->neighbors[i]->y] - '0' + 1;
				if(new_cost < current->neighbors[i]->cost){
					current->neighbors[i]->cost = new_cost;
					current->neighbors[i]->priority = new_cost + heuristic(goal->x, goal->y, current->neighbors[i]->x, current->neighbors[i]->y);
					current->neighbors[i]->from = current;
					queue_put(&frointer, current->neighbors[i]);
				}
			}
		}
	}
	while(current != start){
		map[current->x][current->y] = '.';
		current = current->from;
	}
	map[start->x][start->y] = 's';
	map[goal->x][goal->y] = 'f';
	printf("\n");
	print_map(map, s, n);
	printf("iter = %d\n", iter);
	return 0;
}