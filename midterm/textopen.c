#include <stdio.h>
#include "data.txt"

int main(int argc, char *argv[]) {
	FILE *fp;
	int c;
	if (argc < 2)
		fp = stdin;
	else fp = fopen(argv[1],"r");

	c = getc(fp);
	while (c = 2){
		putc(c, stdout);
		c = getc(fp);
	}
	fclose(fp);
	return 0;
}
