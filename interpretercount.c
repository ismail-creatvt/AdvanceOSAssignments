#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int occurrence(char *str, char ch){
	int count = 0;
	for (int i = 0; str[i] != '\0'; ++i) {
        if (ch == str[i])
            ++count;
    }
    return count;
}

void main(){
	char cmd[100];	
	char *delimeter = " ";	
	while(1){
		printf("$ ");
		fflush(stdin);
		fgets(cmd, sizeof(cmd), stdin);
		cmd[strlen(cmd)-1] = '\0';
		printf("%s", cmd);
		int occur = occurrence(cmd,' ');
		char arguments[occur+2][100];
		int i=0;
		strcpy(arguments[i],strtok(cmd, delimeter));
		while(i <= occur){
			strcpy(arguments[i],strtok(NULL, delimeter));
			i++;
		}
		*arguments[i] = NULL;
		for(i=0;i<occur+2;i++){
			printf("%s\n", arguments[i]);
		}
		execvp(arguments[0],arguments);
	}
}