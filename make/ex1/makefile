#makefile
#使用接近專案使用格式
all: myapp
#Which compiler
CC = gcc
#Where are include files kept
INCLUDE=.
#Option for development
CFLAGS = -g -Wall -ansi #g:debug資訊 -Wall顯示所有警告訊息 -ansi 標準c
#Options for release
#CFLAGS = -O -Wall -ansi
myapp:main.o 2.o 3.o
	$(CC) -o myapp main.o 2.o 3.o
main.o: main.c a.h
	$(CC) -I$(INCLUDE)$(CFLAGS) -c main.c
2.o: 2.c a.h b.h
    $(CC) -I$(INCLUDE)$(CFLAGS) -c 2.c
3.o: 3.c b.h c.h
    $(CC) -I$(INCLUDE)$(CFLAGS) -c 3.c

