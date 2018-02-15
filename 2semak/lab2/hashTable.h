#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NAMESIZE 50
#define BUFSIZE 30

struct intList{
	int data;
	struct intList * next;
};

struct data_base{
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

struct data_base * read(FILE * f);
int find(struct data_base *db, int num);
int pop_first(struct intList ** l);
void pushtoIntList(struct intList ** l, int num);