#include <stdio.h>
#include "client2.h"



int main(void){
	struct data_to_pass_st my_data;
	int server_fifo_fd;
	server_fifo_fd=open(SERVER_FIFO_NAME,O_WRONLY);
	if(server_fifo_fd==-1){
		fprintf(stderr,"Sorry, no server");
		exit(EXIT_FAILURE);
	}
	int sum=0;	
	int i;
	for(i=1;i<=10;i++){
	sum += i;

	}	
	my_data.client_pid=sum;
	//printf("%d",sum);
	write(server_fifo_fd,&my_data,sizeof(my_data));
	
}
