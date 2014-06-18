/* talk_client_msg.c 可傳送與接收
 * */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/types.h>

struct my_msg_st{
	long int my_msg_type;
	char some_text[BUFSIZ];
};

int main(){
	pid_t pid;
	int running = 1;
	int msgid,msgid2;
	struct my_msg_st rec_data,snd_data;
	long int msg_to_receive = 0;
	char buffer[BUFSIZ];

	// 開始設定 message queue 這邊設定1234為server 讀取client 的key 
	msgid = msgget((key_t)1234,0666|IPC_CREAT);
	msgid2 = msgget((key_t)5678,0666|IPC_CREAT);

	if((msgid == -1) || (msgid2 == -1)){ // error happen
		fprintf(stderr,"msgget failed with error: %d\n",errno);
		exit(EXIT_FAILURE);
	} 
	
	pid = fork();

	if(pid){
		while(running){


			if(msgrcv(msgid2,(void *)&rec_data,BUFSIZ,msg_to_receive,0)==-1){
				fprintf(stderr,"msgrcv failed with error : %d\n",errno);
				exit(EXIT_FAILURE);
			}
			printf("Server wrote: %s", rec_data.some_text);
			if(strncmp(rec_data.some_text,"end",3) == 0){
				running = 0;
			}
		
		}
	}else{
		while(running){
			printf("Enter some text: ");
        	fgets(buffer,BUFSIZ,stdin);
        	snd_data.my_msg_type=1;
        	strcpy(snd_data.some_text,buffer);

        	if(msgsnd(msgid,(void *)&snd_data,BUFSIZ,0)==-1){
            	fprintf(stderr,"msgsnd failed with error : %d\n",errno);
            	exit(EXIT_FAILURE);
        	}
        	//printf("You wrote: %s", some_data.some_text);
        	if(strncmp(buffer,"end",3) == 0){
            	running = 0;
        	}
		}
	}

		
	if(msgctl(msgid,IPC_RMID,0) == -1){
		fprintf(stderr,"msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	if(msgctl(msgid2,IPC_RMID,0) == -1){
		fprintf(stderr,"msgctl(IPC_RMID msgid2) failed\n");
		exit(EXIT_FAILURE);
	}
		
    exit(EXIT_SUCCESS);
}
