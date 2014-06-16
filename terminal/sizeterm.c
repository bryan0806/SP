//抓取 終端機行數列數的範例
// compile時要以： "gcc sizeterm.c -lncurses -o termsize"來作
#include <stdio.h>
#include <term.h>
#include <curses.h>
#include <stdlib.h>

int main(void){
	int nrows,ncolumns;
	setupterm(NULL,fileno(stdout),(int *)0);
	nrows=tigetnum("lines");
	ncolumns = tigetnum("cols");
	printf("This terminal has %d columns and %d rows\n",ncolumns,nrows);
	exit(0);
}
