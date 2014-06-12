/* using pipe popen fread to using pipe */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void){
	FILE *read_fp;
	char buffer[BUFSIZ+1];
	int chars_read;
	memset(buffer,'\0',sizeof(buffer)); // 將buffer填滿 \0
	read_fp=popen("uname -a","r");  // read_fp 指向 uname -r 的輸出結果
	if(read_fp != NULL){
		chars_read=fread(buffer,sizeof(char),BUFSIZ,read_fp); read_fp寫入buffer
		if(chars_read>0){
			printf("Output was:-\n%s\n",buffer);
		}
		pclose(read_fp);
		exit(EXIT_SUCCESS);
	}
}
