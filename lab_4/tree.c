#include <stdio.h>
#include <stdlib.h>

#define keylen 50

struct tree{
	int d1;
	int d2;
	char key[keylen];
	int height;
	struct tree *left;
	struct tree *right;
};

void clear(char * str){
	for (int i = 0; i < keylen; ++i){
		str[i] = 0;
	}
}

int strravn(char *str1, char *str2){
	for (int i = 0; i < keylen; ++i)
	{
		if(str1[i] > str2[i]){
			return 1;
		}
		if(str1[i] < str2[i]){
			return 2;
		}
	}
	return 0;
}

int height(struct tree *tr){
	if(tr){
		return tr->height;
	} else{
		return 0;
	}
}

int bfactor(struct tree *tr){
	return height(tr->right) - height(tr->left);
}

void fixheight(struct tree *tr){
	int hl = height(tr->left);
	int hr = height(tr->right);
	if(hl > hr){
		tr->height = hl + 1;
	} else{
		tr->height = hr + 1;
	}
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
	if(bfactor(tr) == 2){
		if(bfactor(tr->right) < 0){
			tr->right = rotateright(tr->right);
		}
		return rotateleft(tr);
	}
	if(bfactor(tr) == -2){
		if(bfactor(tr->left) > 0){
			tr->left = rotateleft(tr->left);
		}
		return rotateright(tr);
	}
	return tr;
}

struct tree * insert(struct tree * tr, char* k, int data1, int data2){
	if(!tr){
		struct tree *r = (struct tree *)malloc(1*sizeof(struct tree));
		r->left = 0;
		r->right = 0;
		for (int i = 0; i < keylen; ++i)
		{
			r->key[i] = k[i];
		}
		r-> height = 1;
		r->d1 = data1;
		r->d2 = data2;
		return r;
	}
	if(strravn(tr->key, k) == 1){
		tr->left = insert(tr->left, k, data1, data2);
	} else{
		tr->right = insert(tr->right, k, data1, data2);
	}
	return balance(tr);
}

void printtree(struct tree* tr){
	if(!tr){
		return;
	}
	printf(" %s-%d-%d ", tr->key, tr->d1, tr->d2);
	printtree(tr->left);
	printtree(tr->right);
}

struct tree * read(char ** argv, struct tree * tr){
	FILE *f = fopen(argv[1],"r");
	int data1 = 0;
	int data2 = 0;
	char key[keylen];
	while(1){
		clear(key);
		if(-1 == fscanf(f,"%s %d %d", key, &data1, &data2)){
			break;
		}
		tr = insert(tr,key,data1,data2);
	};
	fclose(f);
	return tr;
}

struct tree * find(struct tree * tr, char* key){
	if(tr == 0){
		return 0;
	}
	if(strravn(tr->key, key) == 0){
		return tr;
	}
	if(strravn(tr->key, key) == 1){
		return find(tr->left, key);
	}
	if(strravn(tr->key, key) == 2){
		return find(tr->right, key);
	}
	return 0;
}

int main(int argc, char ** argv){
	struct tree * head = 0;
	struct tree * foc = 0;
	head = read(argv, head);
	printtree(head);
	char str[50];
	while(1){
		clear(str);
		scanf("%s", str);
		foc = find(head, str);
		if(foc){
			printf("\n%d -- %d\n", foc->d1, foc->d2);
		} else{
			printf("No found\n");
		}
	};
	return 0;
}