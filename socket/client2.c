// client2.c client輸入一字元 server 加一回傳
//
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(void){
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char ch='A';	
	
	/* Create a socket for the client */
	sockfd=socket(AF_INET,SOCK_STREAM,0); 
	/* Name the socket as agreed with the server*/
	address.sin_family=AF_INET; // 地址是以結構體儲存
	address.sin_addr.s_addr=inet_addr("127.0.0.1"); // 寫上server ip
	address.sin_port=9734;
	len=sizeof(address);
	/* Now connect our socket to the server's socket */
	result=connect(sockfd,(struct sockaddr *)&address,len);// connect使用此格式
	if(result == -1){
		perror("oops:client2");
		exit(1);
	}
	/* We can now read/write via sockfd */
    write(sockfd,&ch,1); // server端有一個read在等待
	read(sockfd,&ch,1); //等待server端回傳write
	printf("char from server = %c\n",ch);
	close(sockfd);
	exit(0);
	}
