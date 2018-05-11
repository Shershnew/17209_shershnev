#include <stdio.h>
#include <stdlib.h>

void printdes(int ** mas, int w, int h){
	for (int i = 0; i < w; ++i)
	{
		printf("\n");
		for (int j = 0; j < h; ++j)
		{
			printf("%d\t", mas[i][j]);
		}
	}
}

int countheighbors(int ** mas, int x, int y, int w, int h){
	int count = 0;
	if(x < 0 || x >= w || y < 0 || y >= h){
		return 9;
	}
	if(x + 2 < w && y + 1 < h && mas[x+2][y+1] == 0){
		count++;
	}
	if(x + 2 < w && y - 1 >= 0 && mas[x+2][y-1] == 0){
		count++;
	}
	if(x - 2 >= 0 && y + 1 < h && mas[x-2][y+1] == 0){
		count++;
	}
	if(x - 2 >= 0 && y - 1 >= 0 && mas[x-2][y-1] == 0){
		count++;
	}
	if(x + 1 < w && y + 2 < h && mas[x+1][y+2] == 0){
		count++;
	}
	if(x + 1 < w && y - 2 >= 0 && mas[x+1][y-2] == 0){
		count++;
	}
	if(x - 1 >= 0 && y + 2 < h && mas[x-1][y+2] == 0){
		count++;
	}
	if(x - 1 >= 0 && y - 2 >= 0 && mas[x-1][y-2] == 0){
		count++;
	}
	return count;
}

int findmin(int ** mas, int x, int y, int w, int h, int without){
	int min = 9;
	int mini = 9;
	int tec = 0;
	if((tec = countheighbors(mas, x+2, y+1, w, h)) < min && (without % 2 != 1) && mas[x+2][y+1] == 0){
		min = tec;
		mini = 1;
	}
	if((tec = countheighbors(mas, x+2, y-1, w, h)) < min && ((without>>1) % 2 != 1) && mas[x+2][y-1] == 0){
		min = tec;
		mini = 2;
	}
	if((tec = countheighbors(mas, x-2, y+1, w, h)) < min && ((without>>2) % 2 != 1) && mas[x-2][y+1] == 0){
		min = tec;
		mini = 3;
	}
	if((tec = countheighbors(mas, x-2, y-1, w, h)) < min && ((without>>3) % 2 != 1) && mas[x-2][y-1] == 0){
		min = tec;
		mini = 4;
	}
	if((tec = countheighbors(mas, x+1, y+2, w, h)) < min && ((without>>4) % 2 != 1) && mas[x+1][y+2] == 0){
		min = tec;
		mini = 5;
	}
	if((tec = countheighbors(mas, x+1, y-2, w, h)) < min && ((without>>5) % 2 != 1) && mas[x+1][y-2] == 0){
		min = tec;
		mini = 6;
	}
	if((tec = countheighbors(mas, x-1, y+2, w, h)) < min && ((without>>6) % 2 != 1) && mas[x-1][y+2] == 0){
		min = tec;
		mini = 7;
	}
	if((tec = countheighbors(mas, x-1, y-2, w, h)) < min && ((without>>7) % 2 != 1) && mas[x-1][y-2] == 0){
		min = tec;
		mini = 8;
	}
	return mini;
}

int findway(int ** mas, int w, int h, int x, int y, int iter){
	if(iter == w * h){
		return 1;
	}

	mas[x][y] = iter;
	unsigned int without = 0;
	int ret = 0;
	while(1){
		int mini = findmin(mas, x, y, w, h, without);
		if(mini == 9){
			mas[x][y] = 0;
			return 0;
		}
		switch(mini){
			case 1: ret = findway(mas, w, h, x+2, y+1, iter+1); if(ret == 0){ without += 1; } break;
			case 2: ret = findway(mas, w, h, x+2, y-1, iter+1); if(ret == 0){ without += 2; } break;
			case 3: ret = findway(mas, w, h, x-2, y+1, iter+1); if(ret == 0){ without += 4; } break;
			case 4: ret = findway(mas, w, h, x-2, y-1, iter+1); if(ret == 0){ without += 8; } break;
			case 5: ret = findway(mas, w, h, x+1, y+2, iter+1); if(ret == 0){ without += 16; } break;
			case 6: ret = findway(mas, w, h, x+1, y-2, iter+1); if(ret == 0){ without += 32; } break;
			case 7: ret = findway(mas, w, h, x-1, y+2, iter+1); if(ret == 0){ without += 64; } break;
			case 8: ret = findway(mas, w, h, x-1, y-2, iter+1); if(ret == 0){ without += 128; } break;
		}
		if(ret == 1){
			break;
		}
	}
	return 1;
}

int main(){
	int w = 0,h = 0;
	int x = 0, y = 0;
	scanf("%d %d", &w, &h);
	scanf("%d %d", &x, &y);
	int ** mas = (int **)calloc(w, sizeof(int *));
	for (int i = 0; i < w; ++i){
		mas[i] = (int *)calloc(h, sizeof(int));
	}
	int res = findway(mas, w, h, x, y, 1);
	printf("\n%d\n", res);
	printdes(mas, w, h);
	for (int i = 0; i < w; ++i){
		free(mas[i]);
	}
	free(mas);
	return 0;
}