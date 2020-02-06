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

void sighup(){
	printf("SIGHUP received\n");
}

void sigint(){
	printf("SIGINT received\n");
}

void sigquit(){
	printf("My DADDY has Killed me!!!\n");
	exit(0);
}

void main(){
	int pid;

	pid = fork();

	if(pid<0){
		fprintf(stderr, "Fork failed\n");
		exit(1);
	}

	if(pid == 0){
		signal(SIGHUP, sighup);
		signal(SIGINT, sigint);
		signal(SIGQUIT, sigquit);

		while(1);
	} else{
		int timer = 0;
		while(timer<30){
			sleep(3);
			kill(pid, SIGHUP);
			timer+=3;
			sleep(3);
			kill(pid, SIGINT);
			timer+=3;
		}
		kill(pid, SIGQUIT);
		int status;
		while(wait(&status)>0);
	}
}