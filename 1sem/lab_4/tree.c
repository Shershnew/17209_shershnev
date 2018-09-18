#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define KEYLEN 60

struct student{
	int age;
	int height;
};

struct tree{
	struct student person;
	char key[KEYLEN];
	int height_delta;
	struct tree * left;
	struct tree * right;
};

void fixheight(struct tree * tr){
	int hl = tr->left ? tr->left->height_delta : 0;
	int hr = tr->right ? tr->right->height_delta : 0;
	tr->height_delta = ((hl > hr) ? hl: hr) +1;
}

int bfactor(struct tree * tr){
	return (tr->right ? tr->right->height_delta : 0) - (tr->left ? tr->left->height_delta : 0);
}

struct tree * rotateright(struct tree * tr){
	struct tree * q = tr->left;
	tr->left = q->right;
	q->right = tr;
	fixheight(tr);
	fixheight(q);
	return q;
}

struct tree * rotateleft(struct tree * tr){
	struct tree * q = tr->right;
	tr->right = q->left;
	q->left = tr;
	fixheight(tr);
	fixheight(q);
	return q;
}

struct tree * balance(struct tree * tr){
	fixheight(tr);
	if(2 == bfactor(tr)){
		if(bfactor(tr->right) < 0){
			tr->right = rotateright(tr->right);
		}
		return rotateleft(tr);
	}
	if(-2 == bfactor(tr)){
		if(bfactor(tr->left) > 0){
			tr->left = rotateleft(tr->left);
		}
		return rotateright(tr);
	}
	return tr;
}

struct tree * insert(struct tree * tr, const char * k, struct student st){
	if(!tr){
		struct tree *r = (struct tree *)malloc(1 * sizeof(struct tree));
		r->left = 0;
		r->right = 0;
		memcpy(r->key, k, KEYLEN);
		r->height_delta = 1;
		r->person.age = st.age;
		r->person.height = st.height;
		return r;
	}
	if(strcmp(tr->key, k) > 0){
		tr->left = insert(tr->left, k, st);
	} else{
		tr->right = insert(tr->right, k, st);
	}
	return balance(tr);
}

struct tree * find(struct tree * tr, const char * key){
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

struct tree * read(FILE * f, struct tree * tr){
	if(NULL == f){
		return 0;
	}
	int data1 = 0;
	int data2 = 0;
	char key[KEYLEN];
	struct student st;
	while(1){
		memset(key, 0, KEYLEN);
		if(-1 == fscanf(f,"%s %d %d", key, &st.age, &st.height)){
			break;
		}
		if(!find(tr, key)){
			tr = insert(tr, key, st);
		}
	}
	return tr;
}

//////////////////////////////////////////////////////////////////////////////////////
//определяет высоту поддерева 
int height (struct tree * node) { 
	if (node == NULL) {
		return 0;
	}
	int left = 0;
	int right = 0;
	left += height(node->left);
	right += height(node->right);
	if (left > right) {
		return left + 1;
	}else {
		return right + 1;
	}
}
//проверка баланса 
int check_balance (struct tree * node) { 
	if (node == NULL) {
		return 0;
	}
	int count = 0;
	int balance = height(node->left) - height(node->right);
	if (balance < 2 && balance > -2) {
		count += check_balance(node->left);
		count += check_balance(node->right);
	} else{
		return 1;
	}
	return count;
}
////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char ** argv){
	struct tree * head = 0;
	FILE * f = fopen(argv[1], "r");
	clock_t start = clock();
	head = read(f, head);
	fclose(f);
	if(head == 0){
		printf("error read\n");
		return -1;
	} else{
		clock_t finish = clock();
		printf("Read %f seconds\n", ((float)(finish - start)) / CLOCKS_PER_SEC);
	}
	if(check_balance(head) == 0){
		printf("balanced\n");
	}else{
		printf("unbalanced\n");
	}
	char name[KEYLEN];
	while(1){
		memset(name, 0, KEYLEN);
		scanf("%s", name);
		struct tree * result = find(head, name);
		if(result){
			printf("\nname - %s\nage - %d\nheight - %d", result->key, result->person.age, result->person.height);
		} else{
			printf("Not found\n");
		}
	}
	return 0;
}