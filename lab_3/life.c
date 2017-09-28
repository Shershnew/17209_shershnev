#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void draw(char * map,int width, int height){
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if(*(map+j+(i * width)) == 1)
            printf("*");
            else
                printf(" ");
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

void turn(char *map, int width, int height){
    int count = 0;
    char *counts = calloc(width * height, 1);
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            count = 0;
            if(*(map + check(i-1,j-1,width,height)) == 1) count++;
            if(*(map + check(i-1,j,width,height)) == 1) count++;
            if(*(map + check(i-1,j+1,width,height)) == 1) count++;
            if(*(map + check(i,j-1,width,height)) == 1) count++;
            if(*(map + check(i,j+1,width,height)) == 1) count++;
            if(*(map + check(i+1,j-1,width,height)) == 1) count++;
            if(*(map + check(i+1,j,width,height)) == 1) count++;
            if(*(map + check(i+1,j+1,width,height)) == 1) count++;
            counts[i+(j*width)] = count;
        }
    }
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            if(*(map + i + (j * width)) == 1 && (counts[i+(j*width)] < 2 || counts[i+(j*width)] > 3))
                *(map + i + (j * width)) = 0;
            if(*(map + i + (j * width)) == 0 && counts[i+(j*width)] == 3)
                *(map + i + (j * width)) = 1;
        }
    }
}

int main(int argc, char **argv){

    FILE *file;
    int width;
    int height;
    int x,y;
    file = fopen(argv[1], "r");
    fscanf(file,"#Size %d %d\n",&width, &height);
    char *map = (char *)calloc(width * height,1);
    while(!feof(file)){
        fscanf(file,"%d %d\n",&x, &y);
        *(map+x-1+((y-1) * width)) = 1;
   }
    fclose(file);
    draw(map, width, height);
    while(getch() != 'k'){
        system("cls");
        draw(map, width, height);
        turn(map, width, height);
    }
    return 0;
}