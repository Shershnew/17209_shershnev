#pragma once
#include "Htable.h"
#include "lists.h"

struct LRU{
	struct Hash_table * ht;
	struct Ht_data * head;
	struct Ht_data * tail;
	int size;
	int max_size;
};

struct LRU * cache_init(int size);
int cache_get(struct LRU * cache, int key);
void cache_put(struct LRU * cache, int key, int num);
void cache_remove_el(struct LRU * cache, int key);
void cache_remove(struct LRU * cache);