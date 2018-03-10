#pragma once

struct intList{
	int data;
	struct intList * next;
};

int IntList_pop_first(struct intList ** l);
void IntList_push(struct intList ** l, int num);
void IntList_print(struct intList * l);
void IntList_free(struct intList * l);