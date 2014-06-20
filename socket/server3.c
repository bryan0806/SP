// server2.c client輸入一字元 server 加一回傳
//
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

int main(void){
	int server_sockfd,client_sockfd;
	int server_len,client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	/* Create an unnamed socket for the server */
	server_sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	/* Name the socket */
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=htonl(INADDR_ANY);
	server_address.sin_port=htons(9734);
	server_len=sizeof(server_address);
    bind(server_sockfd,(struct sockaddr *)&server_address,server_len);
	
	/* Create a connection queue and wait for clients */
	listen(server_sockfd,5);

	// 忽略子處理程序的離開信號 防止zombie程序 等待客戶端
	signal(SIGCHLD, SIG_IGN);

	while(1){
	    char ch;
		printf("server waiting\n");
	/*Accept a connection */
		client_len = sizeof(client_address);
		
		//執行後 會看到server waiting 字樣 所以可以知道停在accept 下面的步驟
		client_sockfd=accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);
	// server端接到client的connect之後產生一個connect socket(client socket) 然後以此cleint socket 作讀寫動作
	
	// 開始fork() !!
	if(fork()==0){ // 子處理

	/* We can now read/write to client on client_sockfd */
    read(client_sockfd,&ch,1);
	sleep(5); // 模擬伺服器計算工作 或是 存取資料時間
	ch++;
	write(client_sockfd,&ch,1);
	close(client_sockfd);
	exit(0);
	}else{  // 父處理
		close(client_sockfd);
	}
	}
}
