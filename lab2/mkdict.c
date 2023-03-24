#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mkdict(char* filename)
{
	FILE* file = fopen(filename, "w");
	if(file == NULL)
		exit(1);
	for(int i = 0; i < 400000; i++) {
		for(int j = 0; j < 8; j++) {
			fprintf(file, "%c", rand() % 26 + 97);
		}
		fprintf(file, "\n");
	}
	fclose(file);
}

int main()
{
	mkdict("slova.txt");
	return 0;
}
