#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<stdlib.h>
#define MESSAGE_BLOCK_SIZE 35
#define READ 0
#define WRITE 1

void main(){
	char message[MESSAGE_BLOCK_SIZE]="This is a message to child process";
	int p[2], status;

	//if pipe can't be created exit
	if(pipe(p) < 0){
		fprintf(stderr,"Pipe can't be created");
		exit(1);	
	} 

	write(p[WRITE], message, MESSAGE_BLOCK_SIZE);

	if(!fork()){
		char message[MESSAGE_BLOCK_SIZE];
		read(p[READ], message, MESSAGE_BLOCK_SIZE);
		printf("%s\n", message);
		exit(0);
	}

	while(wait(&status) > 0);
}