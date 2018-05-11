#pragma once
#include <stdio.h>
#include "Htable.h"
#include "lists.h"

struct graph_base{
	struct Hash_table * ht;
	struct intList * list;
};

struct graph_base * read_graph(FILE * f);
void free_graph(struct graph_base * gb);
void printGraphToWidth(struct graph_base * gb);
void printGraphWayFrom(struct graph_base * gb, int node);