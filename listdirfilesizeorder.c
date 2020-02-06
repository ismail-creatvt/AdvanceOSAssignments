/**
20. Write a C program which receives file names as command line arguments and display those
filenames in ascending order according to their sizes.
i)(e.g $ a.out a.txt b.txt c.txt, ...)
*/
#include <stdio.h> 
#include <dirent.h> 
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>

typedef struct file_info{
  char *name;
  size_t size;
}fileinfo;

void insertionSort(fileinfo info[], int n)  
{  
    int i, j;
    fileinfo key;  
    for (i = 1; i < n; i++) 
    {  
        key = info[i];  
        j = i - 1;  
        while (j >= 0 && info[j].size > key.size) 
        {  
            info[j + 1] = info[j];  
            j = j - 1;  
        }  
        info[j + 1] = key;  
    }  
}

void main(int argc, char **argv) 
{ 
    struct stat fstat;
    if(argc < 2){
        printf("no files passed\n");
        exit(1);
    }
    int fileCount = argc -1;
    fileinfo info[fileCount];
    int i;
    for(i =1;i<argc;i++){
        info[i-1].name = argv[i];
        stat(argv[i],&fstat);
        info[i-1].size = fstat.st_size;
    }
    insertionSort(info, fileCount);
    for(i=0;i<fileCount;i++){
      printf("%s -> %ld\n", info[i].name, info[i].size);
    }
}