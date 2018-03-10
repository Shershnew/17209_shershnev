#pragma once

#define NAMESIZE 50
#define BUFSIZE 30

struct Ht_data{
	char name[NAMESIZE]; //for hesh
	int node;
	struct intList * list;
	int was_print;
};

struct Hash_table{
	struct Ht_data ** Ht_data;
	long long buf_size;
	int size;
};

struct Ht_data * Ht_get(struct Hash_table * ht, int num);
void Ht_set(struct Hash_table * ht, struct Ht_data * data);
void Ht_free(struct Hash_table * ht);
struct Hash_table * Ht_init();
