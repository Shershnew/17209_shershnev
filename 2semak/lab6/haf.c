#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

void print_tree(struct node * head){
	if(head->c != -1){
		printf("%c ", head->c);
	}
	if(head->left != 0){
		print_tree(head->left);
	}
	if(head->right != 0){
		print_tree(head->right);
	}
}

int find_node(struct node ** tree, int size, char c){
	for (int i = 0; i < size; ++i){
		if(tree[i]->c == c){
			return i;
		}
	}
	return -1;
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

int main(int argc, char ** argv){
	FILE * f = fopen(argv[1], "r");
	if(f == 0){
		printf("Error read\n");
		return -1;
	}
	unsigned long long freq[256] = {0};
	unsigned char c;
	unsigned char ost = 0;
	while(1){
		c = getc(f);
		if(feof(f)){
			break;
		}	
		freq[c]++;
		// printf("l");
	}
	unsigned int size_char = 0;
	for (int i = 0; i < 256; ++i){
		if(freq[i] != 0){
			size_char++;
		}
	}
	struct node ** tree = (struct node **)calloc((size_char*2) - 1, sizeof(struct node *));
	int j = 0;
	for (int i = 0; i < 256; ++i){
		if(freq[i] != 0){
			tree[j] = (struct node *)calloc(1, sizeof(struct node));
			tree[j]->c = i;
			tree[j]->freq = freq[i];
			j++;
		}
	}
	for (int i = 0; i < size_char - 1; ++i){
		tree[size_char+i] = (struct node *)calloc(1, sizeof(struct node));
		tree[size_char+i]->c = -1;
	}
	
	for (int i = size_char; i < size_char*2 - 1; ++i){	
		tree[i]->left = node_min(tree, i);
		tree[i]->right = node_min(tree, i);
		tree[i]->left->parent = tree[i];
		tree[i]->right->parent = tree[i];
		tree[i]->freq = tree[i]->left->freq + tree[i]->right->freq;
	}
	print_freq(tree, size_char*2-1); 
	fclose(f);
	print_tree(tree[size_char*2 - 2]);
	printf("\n");

	unsigned char * m1 = (unsigned char *)calloc(size_char, sizeof(unsigned char));
	unsigned char * m2 = (unsigned char *)calloc(size_char, sizeof(unsigned char));

	for (int i = 0; i < size_char; ++i){
		struct node * p1 = tree[i];
		struct node * p2 = 0;
		int j = 0;
		while(p1->parent != 0){
			j++;
			p2 = p1->parent;
			if(p1 == p2->left){
				m1[i] = m1[i] << 1;
				m1[i] += 1;
			} else{
				m1[i] = m1[i] << 1;
			}
			p1 = p2;
		}
		if(j == 0){
			j++;
		}
		m2[i] = j;
		printf("m1[%d] = %d m2 = %d\n",i,m1[i],m2[i]);
	}

	unsigned long long llost = 0;
	for (int i = 0; i < size_char; ++i)
	{
		llost += m2[i] * tree[i]->freq;
	}
	llost %= 8;
	ost = llost;

	FILE * f2 = fopen(argv[1], "r");
	FILE * fr = fopen("result.haf", "w");

	fprintf(fr, "%c", ost);

	unsigned char data_w = 0;
	data_w = size_char % 256;
	fprintf(fr, "%c", data_w);
	data_w = (size_char >> 8) % 256;
	fprintf(fr, "%c", data_w);
	data_w = (size_char >> 16) % 256;
	fprintf(fr, "%c", data_w);
	data_w = (size_char >> 24) % 256;
	fprintf(fr, "%c", data_w);

	for (int i = 0; i < size_char; ++i){
		unsigned char simbol = (unsigned char)tree[i]->c;
		fprintf(fr, "%c", simbol);
		unsigned int freq_w = tree[i]->freq;
		simbol = freq_w % 256;
		fprintf(fr, "%c", simbol);
		simbol = (freq_w >> 8) % 256;
		fprintf(fr, "%c", simbol);
		simbol = (freq_w >> 16) % 256;
		fprintf(fr, "%c", simbol);
		simbol = (freq_w >> 24) % 256;
		fprintf(fr, "%c", simbol);
	}

	int count = 0;
	unsigned char cc = 0;
	unsigned char wr = 0;
	while(1){
		cc = getc(f2);
		if(feof(f2)){
			break;
		}
		int tec = find_node(tree, size_char, cc);
		for (int i = 0; i < m2[tec]; ++i){
			wr = wr << 1;
			wr += (m1[tec] >> i) % 2;
			printf("%d\n", (m1[tec] >> i) % 2);
			count ++;
			if(count == 8){
				fprintf(fr, "%c", wr);
				printf("%d --\n", wr);
				wr = 0;
				count = 0;
			}
		}	
	}
	if(count != 0){
		fprintf(fr, "%c", wr);
	}

	fclose(f2);
	fclose(fr);
	return 0;
}