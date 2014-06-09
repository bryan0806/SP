/* 作業：寫一隻程式fork_sum.c 產生子處理執行 1+2...+10之後 
 * 將結果55傳回父處理之後 由父處理列印55*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	pid_t pid;
	printf("fork program starting\n");
	pid=fork();
	int exit_code,result;
	
	switch(pid){
	case -1:
		perror("fork failed");
	case 0:
		//result=system("./sum_for_child"); be careful !!! result is system return value which is not what I think what it is.
		sytem("./sum_for_child");
		result = `$?`;// still can not get result, teacher said must using IPC?
		printf("result is %d\n",result);
		exit_code = result;	
		break;
	}
	
	if(pid!=0){
		int stat_val;
		pid_t child_pid;
		child_pid=wait(&stat_val);
		if(WIFEXITED(stat_val))
			printf("The result is %d\n",WEXITSTATUS(stat_val));
		else
			printf("Child terminated abnormally\n");
	
	}
	exit(exit_code);
}
