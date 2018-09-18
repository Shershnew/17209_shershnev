#pragma once

struct intList{
	int data;
	struct intList * next;
};

int IntList_pop_first(struct intList ** l);
void IntList_push(struct intList ** l, int num);
void IntList_push_from(struct intList ** l, int num, int counter);
void IntList_print(struct intList * l);
void IntList_free(struct intList * l);
void IntList_pop_ondata(struct intList ** l, int el);
struct intList * IntList_get_ondata(struct intList * l, int el);