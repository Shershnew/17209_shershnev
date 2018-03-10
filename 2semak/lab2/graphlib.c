#include "graphlib.h"
#include <string.h>
#include <stdlib.h>

int pop_first(struct intList ** l){
	struct intList * p = (*l)->next;
	int ret = (*l)->data;
	free(*l);
	*l = p;
	return ret;
}

void pushtoIntList(struct intList ** l, int num){
	struct intList ** p = l;
	if(*p == 0){
		*p = (struct intList *)calloc(1, sizeof(struct intList));
		(*p)->data = num;
		(*p)->next = 0;
	} else {
		if((*p)->data == num){
				return;
		}
		while((*p)->next != 0){
			p = &(*p)->next;
			if((*p)->data == num){
				return;
			}
		}
		(*p)->next = (struct intList *)calloc(1, sizeof(struct intList));
		(*p)->next->data = num;
	}
}

void printlist(struct intList * l){
	while(l != 0){
		printf("%d -- ", l->data);
		l=l->next;
	}
	printf("\n");
}

struct graph_base * read_graph(FILE * f){
	struct graph_base * gb = (struct graph_base *)calloc(1, sizeof(struct graph_base));
	struct Ht_data * d;
	if(NULL == f){
		gb->ht->buf_size = 0;
		return gb;
	}

	gb->ht = Ht_init();
	
	while(1){
		int node1, node2;
		int er = fscanf(f, "%d %d", &node1, &node2);
		if(er != 2){
			break;
		}

		pushtoIntList(&gb->list, node1);
		pushtoIntList(&gb->list, node2);

		d = Ht_get(gb->ht, node1);
		if(d == 0){
			d = (struct Ht_data *)calloc(1, sizeof(struct Ht_data));
			itoa(node1, d->name, 10);
			d->node = node1;
			pushtoIntList(&(d->list), node2);
			Ht_set(gb->ht, d);
		} else{
			pushtoIntList(&(d->list), node2);
			Ht_set(gb->ht, d);
		}

		d = Ht_get(gb->ht, node2);
		if(d == 0){
			d = (struct Ht_data *)calloc(1, sizeof(struct Ht_data));
			itoa(node2, d->name, 10);
			d->node = node2;
			pushtoIntList(&(d->list), node1);
			Ht_set(gb->ht, d);
		} else{
			pushtoIntList(&(d->list), node1);
			Ht_set(gb->ht, d);
		}

	}
	return gb;
}


void printGraphToWidth(struct graph_base * gb){
	struct intList *queue = 0;
	while(gb->list != 0){
		int pop_int = pop_first(&gb->list); 
		if(Ht_get(gb->ht, pop_int)->was_print != 5){
			printf("\n");
			pushtoIntList(&queue, pop_int);
			Ht_get(gb->ht, queue->data)->was_print = 5;
		} else{
			continue;
		} 
		while(queue != 0){
			int tec = pop_first(&queue);
			printf("%d --- ", tec);
			struct Ht_data * htd = Ht_get(gb->ht, tec);
			if(htd != 0){
				struct intList * p = htd->list;
				while(p != 0){
					struct Ht_data * htd2 = Ht_get(gb->ht, p->data);
					if(htd2->was_print != 5){
						pushtoIntList(&queue, p->data);
						htd2->was_print = 5;
					}
					p = p->next;
				}
			}
		}
	}
}