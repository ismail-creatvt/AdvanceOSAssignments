/**
17. Write a C program that behaves like a shell (command interpreter). It has its own prompt say “NewShell$”.
Any normal shell command is executed from your shell by starting a child process to execute the system
program corresponding to the command. It should additionally interpret the following command.
i)
ii)
iii)
list f <dirname> - print name of all files in directory
list n <dirname> - print number of all entries
list i<dirname> - print name and inode of all files
*/


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<dirent.h>
int occurrence(char *str, char ch){
	int count = 0;
	for (int i = 0; str[i] != '\0'; ++i) {
        if (ch == str[i])
            ++count;
    }
    return count;
}

void typeline_process(char **arguments, int argc){
	if(argc != 3){
		printf("Invalid arguments\n");
		exit(1);
	}
	FILE *fp = fopen(arguments[2],"r");
	char c;
	if(arguments[1][0] == '+'){
		int lines = atoi(arguments[1]);
		printf("lines : %d\n", lines);
		fseek(fp, lines, SEEK_SET);
		int lineCount = 0;
		while((c = fgetc(fp)) != EOF || lineCount < lines){
			if(c == '\n') lineCount++;
			fputc(c, stdout);
		}
	} else if(arguments[1][0] == '-'){
		int lines = atoi(arguments[1]);
		printf("lines : %d\n", lines);
		fseek(fp, lines, SEEK_END);
		while((c = fgetc(fp)) != EOF) {
			fputc(c, stdout);
		}
	} else if(strcmp(arguments[1],"a")==0){
		while((c = fgetc(fp)) != EOF){
			fputc(c, stdout);
		}
	}
	fclose(fp);
}

void main(){
	char *cmd = (char*) malloc(50 * sizeof(char));	
	char *delimeter = " ";
	int status;
	char username[20];
	getlogin_r(username, 20);
	while(1){
		printf("%s$ ",username);
		fgets(cmd, 50, stdin);
		if(cmd[strlen(cmd)-1] == '\n'){
			cmd[strlen(cmd)-1] = '\0';
		}
		int occur = occurrence(cmd,' ');
		int argc = occur +1;
		char **arguments = (char**) malloc((argc + 1)*sizeof(char*));
		int i=0;
		char *token = strtok(cmd, delimeter);
		int len = strlen(token);
		arguments[i] = malloc(len);
		strcpy(arguments[i],token);
		i++;
		while(i <= occur){
			token = strtok(NULL, delimeter);
			int len = strlen(token);
			arguments[i] = malloc(len);
			strcpy(arguments[i],token);
			i++;
		}

		if(fork()==0){
			if(strcmp(arguments[0],"typeline") == 0){
				typeline_process(arguments, argc);
				exit(0);
			} else{
				execvp(arguments[0],arguments);
			}
		}
		while(wait(&status)>0);
		free(arguments);
	}
}