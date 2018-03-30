#include <stdio.h>
#include "LRU_cache.h"

void printll(struct LRU * lru){
	struct Ht_data * p = lru->head;
	while(p != 0){
		printf("%d -- next %d  pref %d\n", p->data == 0 ? 0 : p->data, p->next == 0 ? 0 : p->next->data, p->pref == 0 ? 0 : p->pref->data);
		p = p->next;
	}
	printf("tail %d\n", lru->tail == 0 ? 0 : lru->tail->data);
	printf("-------------------------------\n");
}

int main(){
	struct LRU * lru = cache_init(3);
	cache_put(lru,1,5);
	printll(lru);
	cache_put(lru,2,6);
	printll(lru);
	cache_get(lru,1);
	printll(lru);
	cache_remove_el(lru, 1);
	printll(lru);
	cache_put(lru,3,7);
	printll(lru);
	cache_put(lru,4,8);
	printll(lru);
	cache_put(lru,5,9);
	printll(lru);

	cache_remove(lru);
	return 0;
}