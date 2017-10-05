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
    if(x < 0)          x = width - 1;
    if(x > width - 1)  x = 0;
    if(y < 0)          y = height - 1;
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

    FILE *fileRLE;
    FILE *fileRULE;
    char *rule[219];
    int width;
    int height;
    int x = 0 ,y = 0;
    int i,j;

    fileRULE = fopen("rule.txt", "r");
    fileRLE = fopen("data.rle", "r");

    char pointer;
    do{
        fscanf(fileRLE,"%c",&pointer);
    }while(pointer != 'x');
    fscanf(fileRLE," = %d, y = %d, rule = Langtons-Loops\n",&width, &height);
    char *map = (char *)calloc(width * height,1);

    int length = 0;
    int eoff = 0;
    do{
        eoff =  fscanf(fileRLE,"%c",&pointer);
        length++;
    }while(pointer != '!' && eoff != -1);
    length--;
    char *str = (char *)malloc(length+1);
    str[length] = '\0';
    if(eoff == -1) fseek (fileRLE,length * -1,SEEK_END);
    else     fseek (fileRLE,(length+1) * -1,SEEK_END);
    for (i = 0; i < length; ++i)
    {
        fscanf(fileRLE,"%c",&str[i]);
    }
    int count = 0;
    for (i = 0; i < length; ++i)
    {
        if(str[i] >= '0' && str[i] <= '9'){
            count *= 10;
            count += str[i] - '0';
        } else
            if(str[i] == '.'){
                if(count == 0){
                    x++;
                    count = 0;
                } else{
                    x += count;
                    count = 0;
                }
            } else
                if(str[i] == '$'){
                    y++; x = 0;
                } else{
                    if(count == 0){
                        map[x+(y*width)] = str[i]-'A'+1;
                        x++;
                    }
                    else{
                        for (j = 0; j < count; ++j)
                        {
                            map[x+(y*width)] = str[i]-'A'+1;
                            x++;
                        }
                        count = 0;
                    }
                }
    }
    for (i = 0; i < 219; ++i)
    {
        rule[i] = (char *)calloc(7,1);
        fscanf(fileRULE,"%s",rule[i]);
    }
    fclose(fileRLE);
    fclose(fileRULE);
    while(getch() != 'k'){
    system("cls");
    printf("%d\n",length);
    printf("%s\n",str);
    draw(map, width, height);
    turn(map,width,height,rule);
    }
    return 0;
}