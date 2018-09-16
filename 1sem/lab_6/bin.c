#include <stdio.h>

double poww(int b){
	double r = 1;
	for (int i = 0; i < b; ++i){
		r /= 2.0;
	}
	return r;
}

int main(){
	double f;
	unsigned long long sign = 0;
	unsigned long long exp = 0;
	double fraction = 1.0;
	scanf("%lf", &f);
	unsigned char * p = (unsigned char *)&f;
	sign = *(p+7) >> 7;
	printf("sign - %d\n", sign);


	for (int i = 1; i < 8; ++i){
		exp = exp << 1;
		exp += (*(p + 7) >> 7 - i) % 2;
	}
	for (int i = 0; i < 4; ++i){
		exp = exp << 1;
		exp += (*(p + 6) >> 7 - i) % 2;
	}
	printf("exp - %d\n", exp);


	for (int i = 4; i < 8; ++i){
		fraction += ((*(p + 6) >> 7 - i) % 2) * poww(i - 3);
	}
	for (int i = 0; i < 8; ++i){
		fraction += ((*(p + 5) >> 7 - i) % 2) * poww(i + 5);
	}
	for (int i = 0; i < 8; ++i){
		fraction += ((*(p + 4) >> 7 - i) % 2) * poww(i + 13);
	}
		for (int i = 0; i < 8; ++i){
		fraction += ((*(p + 3) >> 7 - i) % 2) * poww(i + 21);
	}
		for (int i = 0; i < 8; ++i){
		fraction += ((*(p + 2) >> 7 - i) % 2) * poww(i + 29);
	}
		for (int i = 0; i < 8; ++i){
		fraction += ((*(p + 1) >> 7 - i) % 2) * poww(i + 37);
	}
		for (int i = 0; i < 8; ++i){
		fraction += ((*(p + 0) >> 7 - i) % 2) * poww(i + 45);
	}
	printf("fraction - %.10lf\n", fraction);

//bin
	printf("%d  ", sign);
	for (int i = 1; i < 8; ++i){
		printf("%d", (*(p + 7) >> (7 - i)) % 2);
	}
	for (int i = 0; i < 4; ++i){
		printf("%d", (*(p + 6) >> 7 - i) % 2);
	}
	printf("  ");
	for (int i = 4; i < 8; ++i){
		printf("%d", (*(p + 6) >> 7 - i) % 2);
	}
	for (int j = 0; j < 6; ++j){
		for (int i = 0; i < 8; ++i){
			printf("%d", (*(p + 5 - j) >> 7 - i) % 2);
		}
	}
	return 0;
}