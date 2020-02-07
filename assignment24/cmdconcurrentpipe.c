/**
11. Write a C program to implement the following unix/linux command (use fork, pipe and exec system
call)
ls –l | wc –l
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<errno.h>

void main(){
	int filedes[2];
	if (pipe(filedes) == -1) {
		perror("pipe");
		exit(1);
	}
	if(fork() == 0){
		while ((dup2(filedes[1], STDOUT_FILENO) == -1)) {}
		char *args[] = {"ls","-l", NULL};
		int ret = execvp("ls",args);
		if(ret <0){
			printf("Program can't be executed\n");
		}
	}
	
	close(filedes[1]);
	if(fork() == 0){
		close(filedes[1]);
		while((dup2(filedes[0], STDIN_FILENO) == -1)){}
		char *args[] = {"wc","-l", NULL};
		int ret = execvp("wc",args);
		if(ret <0){
			printf("Program can't be executed\n");
		}
	}
	char output[100];
	read(filedes[0], output, 100);
	printf("%s", output);
	close(filedes[0]);
	exit(0);
}
