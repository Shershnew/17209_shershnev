#include <stdio.h>
#include <stdlib.h>

#define nameSize 50
#define bufSize 98761

struct data{
	char name[nameSize];
	int d1;
	int d2;
};

void clear(char * str){
	for (int i = 0; i < nameSize; ++i){
		str[i] = 0;
	}
}

int strravn(char *str1, char *str2){
	for (int i = 0; i < nameSize; ++i)
	{
		if(str1[i] != str2[i]){
			return 1;
		}
	}
	return 0;
}

int h1(char * str){
	int key = 0;
	for(int i = 0; i < nameSize; ++i){
		key += str[i];
	}
	return key % bufSize;
}

unsigned int h2(char * str){
	unsigned int seed = 131313;
	unsigned int hash = 0;
	for (int i = 0; i < nameSize; ++i){
		hash = (hash * seed) + str[i];
	}
	return hash % bufSize;
}

void insert(struct data ** ht, char * str, int d1, int d2){
	int k = 0;
	int key = 0;
	while(1){
		//printf("do\n");
		key = (h2(str) + k * h1(str)) % bufSize;
		//printf("posle %d\n",key);
		if(ht[key] == 0){
			printf("l9\n");
			ht[key] = (struct data *)malloc(sizeof(struct data));
			ht[key]->d1 = d1;
			ht[key]->d2 = d2;
			for (int i = 0; i < nameSize; ++i){
				ht[key]->name[i] = str[i];
			}
			break;
		} else{
			k++;
		}
	}
}

void read(struct data ** ht, char **argv){
	FILE * f = fopen(argv[1],"r");
	int er = 0;
	int d1 = 0;
	int d2 = 0;
	char str[nameSize];
	clear(str);
	while(1){
		er = fscanf(f, "%s %d %d", str, &d1, &d2);
		//printf("l2\n");
		if(er == -1){
			break;
			//printf("br\n");
		}
		insert(ht, str, d1, d2);
	}
	fclose(f);
}

int find(struct data ** ht, char * str){
	int k = 0;
	int key = 0;
	while(1){
		key = (h2(str) + k * h1(str)) % bufSize;
		printf("key = %d\n", key);
		if(ht[key] != 0 && !strravn(str, ht[key]->name)){
			return key;
		} else {
			k++;
			if(k == bufSize){
				break;
			}
		}
	}
	//printf("r0\n");
	return 0;
}

int main(int argc, char ** argv){
	struct data * Htable[bufSize];
	for (int i = 0; i < bufSize; ++i){
		Htable[i] = 0;
	}
	read(Htable, argv);
	char input[nameSize];
	int key = 0;
	while(1){
		clear(input);
		scanf("%s", input);
		key = find(Htable, input);
		if(key){
			printf("%d -- %d\n", Htable[key]->d1, Htable[key]->d2);
		} else{
			printf("not found\n");
		}
	}
	return 0;
}