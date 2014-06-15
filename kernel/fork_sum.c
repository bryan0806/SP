/* 作業：寫一隻程式fork_sum.c 產生子處理執行 1+2...+10之後 
 * 將結果55傳回父處理之後 由父處理列印55*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "client2.h"

int main(){
	int server_fifo_fd;
	pid_t pid;
	struct data_to_pass_st my_data;
	printf("fork program starting\n");
	pid=fork();
	int exit_code,result;
	mkfifo(SERVER_FIFO_NAME,0777);

	switch(pid){
	case -1:
		perror("fork failed");
	case 0:
		server_fifo_fd=open(SERVER_FIFO_NAME,O_RDONLY);
		printf("enter child\n");
		//result=system("./sum_for_child"); be careful !!! result is system return value which is not what I think what it is.
		//sytem("./sum_for_child");
		//result = `$?`;// still can not get result, teacher said must using IPC?
		if(read(server_fifo_fd,&my_data,sizeof(my_data))>0){
			
		printf("result is %d\n",my_data.client_pid);
		
		}
	case 1:
		printf("enter father\n");
		execlp("/Users/apple/Documents/embedded/sp/kernel/sum_for_child","sum_for_child","",0);

	}
	
}
