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

struct returninsert{
	struct tree * tr;
	int stat;
};

//////////////////////////////////////////////////////////////////////////////////////
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
	} else{
		return right + 1;
	}
}

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

struct tree * rotateright(struct tree * tr, int is_bigh_rotation){
	struct tree * q = tr->left;
	tr->left = q->right;
	q->right = tr;
	if(is_bigh_rotation == 0){
		if(q->height_delta == 1){
			tr->height_delta = 0;
			q->height_delta = 0;
		} else
		if(q->height_delta == 0){
			tr->height_delta = 1;
			q->height_delta = -1;
		}
	}
	return q;
}

struct tree * rotateleft(struct tree * tr, int is_bigh_rotation){
	struct tree * q = tr->right;
	tr->right = q->left;
	q->left = tr;
	if(is_bigh_rotation == 0){
		if(q->height_delta == -1){
			tr->height_delta = 0;
			q->height_delta = 0;
		} else
		if(q->height_delta == 0){
			tr->height_delta = -1;
			q->height_delta = 1;
		}
	}
	return q;
}

struct tree * bigrotateleft(struct tree * tr){
	tr->right = rotateright(tr->right, 1);
	tr = rotateleft(tr, 1);
	if(tr->height_delta == 0){
		tr->right->height_delta = 0;
		tr->left->height_delta = 0;
	} else if(tr->height_delta == 1){
		tr->right->height_delta = -1;
		tr->left->height_delta = 0;
	} else if(tr->height_delta == -1){
		tr->right->height_delta = 0;
		tr->left->height_delta = 1;
	}
	tr->height_delta = 0;
	return tr;
}

struct tree * bigrotateright(struct tree * tr){
	tr->left = rotateleft(tr->left, 1);
	tr = rotateright(tr, 1);
	if(tr->height_delta == 0){
		tr->right->height_delta = 0;
		tr->left->height_delta = 0;
	} else if(tr->height_delta == 1){
		tr->right->height_delta = -1;
		tr->left->height_delta = 0;
	} else if(tr->height_delta == -1){
		tr->right->height_delta = 0;
		tr->left->height_delta = 1;
	}
	tr->height_delta = 0;
	return tr;
}

struct tree * balance(struct tree * tr){
	if(-2 == tr->height_delta){
		if(tr->right->height_delta > 0){
			return bigrotateleft(tr);
		} else
		return rotateleft(tr, 0);
	}
	if(2 == tr->height_delta){
		if(tr->left->height_delta < 0){
			return bigrotateright(tr);
		} else
		return rotateright(tr, 0);
	}
	return tr;
}

struct returninsert insert(struct tree * tr, const char * k, struct student st){
	struct returninsert ret;
	struct returninsert answ_from_insert;
	if(!tr){
		struct tree *r = (struct tree *)malloc(1 * sizeof(struct tree));
		r->left = 0;
		r->right = 0;
		memcpy(r->key, k, KEYLEN);
		r->height_delta = 0;
		r->person.age = st.age;
		r->person.height = st.height;
		ret.tr = r;
		ret.stat = 0;
		return ret;
	}
	if(strcmp(tr->key, k) > 0){
		answ_from_insert = insert(tr->left, k, st);
		tr->left = answ_from_insert.tr;
		ret.stat = answ_from_insert.stat;
		ret.tr = tr;
		if(1 == ret.stat){
			return ret;
		}
		tr->height_delta++;
		ret.tr = balance(tr);
		if(ret.tr->height_delta == 0){
			ret.stat = 1;
		}
	} else{
		answ_from_insert = insert(tr->right, k, st);
		tr->right = answ_from_insert.tr;
		ret.stat = answ_from_insert.stat;
		ret.tr = tr;
		if(1 == ret.stat){
			return ret;
		}
		tr->height_delta--;
		ret.tr = balance(tr);
		if(ret.tr->height_delta == 0){
			ret.stat = 1;
		}
	}
	return ret;
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
			tr = insert(tr, key, st).tr;
		}
	}
	return tr;
}

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
			printf("\nname - %s\nage - %d\nheight - %d\n", result->key, result->person.age, result->person.height);
		} else{
			printf("Not found\n");
		}
	}
	return 0;
}