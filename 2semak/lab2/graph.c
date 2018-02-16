#include "hashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char ** argv){
	FILE * f = fopen(argv[1], "r");
	clock_t start = clock();
	struct data_base * db = read(f);
	fclose(f);
	if(db->buf_size == 0){
		printf("error read\n");
		return -1;
	} else{
		clock_t finish = clock();
		printf("Read %f seconds\n", ((float)(finish - start)) / CLOCKS_PER_SEC);
	}



	struct intList *queue = 0;
	while(db->list != 0){
		int pop_int = pop_first(&db->list);
		if(db->Htable[find(db, pop_int)]->was_print != 5){
			printf("\n");
			pushtoIntList(&queue, pop_int);
		} else{
			continue;
		}
		db->Htable[find(db, queue->data)]->was_print = 5;
		while(queue != 0){
			int tec = pop_first(&queue);
			printf("%d -- ", tec);
			int key = find(db, tec);
			if(key != -1){
				struct intList * p = db->Htable[key]->list;
				do{
					int key2 = find(db, p->data);
					if(key2 == -1){
						pushtoIntList(&queue, p->data);
					} else if(db->Htable[key2]->was_print != 5){
						pushtoIntList(&queue, p->data);
						db->Htable[key2]->was_print = 5;
					}
					p = p->next;
				} while(p != 0);
			}
		}
	}
	return 0;
}