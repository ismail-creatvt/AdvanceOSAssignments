#include<sys/resource.h>
#include<sys/time.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

void child_process_code(){		
	int j,k=5000;
	char filename[10];
	snprintf(filename,10,"hello");
	FILE *fp = fopen(filename,"a");
	for(j=0;j<10;j++){
		while(k--);
		k=5000;
		fprintf(fp,"%d - ",j);
	}
	fprintf(fp, "\n");
	fclose(fp);
}

void main(){
	int status = 0,i;
	pid_t wpid;
	struct rusage usage;
	for(i=0;i<10;i++){
		if(!fork()){
			child_process_code();
			exit(0);
		}
	}
	while((wpid = wait(&status))>0);
	getrusage(RUSAGE_CHILDREN, &usage);
	printf("Total time spent in user mode by children : %ld s %ld ms\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
	printf("Total time spent in kernel mode by children : %ld s %ld ms\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
}