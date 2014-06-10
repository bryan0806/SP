/* using kill(pid_t pid,int sig) */
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int alarm_fired=0;
void ding(int sig){
	alarm_fired=1;
}

int main(){
	pid_t pid;
	printf("alarm application starting\n");
	pid=fork();
	
	switch(pid){
		case -1:/*failed*/
			perror("fork falied");
			exit(1);
		case 0:/*child*/
			sleep(5);
			kill(getppid(),SIGALRM); // send to father alarm signal
			exit(0);
		}
	
	/* from here is parent process */
	printf("waiting for alarm to go off\n");
	(void)signal(SIGALRM,ding); // if received the SIGALRM then trigger ding
	pause();// wait for signal
	if(alarm_fired)
		printf("DIng!\n");
	printf("done\n");
	exit(0);	

	}
