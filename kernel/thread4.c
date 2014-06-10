/* 使用 mutex 處理同步 */
// 使用 "cc thread4.c -o thread4 -lpthread" 去compile
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

void *thread_function(void *arg);
pthread_mutex_t work_mutex; /* protects both work_area and time_to_exit 這個是mutex 使用的參數*/
#define WORK_SIZE 1024
char work_area[WORK_SIZE];
int time_to_exit=0;

int main(){
	int res;
	pthread_t a_thread;
	void *thread_result;
	res=pthread_mutex_init(&work_mutex,NULL); // 開始mutex
	if(res!=0){
		perror("Mutex initialization failed");
		exit(EXIT_FAILURE);
	}
	
	res=pthread_create(&a_thread,NULL,thread_function,NULL); // 創造一個thread
	if(res!=0){
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
	printf("work_mutex before lock : %d",work_mutex);
	pthread_mutex_lock(&work_mutex); // lock mutex
	printf("work_mutex after lock : %d",work_mutex);
	printf("Input some text. Enter 'end' to finish\n");
	while(!time_to_exit){ // 除非time_to_exit =1 才會跳出此迴圈
		fgets(work_area,WORK_SIZE,stdin);
		pthread_mutex_unlock(&work_mutex);
		while(1){
			pthread_mutex_lock(&work_mutex);
			if(work_area[0] != '\0'){  // if 資料尚未被讀完
				pthread_mutex_unlock(&work_mutex);
				sleep(1);
			}else{ // 如果資料被讀完
				break;

			}
		}
	}
	
	pthread_mutex_unlock(&work_mutex);
	printf("\nWaiting for thread to finish...\n");
	res=pthread_join(a_thread,&thread_result);
	if(res!=0){
		perror("Thread join error");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined\n");
	pthread_mutex_destroy(&work_mutex);
	exit(EXIT_SUCCESS);
}

void *thread_function(void *arg){
	sleep(1);// 因為有這一行 可以確定 main 的第一個lock 先生效
	pthread_mutex_lock(&work_mutex);
	while(strncmp("end",work_area,3)!=0){
		printf("You input %d charatcters\n",strlen(work_area)-1);
		work_area[0]='\0';
		pthread_mutex_unlock(&work_mutex);
		sleep(1);
		while(work_area[0]=='\0'){
		pthread_mutex_unlock(&work_mutex);
		sleep(1);
		pthread_mutex_lock(&work_mutex);
		}
	}
	time_to_exit=1;
	work_area[0]='\0';// 讓main 先跳出while(1) 迴圈
	pthread_mutex_unlock(&work_mutex);
	pthread_exit(0);
}

