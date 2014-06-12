/* FIFO 使用open 技巧 以及指令參數來決定 用 O_RDONLY or O_WRONLY*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO_NAME "/tmp/my_fifo"

int main(int argc,char *argv[]){
	int res;
	int open_mode=0;
	int i;
	if(argc<2){
		fprintf(stderr,"Usage: %s <some combination of\
O_RDONLY O_WRONLY O_NONBLOCK>\n",*argv);
	exit(EXIT_FAILURE);
	}
	
	for(i=1;i<argc;i++){
		if(strncmp(*++argv,"O_RDONLY",8)==0)//這一行讓argv每次可增加一（如果有三個參數 則會依序比對） if argv[1]=O_RDONLY
			open_mode |= O_RDONLY;
		if(strncmp(*argv,"O_WRONLY",8)==0)//if argv[1]=O_WRONLY
			open_mode |= O_WRONLY;
		if(strncmp(*argv,"O_NONBLOCK",10)==0)
			open_mode |= O_NONBLOCK; // | 的功能是 原本是0 則 結果 0 原本是1結果1

	}

	if(access(FIFO_NAME,F_OK)==-1){
		res=mkfifo(FIFO_NAME,0777);
		if(res!=0){
			fprintf(stderr,"Count not create fifo %s\n",FIFO_NAME);
			exit(EXIT_FAILURE);
		}
	}
	printf("Process %d opening FIFO\n",getpid());
	res=open(FIFO_NAME,open_mode);
	printf("Process %d result %d\n",getpid(),res);
	sleep(5);
	if(res!=-1) (void)close(res);
	printf("Process %d finished\n",getpid());
	exit(EXIT_SUCCESS);	

}
