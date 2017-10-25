#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <ctype.h>
//#include <Windows.h>

void draw(char *map, int width, int height){
    int i = 0;
    int j = 0;
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (i = 0; i < height; ++i)
    {
        for (j = 0; j < width; ++j)
        {
            if(*(map+j+(i * width)) == 0){
                //SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 0));
                printf(" ");
            }
            else{
                if(*(map+j+(i * width)) == 1) printf("1");//SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 9));
                else
                if(*(map+j+(i * width)) == 2) printf("2");//SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 4));
                else
                if(*(map+j+(i * width)) == 3) printf("3");//SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 3));
                else
                if(*(map+j+(i * width)) == 4) printf("4");//SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 2)); 
            else
                if(*(map+j+(i * width)) == 5) printf("5");//SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 5));
                 else
                if(*(map+j+(i * width)) == 6) printf("6");//SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 6));
                 else
                if(*(map+j+(i * width)) == 7) printf("7");//SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 7));
                //printf("*");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int check(int x, int y, int width, int height){
    if(x < 0){
        x = width - 1;
    }
    if(x > width - 1){
        x = 0;
    }
    if(y < 0){
        y = height - 1;
    }
    if(y > height - 1){
        y = 0;
    }
    return x + (y * width);
}

void turn(char **map, int width, int height, int *rule){
    char *map2 = calloc(width * height, 1);
    int i = 0;
    int j = 0;
    int k = 0;
    int id = 0;
    char tec[5];
    for (j = 0; j < height; ++j)
    {
        for (i = 0; i < width; ++i)
        {
            tec[0] = (*map)[check(i,j,width,height)];
            tec[1] = (*map)[check(i,j-1,width,height)];
            tec[2] = (*map)[check(i+1,j,width,height)];
            tec[3] = (*map)[check(i,j+1,width,height)];
            tec[4] = (*map)[check(i-1,j,width,height)];
            id = 0;
            id += (int)tec[0];
            id *= 10;
            id += (int)tec[1];
            id *= 10;
            id += (int)tec[2];
            id *= 10;
            id += (int)tec[3];
            id *= 10;
            id += (int)tec[4];
            if(rule[id] != 0){
                map2[i+(j*width)] = rule[id]-1;
            }
        }
    }
    char *c = *map;
    *map = map2;
    free(c);
}

char* read_rle(int *width, int *height, char **argv){
    FILE *fileRLE;
    fileRLE = fopen(argv[1], "r");
    int x = 0;
    int y = 0;
    int i = 0;
    int j = 0;
    int count = 0;
    char *map;
    char pointer;
    do{
        if(fscanf(fileRLE,"%c",&pointer) == -1){
            break;
        }
        if(pointer == 'x'){
            fscanf(fileRLE," = %d, y = %d, rule = Langtons-Loops\n", width, height);
            map = (char *)calloc(*width * *height, 1);
            fscanf(fileRLE, "%c", &pointer);
        }
        if(pointer == '#'){
            while(pointer != '\n'){
                fscanf(fileRLE, "%c", &pointer);
            }
        }
        if(isdigit(pointer)){
            count *= 10;
            count += pointer - '0';
        }
        else
        if(pointer == '.'){
            if(count == 0){
                x++;
                count = 0;
            }
            else{
                x += count;
                count = 0;
            }
        }
        else
        if(pointer == '$'){
            y++;
            x = 0;
        }
        else
        if(pointer == '\n' || pointer == '!'){
            continue;
        }
        else
        if(count == 0){
            map[x+(y * *width)] = pointer-'A'+1;
            x++;
            }
        else{
            for (j = 0; j < count; ++j){
                map[x+(y * *width)] = pointer-'A'+1;
                x++;
            }
            count = 0;
        }
    }while(pointer != '!');
    fclose(fileRLE);
    return map;
}

int* read_rule(){
    FILE *fileRULE = fopen("rule.txt", "r");
    int* rule = (int*)calloc(100000, sizeof(int));
    char* str = (char *)calloc(7,1);
    int id = 0;
    int i = 0;
    for (i = 0; i < 219; ++i)
    {
        fscanf(fileRULE,"%s",str);
        id = 0;
        id += str[0]-'0';
        id *= 10;
        id += str[1]-'0';
        id *= 10;
        id += str[2]-'0';
        id *= 10;
        id += str[3]-'0';
        id *= 10;
        id += str[4]-'0';
        rule[id] = str[5]-'0'+1;
        id = 0;
        id += str[0]-'0';
        id *= 10;
        id += str[4]-'0';
        id *= 10;
        id += str[1]-'0';
        id *= 10;
        id += str[2]-'0';
        id *= 10;
        id += str[3]-'0';
        rule[id] = str[5]-'0'+1;
        id = 0;
        id += str[0]-'0';
        id *= 10;
        id += str[3]-'0';
        id *= 10;
        id += str[4]-'0';
        id *= 10;
        id += str[1]-'0';
        id *= 10;
        id += str[2]-'0';
        rule[id] = str[5]-'0'+1;
        id = 0;
        id += str[0]-'0';
        id *= 10;
        id += str[2]-'0';
        id *= 10;
        id += str[3]-'0';
        id *= 10;
        id += str[4]-'0';
        id *= 10;
        id += str[1]-'0';
        rule[id] = str[5]-'0'+1;
    }
    fclose(fileRULE);
    free(str);
    return rule;
}

int main(int argc, char **argv){
    int width;
    int height;
    int i = 0;
    int j = 0;
    int *rule = read_rule();
    char *map = read_rle(&width, &height, argv);
    while(getchar() != 'k'){
        system("clear");
        draw(map, width, height);
        turn(&map,width,height,rule);
    }
    free(rule);
    free(map);
    //system("color 02");
    return 0;
}