/*main.c*/
// 這是第一個範例 來說明使用 makefile 讓指令make 了解如何編譯
#include <stdlib.h>
#include "a.h"

extern void function_two();
extern void function_three();
int main(){
	function_two();
	function_three();
	exit(EXIT_SUCCESS);

}
