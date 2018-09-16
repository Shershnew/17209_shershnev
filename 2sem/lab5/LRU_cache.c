#include "LRU_cache.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct LRU * cache_init(int size){
	struct LRU * p = (struct LRU *)calloc(1,sizeof(struct LRU));
	p->ht = Ht_init();
	p->max_size = size;
	return p;
}

int cache_get(struct LRU * cache, int key){
	struct Ht_data * d = Ht_get(cache->ht, key);
	if(d == 0){
		return -1;
	}
	if(d == cache->tail){
		if(d->pref != 0){
			cache->tail = d->pref;	
		} else{
			cache->tail = 0;
		}	
	}
	if(d->pref != 0){
		d->pref->next = d->next;	
	}
	if(d->next != 0){
		d->next->pref = d->pref;
	}
	d->next = cache->head;
	d->pref = 0;
	cache->head->pref = d;
	cache->head = d;
	return d->data;
}

void cache_put(struct LRU * cache, int key, int num){
	struct Ht_data * data = (struct Ht_data *)calloc(1, sizeof(struct Ht_data));
	itoa(key, data->name, 10);
	data->data = num;
	Ht_set(cache->ht, data);
	if(cache->head != 0){
		cache->head->pref = data;
		data->next = cache->head;
	} else{
		cache->tail = data;
	}
	cache->head = data;
	if(cache->size == cache->max_size){
		cache->tail->pref->next = 0;
		struct Ht_data * del = cache->tail;
		cache->tail = cache->tail->pref;
		free(del);
		
	} else{
		cache->size++;
	}
}

void cache_remove_el(struct LRU * cache, int key){
	struct Ht_data * el = Ht_get(cache->ht, key);
	if(el == 0){
		return;
	}
	cache->size--;
	if(el->next == 0){
		cache->tail = el->pref;
	} else{
		el->next->pref = el->pref;
	}
	if(el->pref == 0){
		cache->head = el->next;
	} else{
		el->pref->next = el->next;
	}
	free(el);
}

void cache_remove(struct LRU * cache){
	Ht_free(cache->ht);
	free(cache);
}