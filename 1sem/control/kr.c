#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int binsearch(int * arr, int len, int el){
	int l = 0;
	int r = len;
	int tec;
	while(l < r){
		tec = (l + r)/2;
		if(arr[tec] == el){
			return tec;
		} else if(arr[tec] > el){
			r = tec;
		} else{
			l = tec;
		}
	}
	return -1;
}
//as df safbfd
int strstrfor(char * arr, char * el){
	int i = 0;
	while(el[i] != '\0'){
		if(arr[i] == '\0'){
			return 0;
		}
		if(el[i] != arr[i]){
			return 0;
		}
		i++;
	}
	return 1;
}

int strstrr(char * arr, char * el){
	int i = 0;
	while(arr[i] != 0){
		if(strstrfor(arr + i, el)){
			return i;
		}
		i++;
	}
	return -1;
}

int main(){

	int arr_int[] = {1,4,6,8,9,13,15,577};
	printf("%d\n", binsearch(arr_int, sizeof(arr_int) / sizeof(int), 1));

	printf("%d str\n", strstrr("asdfasdfadggfadsdfhfghsdsgghjhf", "asdfasdfadggfadsdfhfghsdsgghjhf"));
	return 0;
}