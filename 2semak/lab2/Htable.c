#include "Htable.h"
#include <stdlib.h>
#include <string.h>

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

void insert_for_resize(struct Hash_table * ht, struct Ht_data * person){
	int k = 0;
	int key = 0;
	while(1){
		key = (h2(person->name) + k * h1(person->name)) % ht->buf_size;
		if(ht->Ht_data[key] == 0){
			ht->Ht_data[key] = person;
			ht->size++;
			break;
		} else {
			k++;
		}
	}
}

void resize(struct Hash_table ** ht){
	struct Hash_table * ht_new = (struct Hash_table *)calloc(1, sizeof(struct Hash_table));
	long long buf_size_new = (*ht)->buf_size * 2;
	ht_new->Ht_data = (struct Ht_data **)calloc(buf_size_new, sizeof(struct Ht_data *));
	ht_new->buf_size = buf_size_new;
	for (long long i = 0; i < (*ht)->buf_size; ++i){
		if((*ht)->Ht_data[i] != 0){
			insert_for_resize(ht_new, (*ht)->Ht_data[i]);
		}
	}
	(*ht)->Ht_data = ht_new->Ht_data;
	(*ht)->buf_size = ht_new->buf_size;
	free(ht_new);
}

void Ht_set(struct Hash_table * ht, struct Ht_data * data){
	int k = 0;
	int key = 0;

	if (ht->size >= ht->buf_size/2){
		resize(&ht);
	}

	while(1){
		key = (h2(data->name) + k * h1(data->name)) % ht->buf_size;
		if(ht->Ht_data[key] == 0){
			ht->Ht_data[key] = data;
			ht->size++;
			break;		
		} else if(!strcmp(data->name, ht->Ht_data[key]->name)){
			break;
		} else {
			k++;
		}	 
	}
}

struct Ht_data * Ht_get(struct Hash_table * ht, int num){
	char str[NAMESIZE];
	itoa(num, str, 10);
	int k = 0;
	int key = 0;
	while(1){
		key = (h2(str) + k * h1(str)) % ht->buf_size;
		if(ht->Ht_data[key] != 0 && !strcmp(str, ht->Ht_data[key]->name)){
			return ht->Ht_data[key];
		} else{
			k++;
			if(k == ht->buf_size){
				break;
			}
		}
	}
	return 0;
}

void Ht_free(struct Hash_table * ht){
	for (int i = 0; i < ht->buf_size; ++i){
		if(ht->Ht_data[i] != 0){
			IntList_free(ht->Ht_data[i]->list);
			free(ht->Ht_data[i]);
		}
	}
	free(ht->Ht_data);
	free(ht);
}

struct Hash_table * Ht_init(){
	struct Hash_table * ht = calloc(1, sizeof(struct Hash_table));
	ht->buf_size = BUFSIZE;
	ht->size = 0;
	ht->Ht_data = (struct Ht_data **)calloc(BUFSIZE, sizeof(struct Ht_data *));
	return ht;
}