#include "graphlib.h"
#include <string.h>
#include <stdlib.h>

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

		IntList_push(&gb->list, node1);
		IntList_push(&gb->list, node2);

		d = Ht_get(gb->ht, node1);
		if(d == 0){
			d = (struct Ht_data *)calloc(1, sizeof(struct Ht_data));
			itoa(node1, d->name, 10);
			d->node = node1;
			IntList_push(&(d->list), node2);
			Ht_set(gb->ht, d);
		} else{
			IntList_push(&(d->list), node2);
			Ht_set(gb->ht, d);
		}

		d = Ht_get(gb->ht, node2);
		if(d == 0){
			d = (struct Ht_data *)calloc(1, sizeof(struct Ht_data));
			itoa(node2, d->name, 10);
			d->node = node2;
			IntList_push(&(d->list), node1);
			Ht_set(gb->ht, d);
		} else{
			IntList_push(&(d->list), node1);
			Ht_set(gb->ht, d);
		}

	}
	return gb;
}

void free_graph(struct graph_base * gb){
	Ht_free(gb->ht);	
	IntList_free(gb->list);
	free(gb);
}

void printGraphToWidth(struct graph_base * gb){
	struct intList *queue = 0;
	while(gb->list != 0){
		int pop_int = IntList_pop_first(&gb->list); 
		if(Ht_get(gb->ht, pop_int)->was_print != 5){
			printf("\n");
			IntList_push(&queue, pop_int);
			Ht_get(gb->ht, queue->data)->was_print = 5;
		} else{
			continue;
		} 
		while(queue != 0){
			int tec = IntList_pop_first(&queue);
			printf("%d --- ", tec);
			struct Ht_data * htd = Ht_get(gb->ht, tec);
			if(htd != 0){
				struct intList * p = htd->list;
				while(p != 0){
					struct Ht_data * htd2 = Ht_get(gb->ht, p->data);
					if(htd2->was_print != 5){
						IntList_push(&queue, p->data);
						htd2->was_print = 5;
					}
					p = p->next;
				}
			}
		}
	}
}


int find_else_way(struct graph_base * gb, struct intList * way){
	struct intList * p = way;
	struct Ht_data * dt;
	while(p != 0){
		dt = Ht_get(gb->ht, p->data);
		if(dt != 0 && dt->list != 0){
			return p->data;
		}
		p = p->next;
	}
	return -1;
}

void printGraphWayFrom(struct graph_base * gb, int node){
	struct intList * ring = 0;
	IntList_push(&ring, node);
	struct intList * p = ring;
	struct Ht_data * dt;
	int sosed = -1;
	int tec = 0;
	int t2;
	while(1){
		tec = find_else_way(gb, p);
		sosed = -1;
		t2 = tec;
		if(tec == -1){
			break;
		}
		p = IntList_get_ondata(p, tec);
		dt = Ht_get(gb->ht, tec);
		int c = 0;
		while(sosed != tec){
			sosed = IntList_pop_first(&(dt->list));
			IntList_pop_ondata(&(Ht_get(gb->ht, sosed)->list), t2);
			t2 = sosed;
			IntList_push_from(&p, sosed, c);
			c++;
			dt = Ht_get(gb->ht, sosed);
		}
	} 
	IntList_print(ring);
}