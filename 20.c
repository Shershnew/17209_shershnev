#include<stdio.h>
#define n 300
void glhf(int* a, int b) {
    int r[n];
    int perenos;
    int t;
    for (int i = 0; i < n; ++i)
        r[i] = 0;
    for (int i = 0; i < b; ++i){
        perenos = 0;
        for (int j = 0; j < n; ++j){
            r[j] = (r[j] + a[j] + perenos);
            perenos = r[j] / 10;
            r[j] %= 10;
        }
    }
    for (int i = 0; i < n; ++i)
        a[i] = r[i];
}

int main() {
    int a[n];
    long long R = 0;
    for (int i = 0; i < n; ++i)
        a[i] = 0;
    a[0] = 1;
     for (char i = 1; i < 100; ++i)
         glhf(a,i);
     for (int i = 0; i < n; ++i)
        R += a[i];
    printf("\n%d\n",R);
    return 0;
}