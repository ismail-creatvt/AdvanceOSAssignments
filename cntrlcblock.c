/**
22. Write a C program to implement the following unix/linux command (use fork, pipe and exec system
call). Your program should block the signal Ctrl-C and Ctrl-\ signal during the execution.
i. ls –l | wc –l
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<errno.h>
#include<signal.h>

void sigint(){

}

void main(){
	int filedes[2];
	if (pipe(filedes) == -1) {
		perror("pipe");
		exit(1);
	}
	signal(SIGINT, sigint);
	if(fork() == 0){
		while ((dup2(filedes[1], STDOUT_FILENO) == -1)) {}
		char *args[] = {"ls","-l", NULL};
		int ret = execvp("ls",args);
		if(ret <0){
			printf("Program can't be executed\n");
		}
		exit(0);
	}
	close(filedes[1]);
	if(fork() == 0){
		while((dup2(filedes[0], STDIN_FILENO) == -1)){}
		char *args[] = {"wc","-l", NULL};
		int ret = execvp("wc",args);
		if(ret <0){
			printf("Program can't be executed\n");
		}
		exit(0);
	}
	char output[100];
	read(filedes[0], output, 100);
	printf("%s", output);
	close(filedes[0]);
	// exit(0);
	int i=0;
	while(i<2000000000) i++;
}