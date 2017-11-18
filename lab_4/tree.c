#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEYLEN 50

struct student{
	int age;
	int height;
};

struct tree{
	struct student person;
	char key[KEYLEN];
	int height_delta;
	struct tree *left;
	struct tree *right;
};

void fixheight(struct tree *tr){
	int hl = tr->left ? tr->left->height_delta : 0;
	int hr = tr->right ? tr->right->height_delta : 0;
	tr->height_delta = hl - hr;
}

struct tree * rotateright(struct tree *tr){
	struct tree *q = tr->left;
	tr->left = q->right;
	q->right = tr;
	fixheight(tr);
	fixheight(q);
	return q;
}

struct tree * rotateleft(struct tree *tr){
	struct tree *q = tr->right;
	tr->right = q->left;
	q->left = tr;
	fixheight(tr);
	fixheight(q);
	return q;
}

struct tree * balance(struct tree * tr){
	fixheight(tr);
	if(2 == tr->height_delta){
		if(tr->right->height_delta < 0){
			tr->right = rotateright(tr->right);
		}
		return rotateleft(tr);
	}
	if(-2 == tr->height_delta){
		if(tr->left->height_delta > 0){
			tr->left = rotateleft(tr->left);
		}
		return rotateright(tr);
	}
	return tr;
}

struct tree * insert(struct tree * tr, const char* k, int data_age, int data_height){
	if(!tr){
		struct tree *r = (struct tree *)malloc(1*sizeof(struct tree));
		r->left = 0;
		r->right = 0;
		for(int i = 0; i < KEYLEN; ++i){
			r->key[i] = k[i];
		}
		r->height_delta = 0;
		r->person.age = data_age;
		r->person.height = data_height;
		return r;
	}
	if(strcmp(tr->key, k) > 0){
		if(tr->left == 0){
			tr->height_delta--;
		}
		tr->left = insert(tr->left, k, data_age, data_height);
	} else{
		if(tr->right == 0){
			tr->height_delta++;
		}
		tr->right = insert(tr->right, k, data_age, data_height);
	}
	return balance(tr);
}

struct tree * read(FILE *f, struct tree * tr){
	if(NULL == f){
		return 0;
	}
	int data1 = 0;
	int data2 = 0;
	char key[KEYLEN];
	while(1){
		memset(key, 0, KEYLEN);
		if(-1 == fscanf(f,"%s %d %d", key, &data1, &data2)){
			break;
		}
		tr = insert(tr, key, data1, data2);
	}
	return tr;
}

struct tree * find(struct tree * tr, const char* key){
	if(tr == 0){
		return 0;
	}
	int t = strcmp(tr->key, key);
	if(t == 0){
		return tr;
	} else if(t > 0){
		return find(tr->left, key);
	} else{
		return find(tr->right, key);
	}
	return 0;
}

int main(int argc, char ** argv){
	struct tree * head = 0;
	FILE *f = fopen(argv[1], "r");
	head = read(f, head);
	fclose(f);
	if(head == 0){
		printf("error read\n");
		return -1;
	} else{
		printf("read\n");
	}
	char name[50];
	while(1){
		memset(name, 0, KEYLEN);
		scanf("%s", name);
		struct tree * result = find(head, name);
		if(result){
			printf("\n%d -- %d\n", result->person.age, result->person.height);
		} else{
			printf("Not found\n");
		}
	};

	return 0;
}