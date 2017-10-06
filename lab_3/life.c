#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

void draw(char * map,int width, int height){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if(*(map+j+(i * width)) == 0){
                SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 0));
                printf(" ");
            }
            else{
                if(*(map+j+(i * width)) == 1) SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 9)); else
                if(*(map+j+(i * width)) == 2) SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 4)); else
                if(*(map+j+(i * width)) == 3) SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 3)); else
                if(*(map+j+(i * width)) == 4) SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 2)); else
                if(*(map+j+(i * width)) == 5) SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 5)); else
                if(*(map+j+(i * width)) == 6) SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 6)); else
                if(*(map+j+(i * width)) == 7) SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 7));
                printf("*");
            }
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

    int eoff = 0;
    int count = 0;
    do{
        eoff =  fscanf(fileRLE,"%c",&pointer);
        if(pointer >= '0' && pointer <= '9'){
            count *= 10;
            count += pointer - '0';
        }
        else
            if(pointer == '.'){
                if(count == 0){
                    x++;
                    count = 0;
                } else{
                    x += count;
                    count = 0;
                }
            }
            else
                if(pointer == '$'){
                    y++; x = 0;
                }
                else
                    if(pointer == '\n' || pointer == '!'){
                        continue;
                    }
                        else
                            if(count == 0){
                            map[x+(y*width)] = pointer-'A'+1;
                            x++;
                            }
                            else{
                                for (j = 0; j < count; ++j){
                                    map[x+(y*width)] = pointer-'A'+1;
                                    x++;
                                }
                                count = 0;
                            }
    }while(pointer != '!' && eoff != -1);

    for (i = 0; i < 219; ++i)
    {
        rule[i] = (char *)calloc(7,1);
        fscanf(fileRULE,"%s",rule[i]);
    }
    fclose(fileRLE);
    fclose(fileRULE);
    printf("%d\n",'A'-1-54);
    while(getch() != 'k'){
    system("cls");
    draw(map, width, height);
    turn(map,width,height,rule);
    }
    system("color 02");
    return 0;
}