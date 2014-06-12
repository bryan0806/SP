/* fifo3.c :named pipe 實做  */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO_NAME "/tmp/my_fifo" // pipe name
#define BUFFER_SIZE PIPE_BUF
#define TEN_MEG (1024*1024*10)

int main(void){
	int pipe_fd;
	int res;
	int open_mode=O_WRONLY;
	int bytes_sent=0;
	char buffer[BUFFER_SIZE+1];
	if(access(FIFO_NAME,F_OK)==-1){ // 如果管線檔案不存在 
		res=mkfifo(FIFO_NAME,0777);
		if(res!=0){
			fprintf(stderr,"Count not create fifo %s\n",FIFO_NAME);
			exit(EXIT_FAILURE);
		}
	}
	
	printf("Process %d opening FIOF O_WRONLY\n",getpid());
	pipe_fd=open(FIFO_NAME,open_mode);
	printf("Process %d result %d\n",getpid(),pipe_fd);

	if(pipe_fd!= -1){ // 表示有東西進去了？？
		while(bytes_sent < TEN_MEG){
			res=write(pipe_fd,buffer,BUFFER_SIZE);
			if(res==-1){
				fprintf(stderr,"Write error on pipe\n");
				exit(EXIT_FAILURE);
			}
			bytes_sent += res; // 每次寫入的位元累計
		}
		(void)close(pipe_fd);

	}else{  // pipe_fd == -1
		exit(EXIT_FAILURE);
	}
	printf("Process %d finished\n",getpid());
	exit(EXIT_SUCCESS);
}
