#include <stdio.h>

int main(){
	float f;
	scanf("%f", &f);
	unsigned char * p = (unsigned char *)&f;
	char str[33];
	str[33] = '\0';
	for (int j = 0; j < 4; ++j){
		for (int i = 0; i < 8; ++i){
			str[31-i-(8*j)] ='0' + *p % 2;
			*p = *p>>1;
		}
		p++;
	}
	printf("%s\n", str);
	return 0;
}