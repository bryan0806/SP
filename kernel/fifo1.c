/* 使用 mkfifo 函數來建立 pipe 檔案*/
// 其中一個視窗使用 cat < /tmp/my_fifo
// 另外一個打 echo "Hello World" > /tmp/my_fifo 
// 會在第一個顯示hello world
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void){
	int res=mkfifo("/tmp/my_fifo",0777);
	if(res=0)
		printf("FIFO created\n");
	exit(EXIT_SUCCESS);
}
