//之前有取消註冊 所以程式只被呼叫一次
//這次 也利用struct sigaction來作註冊
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig){
	printf("OUCH! - I got signal %d\n",sig);
}

int main(){
	// register start here
	struct sigaction act;
	act.sa_handler = ouch;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	sigaction(SIGINT,&act,0);
	// register end here
	while(1){
		printf("Hello World!\n");
		sleep(1);
	}
}

