/**
21. Write a C program which create a child process which catch a signal sighup, sigint and sigquit. The Parent
process send a sighup or sigint signal after every 3 seconds, at the end of 30 second parent send sigquit signal
to child and child terminates my displaying message "My DADDY has Killed me!!!”.
*/
#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>

void main(){
	int pid;

	pid = fork();

	if(pid<0){
		fprintf(stderr, "Fork failed\n");
		exit(1);
	}

	if(pid == 0){
		while(1){
			usleep(500*1000);
			printf("Running\n");		
			fflush(stdout);
		}
	} else{
		int timer = 0;
		while(timer<10){
			sleep(2);
			kill(pid, SIGSTOP);
			timer+=2;
			sleep(2);			
			kill(pid, SIGCONT);
			timer+=2;
		}
		kill(pid, SIGQUIT);
		int status;
		while(wait(&status)>0);
	}
}
