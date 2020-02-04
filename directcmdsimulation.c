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
	int fp = open("output.txt",O_CREAT|O_WRONLY);
	if(fork() == 0){
		while ((dup2(fp, STDIN_FILENO) == -1)) {}
		char *args[] = {"ls","-l", NULL};
		int ret = execvp("ls",args);
		if(ret <0){
			printf("Program can't be executed\n");
		}
		exit(0);
	}
	
	close(filedes[1]);
	close(filedes[0]);
	exit(0);
}