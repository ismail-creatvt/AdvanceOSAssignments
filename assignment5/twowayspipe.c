/**
5. To handle the two-way communication between parent and child using pipe.
*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define READ_FD 0
#define WRITE_FD 1

int openpipe(int pipno,int pipefd[2]){
   int ret = pipe(pipefd);
   if(ret < 0){
      fprintf(stderr,"Unable to open pipe %d",pipno);
      return 0;
   }
   return 1;
}

void parent_process_code(int pipe1[], int pipe2[]){
      char readMessage[20], message[] = "Hi, How are you?";
      printf("In Parent: Writing Message : %s\n", message);
      write(pipe1[WRITE_FD], message, sizeof(message));
      read(pipe2[READ_FD], readMessage, sizeof(readMessage));
      printf("In Parent: Reading Message : %s\n", readMessage);
}

void child_process_code(int pipe1[], int pipe2[]){
      char readMessage[20], message[] = "I'm fine";
      read(pipe1[READ_FD], readMessage, sizeof(readMessage));
      printf("In Child: Reading Message : %s\n", readMessage);
      printf("In Child: Writing Message : %s\n", message);
      write(pipe2[WRITE_FD], message, sizeof(message));
}

int main() {
   int pipe1[2], pipe2[2];
   
   //if pipe1 or pipe2 can't be opened then exit
   if(!openpipe(1,pipe1) || !openpipe(2, pipe2)) exit(1);
   
    int pid = fork();
   if(pid < 0){
	fprintf(stderr,"Fork can't be executed");
	exit(1);   
   }
   if (pid == 0) {// Parent process 
      parent_process_code(pipe1,pipe2);
   } else { //child process
      child_process_code(pipe1,pipe2);
   }
   return 0;
}
