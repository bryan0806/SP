/* client 端程式*/
#include "client2.h"
#include <ctype.h>

int main(void){
	int server_fifo_fd,client_fifo_fd;
	struct data_to_pass_st my_data;
	int times_to_send;
	pid_t pid;	

	mkfifo(CLIENT_FIFO_NAME,0777);
	printf("open client file\n");
	printf("start to enter some: \n");
	scanf("%s",my_data.some_data);
	

	server_fifo_fd = open(SERVER_FIFO_NAME,O_WRONLY); //打開server端的fifo 寫only
	if(server_fifo_fd==-1){
		fprintf(stderr,"Sorry , no server \n");
		exit(EXIT_FAILURE);
	}

	client_fifo_fd = open(CLIENT_FIFO_NAME,O_RDONLY); //打開server端的fifo 寫only
	if(client_fifo_fd==-1){
		fprintf(stderr,"Sorry , no server \n");
		exit(EXIT_FAILURE);
	}
	
	pid=fork();

	if(pid){ // parent
		while(1){
			scanf("%s",my_data.some_data);
			write(server_fifo_fd,&my_data.some_data,sizeof(my_data.some_data));
		}
			
	}else{ // child process
		read(client_fifo_fd,

	}

	
	
	close(server_fifo_fd);
	unlink(client_fifo);
	exit(EXIT_SUCCESS);
}
