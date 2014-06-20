// server5.c 修改使用select()變成一次可以處理多的程序的server
//
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/ioctl.h>

int main(void){
	int server_sockfd,client_sockfd;
	int server_len,client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	int result;
	fd_set readfds,testfds;

	/* 產生伺服器的 socket 並加以命名 */
	server_sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	/* Name the socket */
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=htonl(INADDR_ANY);
	server_address.sin_port=htons(9734);
	server_len=sizeof(server_address);
    bind(server_sockfd,(struct sockaddr *)&server_address,server_len);
	
	/* Create a connection queue and wait for clients */
	listen(server_sockfd,5);
	
	// 初始並設定readfds , 以便處理來自server_sockfd 的輸入
	FD_ZERO(&readfds);
	FD_SET(server_sockfd,&readfds);


	// 等待客戶端和請求 因為你將timeout 參數輸入空指標 所以不會有
	//過時狀況 如果select回復一個小於1的數值 程式就會離開

	while(1){
	    char ch;
		int fd;
		int nread;

		testfds = readfds; // 這邊需要在拷貝一次的原因是 若在處理過程中有新的檔案描述子加入 可確保不會被忽略 而在下次的回圈中被拷貝進去

		printf("server waiting\n");
		// select 第一個參數為要掃描的數量 FD_SETSIZE=256 所以會掃描0~255
		// 第二個參數為 readfd的 set 第三個參數為writefd set
		//第四個參數為error fd 的set 最後為等待時間
		result = select(FD_SETSIZE,&testfds,(fd_set *)0,(fd_set *)0,(struct timeval *) 0);

		if(result < 1){
			perror("server5");
			exit(1);
		}
		//一旦知道有狀況發生 可以利用FD_ISSET 檢查是哪一個描述子的狀況
		for(fd=0;fd<FD_SETSIZE;fd++){
			if(FD_ISSET(fd,&testfds)){  // 通常用FD_ISSET 來檢查是否有資料讀入或著是寫出 如果有回傳1 
				//如果是server_sockfd 上的動靜 就表示有新的連結請求
				//接受連結後 應該將相關的client_sockfd 加到描述子集合中
				if(fd==server_sockfd){
					client_len = sizeof(client_address);
					client_sockfd=accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);
					FD_SET(client_sockfd,&readfds);
					printf("adding client on fd %d\n",client_sockfd);
				}else{ // 如果不是伺服器描述子的時候 那就是客戶端的狀況 
				// 如果收到關閉的狀況 也就是客戶端已經離線 就應該把他從集合中刪除 
				ioctl(fd,FIONREAD,&nread); // ioctl 功能很多 這邊FIONREAD 是用來看有多少個位元的資料 在fd裏面等待被讀取
				
				if(nread==0){ // 這邊老師說 是client端要求斷線時 會送出一個沒有位元的特殊信號
					close(fd);
					FD_CLR(fd,&readfds);
					printf("removing client on fd %d\n",fd);
				}else{
					read(fd,&ch,1);
					sleep(5);
					printf("serving client on fd %d\n",fd);
					ch++;
					write(fd,&ch,1);
				}

				}
			}
		}
	

	}
}
