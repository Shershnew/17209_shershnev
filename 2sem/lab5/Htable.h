#pragma once
#include "lists.h"

#define NAMESIZE 50
#define BUFSIZE 30

struct Ht_data{
	char name[NAMESIZE]; //for hаsh
	struct Ht_data * next;
	struct Ht_data * pref;
	int data;
};

struct Hash_table{
	struct Ht_data ** Ht_data;
	long long buf_size;
	int size;
};

struct Ht_data * Ht_get(struct Hash_table * ht, int key);
void Ht_set(struct Hash_table * ht, struct Ht_data * data);
void Ht_free_el(struct Hash_table * ht, int key);
void Ht_free(struct Hash_table * ht);
struct Hash_table * Ht_init();
