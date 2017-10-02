#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void draw(char * map,int width, int height){
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if(*(map+j+(i * width)) == 0)
                printf(" ");
            else
            printf("%d",*(map+j+(i * width)));
        }
    printf("\n");
    }
    printf("\n");
}

int check(int x,int y,int width,int height){
    if(x < 0) x = width - 1;
    if(x > width - 1) x = 0;
    if(y < 0) y = height - 1;
    if(y > height - 1) y = 0;
    return x + (y * width);
}

void turn(char *map, int width, int height,char **rule){
    char *map2 = calloc(width * height, 1);
    char tec[7];
    tec[6] = '\0';
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            tec[0] = map[check(i,j,width,height)];
            tec[1] = map[check(i,j-1,width,height)];
            tec[2] = map[check(i+1,j,width,height)];
            tec[3] = map[check(i,j+1,width,height)];
            tec[4] = map[check(i-1,j,width,height)];
            for (int k = 0; k < 219; ++k)
            {
                if(*(rule[k]) - '0' == tec[0] && *(rule[k]+1) - '0' == tec[1] && *(rule[k]+2) - '0' == tec[2] && *(rule[k]+3) - '0' == tec[3] && *(rule[k]+4) - '0' == tec[4]){
                    map2[i+(j*width)] =*(rule[k]+5) - '0';
                    break;
                } else
                if(*(rule[k]) - '0' == tec[0] && *(rule[k]+1) - '0' == tec[4] && *(rule[k]+2) - '0' == tec[1] && *(rule[k]+3) - '0' == tec[2] && *(rule[k]+4) - '0' == tec[3]){
                    map2[i+(j*width)] =*(rule[k]+5) - '0';
                    break;
                } else
                if(*(rule[k]) - '0' == tec[0] && *(rule[k]+1) - '0' == tec[3] && *(rule[k]+2) - '0' == tec[4] && *(rule[k]+3) - '0' == tec[1] && *(rule[k]+4) - '0' == tec[2]){
                    map2[i+(j*width)] =*(rule[k]+5) - '0';
                    break;
                } else
                if(*(rule[k]) - '0' == tec[0] && *(rule[k]+1) - '0' == tec[2] && *(rule[k]+2) - '0' == tec[3] && *(rule[k]+3) - '0' == tec[4] && *(rule[k]+4) - '0' == tec[1]){
                    map2[i+(j*width)] =*(rule[k]+5) - '0';
                    break;
                }
            }
        }
    }
    for (int i = 0; i < width * height; ++i)
    {
        map[i] = map2[i];
    }
}

int main(int argc, char **argv){

    FILE *file;
    char *rule[219];
    int width;
    int height;
    int x = 1 ,y = 1;
    int i,j;

    file = fopen("rule.txt", "r");
    fscanf(file,"#Size %d %d\n",&width, &height);

    char *map = (char *)calloc(width * height,1);
    char str[width];
    for (i = 0; i < 10; ++i)
    {
        for (j = 0; j < width; ++j)
        {
            str[j] = 0;
        }
        fscanf(file,"%s",str);
        for (j = 0; j < width; ++j)
        {
            if(str[j] != 0)
            map[j+x+((i+y)*width)] = str[j] - '0';
        }
    }
    for (i = 0; i < 219; ++i)
    {
        rule[i] = (char *)calloc(7,1);
        fscanf(file,"%s",rule[i]);
    }
    fclose(file);
    while(getch() != 'k'){
    system("cls");
    draw(map, width, height);
    turn(map,width,height,rule);
    }
    return 0;
}