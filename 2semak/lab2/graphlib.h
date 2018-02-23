#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMESIZE 50
#define BUFSIZE 30

struct intList{
	int data;
	struct intList * next;
};

struct graph_base{
	struct data ** Htable;
	long long buf_size;
	int size;
	struct intList * list;
};

struct data{
	char name[NAMESIZE];
	int d1;
	struct intList * list;
	int was_print;
};

struct graph_base * read_graph(FILE * f);
int find(struct graph_base *db, int num);
void printGraphFromHtableToWidth(struct graph_base * db);