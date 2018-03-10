#pragma once
#include <stdio.h>
#include "Htable.h"

struct intList{
	int data;
	struct intList * next;
};

struct graph_base{
	struct Hash_table * ht;
	struct intList * list;
};

struct graph_base * read_graph(FILE * f);
void printGraphToWidth(struct graph_base * gb);