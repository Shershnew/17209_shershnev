#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char filename[13], cmd[600];
	strcpy(filename, argv[1]);
	printf("%s\n", filename);
	return 0;
}