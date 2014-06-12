/* client 端程式*/
#include "client.h"
#include <ctype.h>

int main(void){
	int server_fifo_fd,client_fifo_fd;
	struct data_to_pass_st my_data;
	int times_to_send;
	char client_fifo[256];

	server_fifo_fd = open(SERVER_FIFO_NAME,O_WRONLY); //打開server端的fifo 寫only
	if(server_fifo_fd==-1){
		fprintf(stderr,"Sorry , no server \n");
		exit(EXIT_FAILURE);
	}
	
	my_data.client_pid=getpid();// 寫入pid作為識別
	sprintf(client_fifo,CLIENT_FIFO_NAME,my_data.client_pid); // 將pid寫入路徑裡面 作為識別檔案 並填入char矩陣
	if(mkfifo(client_fifo,0777)==-1){ // 製作pipe檔案
		fprintf(stderr,"Sorry, can not make %s\n",client_fifo);
		exit(EXIT_FAILURE);
	}
	
	for(times_to_send=0;times_to_send<5;times_to_send++){
		sprintf(my_data.some_data,"Hello from %d",my_data.client_pid);
		printf("%d send %s, ", my_data.client_pid,my_data.some_data);
		write(server_fifo_fd,&my_data,sizeof(my_data));
		
		// 從這邊開始作"讀"的動作  		
		client_fifo_fd=open(client_fifo,O_RDONLY);
		if(client_fifo_fd != -1){
			if(read(client_fifo_fd,&my_data,sizeof(my_data))>0){
				printf("received: %s \n",my_data.some_data);
			}
			close(client_fifo_fd);
		}
	}
	close(server_fifo_fd);
	unlink(client_fifo);
	exit(EXIT_SUCCESS);
}
