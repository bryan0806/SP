/* 這個範例 示範了使用 Semaphore 作thread 與 主程式間的切換動作*/
// using "cc -D_REENTRANT thread3.c -o thread3 -lthread"來作compile
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

void *thread_function(void *arg); // thread 函數宣告
sem_t bin_sem; // 控制Semaphore 的變數
#define WORK_SIZE 1024
char work_area[WORK_SIZE];

int main(){
	int res;
	pthread_t a_thread; //控制thread 的變數
	void *thread_result; // 給thread 用的回傳值
	
	res=sem_init(&bin_sem,0,0); // 建立Semaphore
	if(res!=0){
		perror("Semaphore initialization failed");
		exit(EXIT_FAILURE);
	}
	
	res=pthread_create(&a_thread,NULL,thread_function,NULL); //建立thread
	if(res!=0){
		perror("Thread creation failed!");
		exit(EXIT_FAILURE);
	}

	printf("Input some text. Enter 'end' to finish\n");
	while(strncmp("end",work_area,3)!=0){
		fgets(work_area,WORK_SIZE,stdin);
		sem_post(&bin_sem); // 此程式會讓 bin_sem +=1

	}
	// only user enter "end" can go here
	printf("\nWaiting for thread to finish...\n");
	res=pthread_join(a_thread,&thread_result);
	if(res!=0){
		perror("THread join failed");
		exit(EXIT_FAILURE);
	}


	printf("Thread joined\n");
	sem_destroy(&bin_sem);
	exit(EXIT_SUCCESS);

}

void *thread_function(void *arg){
	sem_wait(&bin_sem); //第一步：bin_sem先減一,一直到bin_sem變成1之前,不會執行下面的東作 wait for bin_sem to become bigger than 0
	while(strncmp("end",work_area,3)!=0){
		printf("You input %d characters\n",strlen(work_area)-1);
		sem_wait(&bin_sem);//bin_sem -1 and wait for become 1

	}
	pthread_exit(NULL);
}
