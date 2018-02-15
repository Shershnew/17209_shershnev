#include "hashTable.h"

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

void insert_for_resize(struct data_base * db, struct data * person){
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

void resize(struct data_base ** db){
	struct data_base * db_new = (struct data_base *)calloc(1, sizeof(struct data_base));
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

struct insert{
	int d1;
	int d2;
};

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
			//printf("1s\n");
		}
		(*p)->next = (struct intList *)calloc(1, sizeof(struct intList));
		(*p)->next->data = num;
	}
}

void insert(struct data_base * db, struct insert person){
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

struct data_base * read(FILE * f){
	struct data_base * db = (struct data_base *)calloc(1, sizeof(struct data_base));
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
	}
	return db;
}

int find(struct data_base *db, int num){
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