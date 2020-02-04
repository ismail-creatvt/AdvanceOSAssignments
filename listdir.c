#include <stdio.h> 
#include <dirent.h> 
#include<string.h>
void main() 
{ 
    struct dirent *de;
  
    DIR *directory = opendir("."); 
  
    if (directory == NULL)
    { 
        printf("Could not open current directory" ); 
        return;
    } 
  
    int fileCount = 0;
    while ((de = readdir(directory)) != NULL) 
            if(strcmp(de->d_name,".") != 0 && strcmp(de->d_name,"..")){
                fileCount++;
                printf("%s\n", de->d_name);
            }
    printf("----------------------------------------\n");
    printf("Total file count : %d\n", fileCount);  
    closedir(directory);
}