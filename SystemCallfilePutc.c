#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h> // for exit()

int main(void){
	char ch; // here store ascii code can search man putc for reference
	
     int in,out;
 	 int count=0;
     in = open("file2.in",O_RDONLY);
 
     out = open("fileoutput.out",O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
 
     while(read(in,&ch,1)==1){
         write(out,&ch,1);
 		count++;
     }
 
     close(in);
     close(out);
	printf("there are %d words in the file.\n",count);

     return 0;
	


}
