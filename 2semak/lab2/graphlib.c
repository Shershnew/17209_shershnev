#include "graphlib.h"

unsigned int h1(char * str){
	unsigned int hashAddress = 17;
	for (int counter = 0; str[counter] != '\0'; counter++){
		hashAddress = str[counter] + (hashAddress << 6) + (hashAddress << 16) - hashAddress;
	}
	return hashAddress;
}

unsigned int h2(char * str){
	unsigned int hashAddress = 5381;
	for (int counter = 0; str[counter] != '\0'; counter++){
		hashAddress = ((hashAddress << 5) + hashAddress) + str[counter];
	}
	return hashAddress;
}

void insert_for_resize(struct graph_base * db, struct data * person){
	int k = 0;
	int key = 0;
	while(1){
		key = (h2(person->name) + k * h1(person->name)) % db->buf_size;
		if(db->Htable[key] == 0){
			db->Htable[key] = person;
			db->size++;
			break;
		} else {
			k++;
		}
	}
}

void resize(struct graph_base ** db){
	struct graph_base * db_new = (struct graph_base *)calloc(1, sizeof(struct graph_base));
	long long buf_size_new = (*db)->buf_size * 2;
	db_new->Htable = (struct data **)calloc(buf_size_new, sizeof(struct data *));
	db_new->buf_size = buf_size_new;
	for (long long i = 0; i < (*db)->buf_size; ++i){
		if((*db)->Htable[i] != 0){
			insert_for_resize(db_new, (*db)->Htable[i]);
		}
	}
	(*db)->Htable = db_new->Htable;
	(*db)->buf_size = db_new->buf_size;
	free(db_new);
}

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

struct insert{
	int d1;
	int d2;
};

void insert(struct graph_base * db, struct insert person){
	int k = 0;
	int key = 0;

	if (db->size >= db->buf_size/2){
		resize(&db);
	}

	char s[NAMESIZE];
	itoa(person.d1, s, 10);
	while(1){
		key = (h2(s) + k * h1(s)) % db->buf_size;
		if(db->Htable[key] == 0){
			db->Htable[key] = (struct data *)malloc(sizeof(struct data));
			db->Htable[key]->d1 = person.d1;
			db->Htable[key]->list = 0;
			pushtoIntList(&db->Htable[key]->list, person.d2);
			pushtoIntList(&db->list, person.d1);
			memcpy(db->Htable[key]->name, s, NAMESIZE);
			db->size++;
			break;
		} else if(db->Htable[key]->d1 == person.d1){
			pushtoIntList(&db->Htable[key]->list, person.d2);
			pushtoIntList(&db->list, person.d1);
			break;
		} else {
			k++;
		}	 
	}
}

struct graph_base * read_graph(FILE * f){
	struct graph_base * db = (struct graph_base *)calloc(1, sizeof(struct graph_base));
	if(NULL == f){
		db->buf_size = 0;
		return db;
	}
	db->buf_size = BUFSIZE;
	db->size = 0;
	db->Htable = (struct data **)calloc(db->buf_size, sizeof(struct data *));
	struct insert person;
	while(1){
		int er = fscanf(f, "%d %d", &person.d1, &person.d2);
		if(er != 2){
			break;
		}
		insert(db, person);
		int c = person.d1;
		person.d1 = person.d2,
		person.d2 = c;
		insert(db, person);
	}
	return db;
}

int find(struct graph_base *db, int num){
	char str[NAMESIZE];
	itoa(num, str, 10);
	int k = 0;
	int key = 0;
	while(1){
		key = (h2(str) + k * h1(str)) % db->buf_size;
		if(db->Htable[key] != 0 && !strcmp(str, db->Htable[key]->name)){
			return key;
		} else{
			k++;
			if(k == db->buf_size){
				break;
			}
		}
	}
	return -1;
}

void printGraphFromHtableToWidth(struct graph_base * db){
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
}