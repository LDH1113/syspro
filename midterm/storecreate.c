#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "db.dat"
#define  MAX 24
#define START_ID 

int main(int argc, char *argv[]) {
	int fd;
	struct inf record;
	
	struct inf {
		int id;
		char name[MAX];
		char category[MAX];
		int expired_date;
		int stock;
	};

	if (argc < 2)
		fp = stdin;
	else fp = fopen(argv[1],"r");

	if((fd = open(argv[1], O_WRONLY|O_CREAT|O_EXCL, 0640)) == -1) {
		perror(argv[1]);
		exit(2);
	}
	printf("%-15s %-14s %-9s %5s %-2s", "id", "name", "category", "expired date", "stock");
	while (scanf("%d %s %s %d %s", &record.id, record.name, record.category, &record.expired_date, record.stock) == 5) {
		lseek(fd, (record.id - START_ID) *sizeof(record), SEEK_SET);
		write(fd, (char *) &record, sizeof(record));
	}
	close(fd);
	exit(0);
}
