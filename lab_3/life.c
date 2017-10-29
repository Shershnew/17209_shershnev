#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#ifdef _WIN32
#include <conio.h>
#include <Windows.h>
#endif

void draw(char *map, int width, int height){
    int i = 0;
    int j = 0;
    int r = 0;
    #ifdef _WIN32
    int lastchar = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif
    for (i = 0; i < height; ++i)
    {
        for (j = 0; j < width; ++j)
        {
            r = *(map+j+(i * width));
            if(r == 0){
                #ifdef _WIN32
                if(lastchar != 1){
                    SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 0));
                    lastchar = 1;
                }
                #endif
                printf(" ");
            }
            else{
                #ifdef _WIN32
                lastchar = 0;
                if(r == 1){ 
                    SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 9));
                }
                else
                if(r == 2){
                    SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 4));
                }
                else
                if(r == 3){
                    SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 3));
                }
                else
                if(r == 4){
                    SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 2));
                }
                else
                if(r == 5){
                    SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 5));
                }
                else
                if(r == 6){
                    SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 6)); 
                }
                else
                if(r == 7){
                    SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 7));
                }
                printf("*");
                #else
                printf("%d", r);
                #endif
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
            for (k = 0; k < 5; k++){
            id *= 10;
            id += (int)tec[k];
            }
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
    if(NULL == fileRLE){
        return 0;
    }
    int x = 0;
    int y = 0;
    int i = 0;
    int j = 0;
    int count = 0;
    char c = ' ';
    char *map;
    char pointer;
    do{
        if(fscanf(fileRLE,"%c",&pointer) == -1){
            break;
        }
        if(pointer == 'x'){
            fscanf(fileRLE," = %d, y = %d", width, height);
            while (c != '\n'){
                fscanf(fileRLE,"%c",&c);
            }
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

int* read_rule(char **argv){
    FILE *fileRULE = fopen(argv[2], "r");
    if(NULL == fileRULE){
        return 0;
    }
    int* rule = (int*)calloc(77778, sizeof(int));
    char* str = (char *)calloc(7,1);
    int id = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    for (i = 0; i < 219; ++i)
    {
        fscanf(fileRULE,"%s",str);
        for (j = 0; j < 4; j++){
            id = 0;
            id += str[0]-'0';
            for (k = 0; k < 4; k++){
                id *= 10;
                id += str[(k+j)%4+1]-'0';
            }
            rule[id] = str[5]-'0'+1;
        }
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
    if(argc < 3 || argc == 4){
            printf("Need input files\n");
            return 0;
    }
    int *rule = read_rule(argv);
    char *map = read_rle(&width, &height, argv);
    if(rule == 0 || map == 0){
        printf("Error input filename\n");
        return 0;
    }
    if(argc == 3){
        while(getchar() != 'k'){
            #ifdef _WIN32
            system("cls");
            #else
            system ("clear");
            #endif
            draw(map, width, height);
            turn(&map,width,height,rule);
        }
        free(rule);
        free(map);
        #ifdef _WIN32
        system("color 0f");
        #endif
    }else{
        int count  = atoi(argv[4]);
        FILE * fwrite = fopen(argv[3],"w");
        if(count == 0 || fwrite == 0){
            printf("Error input parametr\n");
            return 0;
        }
        for(i = 0; i < count; i++){
            turn(&map,width,height,rule);   
        }
        for(i = 0; i < height; i++){
            for(j = 0; j < width; j++){
                if(map[j+(i*width)] == 0){
                    fprintf(fwrite, " ");
                }else{
                    fprintf(fwrite, "%c", map[j+(i*width)]+'0');
                }
            }
            fprintf(fwrite, "\n");
        }
        fclose(fwrite);
        free(rule);
        free(map);
    }
    return 0;
}