/* 追加使用fork 讓父process read 子process write
 使用pipe 函數 可指定file_descriptor*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void){
	int data_processed;
	int file_pipes[2];
	const char some_data[]="123";
	char buffer[BUFSIZ+1];
	pid_t fork_result;
	memset(buffer,'\0',sizeof(buffer));
	if(pipe(file_pipes)==0){ // 如果file_descriptor 是2個int 矩陣 回傳0
		fork_result=fork(); // 這邊開始 父子 同時開始動作
		if(fork_result == -1){ // error handling 
			fprintf(stderr,"fork failure");
			exit(EXIT_FAILURE);
		}	
		if(fork_result==0){ // in the child process
		data_processed=read(file_pipes[0],buffer,BUFSIZ);
		printf("Read %d bytes: %s \n",data_processed,buffer);
		exit(EXIT_SUCCESS);
		}else{  // in the parent process
		data_processed=write(file_pipes[1],some_data,strlen(some_data));
		printf("Wrote %d bytes\n",data_processed);
		}
	}
	exit(EXIT_FAILURE);
}
