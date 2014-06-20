/* 這個程式展示 select() 的用法 */
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	char buffer[128];
	int result,nread;

	fd_set inputs,testfds;
	struct timeval timeout;

	FD_ZERO(&inputs);
	FD_SET(0,&inputs);

	// 在stdin 上等待輸入 最長2.5秒
	while(1){
		testfds = inputs;
		timeout.tv_sec = 2;
		timeout.tv_usec=500000;

		result=select(FD_SETSIZE,&testfds,(fd_set *)NULL,(fd_set *)NULL,&timeout);
		// 此時 檢驗result 如果沒有輸入 程式會繼續回圈 如果有錯誤則離開
		switch(result){
		case 0:
			printf("timeout\n");
			break;
		case -1:
			perror("select");
			exit(1);
		// 程式等待過程中 如果有動作 則會從stdin(檔案描述子為0)	讀取輸入並把它印出
		default:
			if(FD_ISSET(0,&testfds)){  // 如果0是testfds的集合中的一個 則回回傳一個非零的值
				ioctl(0,FIONREAD,&nread);
/* ioctl ioctl是應用程式用來和驅動程式溝通的API 讓應用程式可以
對某個裝置下命令你想要用ioctl做什麼事呢?在unix環境中, 
裝置的存取和檔案是一樣的一般會先用open函式來取得對裝置的一個控制權
open會傳回一個handle值
一般用法 ioctl(handle, command, ...)
前面兩個參數是必須的, 後面的參數則視情況而定handle就是open函式傳回來的值
command就是一個command code command code每個值所代表的命令會因裝置而異
完全由驅動程式來解釋command code的意義 有的command code還需要
傳進額外的參數時, 就會使用第3, 第4...個參數了
FIONREAD:Return in the integer pointed to by the third argument 
to ioctl the number of bytes currently in the socket receive buffer. 
This feature also works for files, pipes, and terminals.*/
				if(nread==0){
				printf("keyboard done\n");
				exit(0);
				}
			nread=read(0,buffer,nread);
			buffer[nread]=0;
			printf("read %d from keyboard: %s",nread,buffer);
		}
		break;
	}
}
}
