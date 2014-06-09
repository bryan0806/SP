/* 此檔案作小寫轉大寫的轉換*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
int main(void){
	int ch; // Because getchar return value is int
	while((ch=getchar())!=EOF){ 	
		putchar(toupper(ch));
	}

	exit(0);
}
