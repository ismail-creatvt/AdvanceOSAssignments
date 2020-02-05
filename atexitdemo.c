/**
7. To demonstrate the use of atexit() function.
*/
#include<stdio.h>
#include<stdlib.h>

FILE *fp;

void call_on_exit(){
	fclose(fp);
	printf("Program is done executing\n");
	printf("pattern.txt closed\n");
}

void main(){
	atexit(call_on_exit);
	fp = fopen("pattern.txt","w");
	printf("Opened file: pattern.txt\n");
	for(int i=0;i<4;i++){
		for(int j=0;j<=i;j++){
			fprintf(fp,"*");
		}
		fprintf(fp,"\n");
	}
}