#include<stdio.h>

#define N 300 //максимальное кол-во символов в числе

void multiplication(int* operand1, int operand2) {
    int result[N] = {0};
    int perenos = 0;
    int t = 0;
    //умножаем по длинной арифметике
    for (int i = 0; i < operand2; ++i) {
        perenos = 0;
        for (int j = 0; j < N; ++j) {
            result[j] = (result[j] + operand1[j] + perenos);
            perenos = result[j] / 10;
            result[j] %= 10;
        }
    }
    //возвращаем число
    for (int i = 0; i < N; ++i) {
        operand1[i] = result[i];
    }
}

int main() {

    int arr[N] = {0};
    int R = 0;
    arr[0] = 1;
    //находим факториал 100
    for (char i = 1; i <= 100; ++i){
         multiplication(arr, i);
    }
    //суммируем цифры
    for (int i = 0; i < N; ++i){
        R += arr[i];
    }
    printf("\n%d\n",R);
    return 0;
}