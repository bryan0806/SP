/* Semaphore是當有一段程式（critical code）
 * 只希望一個process來處理時 不希望同時間有兩個一起處理時：
 * 如資料庫若有兩個process 同時進入可能造成當機
 * 使用指令 第一次打./sem1 1 & 背景執行 第二次打./sem1 
 * 當有參數時（第一次） 會列印十次的XX
 * 沒有參數時 (第二次)會列印十次的OO
 * 利用semaphore 就可讓這兩個process 交叉使用critical section*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>
#include "semun.h" // 此檔案包含union semun 結構

static int set_semvalue(void);
static void del_semvalue(void);
static int semaphore_p(void);
static int semaphore_v(void);

static int sem_id;

int main(int argc,char *argv[]){
	int i;
	int pause_time;
	char op_char='O';

	srand((unsigned int)getpid());

	sem_id = semget((key_t)1234,1,0666|IPC_CREAT);// 產生一個新號誌 或者根據key 取得一個已存在的號誌 666為設定權限
	if(argc >1){ // 假設第一次執行時 使用參數
		if(!set_semvalue()){  // setctl回傳-1時（發生錯誤）
			fprintf(stderr,"Failed to initialize semaphore\n");	
			exit(EXIT_FAILURE);
		}
		op_char='X';
		sleep(2);
	}

	/* 然後進入迴圈 進出入 "critical section" 十次
 *  在那裡 首先先呼叫semaphore_p 讓即將進入critical section 的semaphore等待*/ 	
	for(i=0;i<10;i++){
		if(!semaphore_p()) exit(EXIT_FAILURE);
		printf("%c",op_char);fflush(stdout);
		pause_time=rand()%3;
		sleep(pause_time);
		printf("%c",op_char);fflush(stdout);
/* 在critical section 之後 呼叫semaphore_v
 * 再進去for loop 之前 等待一段亂數時間 然後del sem 結束*/
		if(!semaphore_v()) exit(EXIT_FAILURE);
		
		pause_time=rand()%2;
		sleep(pause_time);	
		}
		
		printf("\n%d - finished\n",getpid());

		if(argc>1){
			sleep(10);
			del_semvalue();
		}
		exit(EXIT_SUCCESS);
}

/* set_semvalue 初始化semaphore 使用SETVAL 
 * 在呼叫semctl時 必須呼叫此函數在使用semephore之前*/

static int set_semvalue(void){
	union semun sem_union;

	sem_union.val = 1;
	if(semctl(sem_id,0,SETVAL,sem_union) == -1) return (0);
	return (1);
}

/* del_sevalue 和set_semvalue幾乎有一樣的型態只是他用IPC_RMID來結束semaphore*/

static void del_semvalue(void){
	union semun sem_union;

	if(semctl(sem_id,0,IPC_RMID,sem_union) == -1)
		fprintf(stderr,"Failed to delete semaphore\n");
}

// semaphore_p 減少semaphore -1 讓程序進入 waiting
//

static int semaphore_p(void){
	struct sembuf sem_b;

	sem_b.sem_num = 0;
	sem_b.sem_op = -1; /* p() */
	sem_b.sem_flg = SEM_UNDO;

	if(semop(sem_id,&sem_b,1)==-1){
		fprintf(stderr,"semaphore_p failed\n");
		return (0);
	}
	return (1);
}

// semaphore_v 跟前面幾乎一樣 只是這次sem_op =1
static int semaphore_v(void){
	struct sembuf sem_b;

	sem_b.sem_num = 0;
	sem_b.sem_op = 1; /* v() */
	sem_b.sem_flg = SEM_UNDO;

	if(semop(sem_id,&sem_b,1)==-1){
		fprintf(stderr,"semaphore_p failed\n");
		return (0);
	}
	return (1);
}
