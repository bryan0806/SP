/* server 端程式*/
#include "client2.h"
#include <ctype.h>

int main(void){
	int server_fifo_fd,client_fifo_fd;
	struct data_to_pass_st send_data,rec_data;
	int times_to_send;
	pid_t pid;	
	int res;
	
	res=mkfifo(SERVER_FIFO_NAME,0777);
	printf("open server file %d\n",res);
	

	server_fifo_fd = open(SERVER_FIFO_NAME,O_RDONLY); //打開server端的fifo 寫only
	if(server_fifo_fd==-1){
		fprintf(stderr,"Sorry , no client file \n");
		exit(EXIT_FAILURE);
	}

	client_fifo_fd = open(CLIENT_FIFO_NAME,O_WRONLY); //打開server端的fifo 寫only
	if(client_fifo_fd==-1){
		fprintf(stderr,"Sorry , no server \n");
		exit(EXIT_FAILURE);
	}
	
	pid=fork();

	if(pid){ // parent
		while(1){
			printf("start to enter some: \n");
			scanf("%s",send_data.some_data); // scanf 不可讀取包含空白的一行
			write(client_fifo_fd,&send_data,sizeof(send_data));
		}
			
	}else{ // child process
		while(1){
		read(server_fifo_fd,&rec_data,sizeof(rec_data));
		printf("client said %s\n",rec_data.some_data);
		}
	}
	
	
	close(client_fifo_fd);
	exit(EXIT_SUCCESS);
	}

