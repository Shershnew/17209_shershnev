#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NAMESIZE 50
#define BUFSIZE 3000000

struct data_base{
	struct data ** Htable;
	long long buf_size;
	int size;
};

struct data{
	char name[NAMESIZE];
	int d1;
	int d2;
};

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

void insert(struct data_base * db, struct data person){
	int k = 0;
	int key = 0;

	if (db->size >= db->buf_size/2){
		resize(&db);
	}

	while(1){
		key = (h2(person.name) + k * h1(person.name)) % db->buf_size;
		if(db->Htable[key] == 0){
			db->Htable[key] = (struct data *)malloc(sizeof(struct data));
			db->Htable[key]->d1 = person.d1;
			db->Htable[key]->d2 = person.d2;
			memcpy(db->Htable[key]->name, person.name, NAMESIZE);
			db->size++;
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
	struct data person;
	while(1){
		memset(person.name, 0, NAMESIZE);
		int er = fscanf(f, "%s %d %d", person.name, &person.d1, &person.d2);
		if(er != 3){
			break;
		}
		insert(db, person);
	}
	return db;
}

int find(struct data_base *db, char * str){
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
	return 0;
}

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
	char input_name[NAMESIZE];
	while(1){
		memset(input_name, 0, NAMESIZE);
		scanf("%s", input_name);
		int key = find(db, input_name);
		if(key){
			printf("%d -- %d\n", db->Htable[key]->d1, db->Htable[key]->d2);
		} else{
			printf("Not found\n");
		}
	}
	return 0;
}