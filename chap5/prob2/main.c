#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BURFSIZE 1024

int main(int argc, char *argv[])
{
	char buffer[BURFSIZE];
	int fd;
	ssize_t nread;
	long total = 0;
	
	if((fd = open(argv[1], O_RDWR)) == -1)
		perror(argv[1]);

	while((nread = read(fd, buffer, BURFSIZE)) > 0)
		total += nread;
	
	close(fd);
	printf("%s File Size : %ld Byte\n", argv[1], total);
	exit(0);
}

