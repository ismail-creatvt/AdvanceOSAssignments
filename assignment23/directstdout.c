/**
14. Write a C program to implement the following unix/linux command
i. ls –l > output.txt
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<errno.h>

void main(){
	int fd = open("output.txt",O_CREAT|O_RDWR);
	dup2(fd, STDOUT_FILENO);
	lseek(fd, 0, SEEK_END);
	printf("This will be written to output.txt");
}
