/**
3. To create a file with hole in it.
*/
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

void main(){
	int fd = open("hole.txt",O_CREAT|O_RDWR);
	system("chmod 722 hole.txt");
	char message[] = "This is a demonstration";
	char message2[] = " for hole in a file.";
	write(fd, message, sizeof(message)); //write first part
	lseek(fd, 10, SEEK_END); //adding hole of 10 characters
	write(fd, message2, sizeof(message2));//write second part
	system("od -c hole.txt");
}
