#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
void main(int argc, char **argv){
	int i,ret;
	int fd[argc-1];
	struct stat filestat;
	printf("Inode Numbers are ...\n");
	for(i=1;i<argc;i++){
		fd[i-1] = open(argv[i],O_RDONLY);
		ret = fstat(fd[i-1],&filestat);
		printf("%s : ",argv[i]);
		if(ret < 0){
			printf("error reading filestat\n");
		} else{
			printf("%ld\n", filestat.st_ino);
		}
	}
}