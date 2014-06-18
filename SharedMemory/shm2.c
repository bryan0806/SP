/* shm2.c 可讓user 輸入資料 */

#include "shm_com.h"

int main(){
	int running = 1;
	void *shared_memory = (void *)0;
	struct shared_use_st * shared_stuff;
	char buffer[BUFSIZ];
	int shmid;

	shmid=shmget((key_t)1234,sizeof(struct shared_use_st),0666|IPC_CREAT);

	if(shmid==-1){ // 產生過程有錯誤的話
        fprintf(stderr,"shmget failed\n");
        exit(EXIT_FAILURE);
     }

    shared_memory = shmat(shmid,(void *)0,0); // 連結共享記憶體 第二參數0 代
                                                // 表給系統決定
     if(shared_memory==(void *)-1){ // error happened
         fprintf(stderr,"shmat failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Memory attached at %X\n",(int)shared_memory);

	shared_stuff=(struct shared_use_st *)shared_memory; //指標指向共用區
	while(running){
		while(shared_stuff -> written_by_you == 1){
			sleep(1);
			printf("waiting for client...\n");
		}
		printf("Enter some text: ");
		fgets(buffer,BUFSIZ,stdin);

		strncpy(shared_stuff -> some_text,buffer,TEXT_SZ);
		shared_stuff -> written_by_you = 1;

		if(strncmp(buffer,"end",3)==0){
			running =0;
		}
	}
	
	if(shmdt(shared_memory) == -1){
		fprintf(stderr,"shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
