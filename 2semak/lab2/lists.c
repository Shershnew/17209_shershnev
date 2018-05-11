#include "lists.h"
#include <stdlib.h>
#include <stdio.h>

int IntList_pop_first(struct intList ** l){
	struct intList * p = (*l)->next;
	int ret = (*l)->data;
	free(*l);
	*l = p;
	return ret;
}

void IntList_push(struct intList ** l, int num){
	struct intList ** p = l;
	if(*p == 0){
		*p = (struct intList *)calloc(1, sizeof(struct intList));
		(*p)->data = num;
		(*p)->next = 0;
	} else {
		// if((*p)->data == num){
		// 		return;
		// }
		while((*p)->next != 0){
			p = &(*p)->next;
			// if((*p)->data == num){
			// 	return;
			// }
		}
		(*p)->next = (struct intList *)calloc(1, sizeof(struct intList));
		(*p)->next->data = num;
	}
}

void IntList_push_from(struct intList ** l, int num, int counter){
	int count = counter;
	struct intList ** p = l;
	struct intList * p2 = 0;
	if(*p == 0){
		*p = (struct intList *)calloc(1, sizeof(struct intList));
		(*p)->data = num;
		(*p)->next = 0;
	} else {
		while((*p)->next != 0 && count != 0){
			count--;
			p = &(*p)->next;
		}
		p2 = (*p)->next;
		(*p)->next = (struct intList *)calloc(1, sizeof(struct intList));
		(*p)->next->data = num;
		(*p)->next->next = p2;
	}	
}

void IntList_print(struct intList * l){
	while(l != 0){
		printf("%d -- ", l->data);
		l=l->next;
	}
	printf("\n");
}

void IntList_free(struct intList * l){
	struct intList * p = 0; 
	struct intList * p2 = l;
	while(p2 != 0){
		p = p2;
		p2 = p->next;
		free(p);
	}
}

struct intList * IntList_get_ondata(struct intList * l, int el){
	struct intList * p = l;
	while(p != 0){
		if(p->data == el){
			return p;
		}
		p = p->next;
	}
	return 0;
}

void IntList_pop_ondata(struct intList ** l, int el){
	if((*l)->data == el){
		IntList_pop_first(l);
		return;
	}
	struct intList * p = (*l);
	while(p->next->data != el){
		p = p->next;
	}
	struct intList * p2 = p->next;
	p->next = p->next->next;
	free(p2);
}