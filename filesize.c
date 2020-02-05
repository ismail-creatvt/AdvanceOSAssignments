/**
9. To print the size of the file.
*/
#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>

void main(int argc, char **argv){
	if(argc < 2){
		printf("No file name passed\n");
		exit(0);
	}
	int fd = open(argv[1], O_RDONLY);
	struct stat filestat;
	int ret = fstat(fd, &filestat);

	printf("Size of %s is %ld bytes.\n", argv[1], filestat.st_size);
}