// using thread

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *thread_function(void *arg);
char message[] = "Hello World";

int main(){
	int res;
	pthread_t a_thread;
	void *thread_result; // 因為通常thread_return 都是void 型別
	res=pthread_create(&a_thread,NULL,thread_function,(void *)message);
    if(res !=0){
	perror("Thread creation failed");
	exit(EXIT_FAILURE);
	}
	printf("Waiting for thread to finish...\n");
	res=pthread_join(a_thread,&thread_result);
	if(res!=0){
		perror("Thread join failed");
		exit(EXIT_FAILURE);
		}
	printf("THread joined, it returned %s\n",(char *)thread_result);//因為知道回傳的是string 所以要加強制轉型
	printf("Message is now %s\n",message);
	exit(EXIT_SUCCESS);
	}
	
	void *thread_function(void *arg){
		printf("thread_function is running. Argument was %s\n",(char *)arg);		sleep(3);
		strcpy(message,"Bye!");
		pthread_exit("Thank you for the CUP time");

	}
	
	
	
