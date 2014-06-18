/* msg2.c 丟資料
* msg1.c 收msg 
 * */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/msg.h>

struct my_msg_st{
	long int my_msg_type;
	char some_text[BUFSIZ];
};

int main(){

	int running = 1;
	int msgid;
	struct my_msg_st some_data;
	char buffer[BUFSIZ];

	// 開始設定 message queue
	msgid = msgget((key_t)1234,0666|IPC_CREAT);

	if(msgid == -1){ // error happen
		fprintf(stderr,"msgget failed with error: %d\n",errno);
		exit(EXIT_FAILURE);
	} 
	
	// 從queue 取得message 直到收到end 然後 delete queue
	while(running){
		printf("Enter some text: ");
		fgets(buffer,BUFSIZ,stdin);
		some_data.my_msg_type=1;
		strcpy(some_data.some_text,buffer);
		
		if(msgsnd(msgid,(void *)&some_data,BUFSIZ,0)==-1){
			fprintf(stderr,"msgsnd failed with error : %d\n",errno);
			exit(EXIT_FAILURE);
		}
		//printf("You wrote: %s", some_data.some_text);
		if(strncmp(buffer,"end",3) == 0){
			running = 0;
		}
	}
		
	/*if(msgctl(msgid,IPC_RMID,0) == -1){
		fprintf(stderr,"msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}*/	
    exit(EXIT_SUCCESS);
}
