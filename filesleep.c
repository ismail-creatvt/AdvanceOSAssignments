/**
8. Open a file goes to sleep for 15 seconds before terminating.
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void main(){
	FILE *fp = fopen("pattern.txt","w");
	printf("Opened file: pattern.txt\n");
	sleep(15);
	for(int i=0;i<4;i++){
		for(int j=0;j<=i;j++){
			fprintf(fp,"*");
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}