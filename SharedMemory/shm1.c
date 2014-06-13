// shm1.c
// 負責接收訊息後印出
#include <stdio.h>
#include "shm_com.h"

int main(void){
	int running = 1;
	void * shared_memory = (void *)0; // 宣告一個空指標 
	struct shared_use_st * shared_stuff;
	int shmid;
	srand((unsigned int)getpid());
	shmid=shmget((key_t)1234,sizeof(struct shared_use_st),0666|IPC_CREAT); // 產生一個共享記憶體 初始化
	if(shmid==-1){ // 產生過程有錯誤
		fprintf(stderr,"shmget failed\n");
		exit(EXIT_FAILURE);
	}
	
	shared_memory = shmat(shmid,(void *)0,0); // 連結共享記憶體 第二參數0 代表給系統決定
	if(shared_memory==(void *)-1){ // error happened
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Memory attached at %X\n",(int)shared_memory);
	
	shared_stuff=(struct shared_use_st *)shared_memory; //指標指向共用區
	shared_stuff -> written_by_you =0;
	while(running){
		if(shared_stuff -> written_by_you){ // 1 才可以進來
			printf("You wrote: %s ", shared_stuff->some_text);
			sleep(rand()%4);
      		shared_stuff->written_by_you=0; // 改成0之後 部會再進if
			if(strncmp(shared_stuff->some_text,"end",3)==0){
				running=0; // 跳出while 不再接收信號
			}
		}	
	}

	if(shmdt(shared_memory)==-1){
		fprintf(stderr,"shmdt failed\n");
		exit(EXIT_FAILURE);
	}

	if(shmct1(shmid,IPC_RMID,0)==-1){
		fprintf(stderr,"shmctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
