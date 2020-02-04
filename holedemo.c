#include<stdio.h>
#include<stdlib.h>
void main(){
	int fd = open("hole.txt","w+");
	char message[] = "This is a demonstration";
	char message2[] = " for hole in a file.";
	write(message, 1, sizeof(message), fp);
	seek(fp, sizeof(message) + 10, SEEK_SET);
	fwrite(message2, 1, sizeof(message2), fp);
	system("od -c hole.txt");
}