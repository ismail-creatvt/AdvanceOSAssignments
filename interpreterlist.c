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

void list_process(char **arguments, int argc){
	if(argc != 3){
		printf("Invalid arguments\n");
		exit(1);
	}
	DIR *directory = opendir(arguments[2]); 
    struct dirent *de;
   	char **filenames;

    if (directory == NULL)
    { 
        printf("Could not open current directory" ); 
        return;
    } 
	if(strcmp(arguments[1],"f")==0){
		while ((de = readdir(directory)) != NULL) 
            if(strcmp(de->d_name,".") != 0 && strcmp(de->d_name,"..")){
                printf("%s\n", de->d_name);
            }
	} else if(strcmp(arguments[1],"n")==0){
		int fileCount = 0;
	    while ((de = readdir(directory)) != NULL) 
	            if(strcmp(de->d_name,".") != 0 && strcmp(de->d_name,"..")){
	                fileCount++;
	            }
		printf("Total files : %d\n", fileCount);
	} else if(strcmp(arguments[1],"i")==0){
		while ((de = readdir(directory)) != NULL) 
            if(strcmp(de->d_name,".") != 0 && strcmp(de->d_name,"..")){
                printf("%s -> %ld\n",de->d_name, de->d_ino);
            }
	}
	closedir(directory);
}

void main(){
	char *cmd = (char*) malloc(100 * sizeof(char));	
	char *delimeter = " ";
	int status;
	char username[20];
	getlogin_r(username, 20);
	while(1){
		printf("%s$ ",username);
		fgets(cmd, 100, stdin);
		if(cmd[strlen(cmd)-1] == '\n'){
			cmd[strlen(cmd)-1] = '\0';
		}
		if(cmd[strlen(cmd)-1] == ' '){
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
			if(strcmp(arguments[0],"list") == 0){
				list_process(arguments, argc);
				exit(0);
			} else{
				execvp(arguments[0],arguments);
			}
		}
		while(wait(&status)>0);
		free(arguments);
	}
}