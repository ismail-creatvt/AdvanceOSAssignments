/**
13. Write a C program to display all the files from current directory whose size is greater that n Bytes
Where n is accept from user.
*/
#include <stdio.h> 
#include <dirent.h> 
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
void main(int argc, char **argv) 
{ 
    struct dirent *de;
  	struct stat fstat;
  	struct tm *timeinfo;

  	if(argc != 2){
  		printf("no size value passed\n");
  		exit(1);
  	}
  	int size = atoi(argv[1]);
  	if(size <0){
  		printf("invalid size value : size should be non negative\n");
  		exit(1);
  	}
    DIR *directory = opendir("."); 
    char **filenames;

    if (directory == NULL)
    { 
        printf("Could not open current directory" ); 
        return;
    } 
    while ((de = readdir(directory)) != NULL) 
            if(strcmp(de->d_name,".") != 0 && strcmp(de->d_name,"..")){
                stat(de->d_name,&fstat);
                if(fstat.st_size > size){
                    printf("%s\n",de->d_name );
                }
            }
    closedir(directory);
}