#include <stdio.h>
#include <stdlib.h>

struct node{
	int c;
	unsigned int freq;
	int was;
	struct node * left;
	struct node * right;
	struct node * parent;
};

void print_freq(struct node ** tree, int size){
	for (int i = 0; i < size; ++i){
		printf("i = %d freq = %d was = %d left = %d right = %d c = %d\n",i, tree[i]->freq, tree[i]->was, tree[i]->left, tree[i]->right, tree[i]->c);		
	}
	printf("\n");
}

struct node * find_node(struct node ** tree, int size, char c){
	for (int i = 0; i < size; ++i){
		if(tree[i]->c == c){
			return tree[i];
		}
	}
	return 0;
}

struct node * node_min(struct node ** tree, int size){
	struct node * tec = 0;
	unsigned long long min = 9999;
	for (int i = 0; i < size; ++i)
	{
		if(tree[i]->was == 0 && tree[i]->freq <= min){
			min = tree[i]->freq;
			tec = tree[i];
		}
	}
	tec->was = 1;
	return tec;
}

int main(int argv, char ** argc){
	FILE * f = fopen(argc[1], "r");
	if(f == 0){
		printf("Error read\n");
		return -1;
	}
	unsigned int size_table = 0;
	unsigned int p = 0;
	unsigned char r = 0;
	unsigned char ost = 0;

	fscanf(f, "%c", &ost);

	fscanf(f, "%c", &r);
	size_table += r;
	fscanf(f, "%c", &r);
	p = r;
	p = p << 8;
	size_table += p;
	p = 0;
	fscanf(f, "%c", &r);
	p = r;
	p = p << 16;
	size_table += p;
	p = 0;
	fscanf(f, "%c", &r);
	p = r;
	p = p << 24;
	size_table += p;
	p = 0;

	struct node ** tree = (struct node **)calloc((size_table*2) - 1, sizeof(struct node *));

	for (int i = 0; i < size_table; ++i){
		tree[i] = (struct node *)calloc(1, sizeof(struct node));
		fscanf(f, "%c", &r);
		tree[i]->c = r;

		fscanf(f, "%c", &r);
		tree[i]->freq += r;
		fscanf(f, "%c", &r);
		p = r;
		p = p << 8;
		tree[i]->freq += p;
		p = 0;
		fscanf(f, "%c", &r);
		p = r;
		p = p << 16;
		tree[i]->freq += p;
		p = 0;
		fscanf(f, "%c", &r);
		p = r;
		p = p << 24;
		tree[i]->freq += p;
		p = 0;
	}

	for (int i = 0; i < size_table - 1; ++i){
		tree[size_table+i] = (struct node *)calloc(1, sizeof(struct node));
		tree[size_table+i]->c = -1;
	}

	for (int i = size_table; i < size_table*2 - 1; ++i){	
		tree[i]->left = node_min(tree, i);
		tree[i]->right = node_min(tree, i);
		tree[i]->left->parent = tree[i];
		tree[i]->right->parent = tree[i];
		tree[i]->freq = tree[i]->left->freq + tree[i]->right->freq; 
	}
	fclose(f);

	FILE * res = fopen("result.txt", "w");
	FILE * f2 = fopen(argc[1], "r");
	for (int i = 0; i < size_table * 5 + 5; ++i){
		char k = 0;
		fscanf(f2, "%c", &k);
	}
	unsigned char cc = 0;
	unsigned char cc2 = 0;
	unsigned char wr = 0;
	int ostflag = 0;
	struct node * p1 = tree[size_table*2 - 2];

	int er = fscanf(f2, "%c", &cc);
	if(er == 1)
	while(1){
		int er2 = fscanf(f2, "%c", &cc2);
		if(er2 != 1){
			ostflag = 1;
			cc = cc << (8 - ost);
		}
		for (int i = 0; i < (ostflag ? ost : 8); ++i){
			printf("--------------c = %d\n", cc/128);
			printf("i == %d\n", i);
			if(cc / 128 == 0){
				cc = cc << 1;
				if(p1->right != 0){
					p1 = p1->right;	
				}
			} else{
				cc = cc << 1;
				if(p1->left != 0){
					p1 = p1->left;	
				}
			}
			if(p1->c != -1){
				printf("i = %d c = %c\n",i, p1->c);
				fprintf(res, "%c", p1->c);
				p1 = tree[size_table*2 - 2];
			}
		}
		cc = cc2;
		if(ostflag){
			break;
		}
	}
	printf("ost = %d\n", ost);
	fclose(f2);
	fclose(res);
	printf("size_table = %d\n", size_table);
	print_freq(tree, size_table*2-1);
	return 0;
}