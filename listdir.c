/**
10. Read the current directory and display the name of the files, no of files in current directory.
*/
#include <stdio.h> 
#include <dirent.h> 
#include<string.h>
#include<unistd.h>

void main() 
{ 
    struct dirent *de;
  
    DIR *directory = opendir("."); 
    char **filenames;

    if (directory == NULL)
    { 
        printf("Could not open current directory" ); 
        return;
    } 
  
    int fileCount = 0;
    while ((de = readdir(directory)) != NULL) 
            if(strcmp(de->d_name,".") != 0 && strcmp(de->d_name,"..")){
                fileCount++;
            }
    printf("total %d\n", fileCount);  
    printf("----------------------------------------\n");


    rewinddir(directory);
    while ((de = readdir(directory)) != NULL) 
            if(strcmp(de->d_name,".") != 0 && strcmp(de->d_name,"..")){
                printf("%s\n", de->d_name);
            }
    closedir(directory);
}