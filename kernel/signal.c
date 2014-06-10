// 使用多個 信號 來觸發同一個函數時
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

void SignalHandle(int signal){
	switch(signal){
		case SIGHUP:
			printf("Catch Singal:SIGHUP(%d)\n ",signal);
			break;
		case SIGINT:
			printf("Catch Singal:SIGINT(%d)\n ",signal);
			break;
		case SIGQUIT:
			printf("Catch Singal:SIGQUIT(%d)\n ",signal);
			break;
		case SIGALRM:
			printf("Catch Singal:SIGALRM(%d)\n ",signal);
			break;
		default:
			printf("Unknown Signal:%d",signal);
			break;

	}
}

int main(void){
	int sec_delay=5;
	
	printf("cURRENT Process ID:%d\n",(int)getpid());

	signal(SIGINT,SignalHandle);
	signal(SIGQUIT,SignalHandle);
	signal(SIGALRM,SignalHandle);

	alarm(sec_delay);
	while(1){

		pause();
	}	
	return 0;
}
