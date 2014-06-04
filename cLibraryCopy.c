#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc,char * argv[]){
	int ch; // buffer
	FILE * fp;
	FILE * fp2;
	int count=0;
	
	if(argc != 3){
     printf("Usage: %s filename filename(out)\n",argv[0]);
     exit(1);
     }
	
    if((fp=fopen(argv[1],"r"))==NULL){
         printf("Can't open %s\n",argv[1]);
         exit(1);
     }
 	
	 fp2=fopen(argv[2],"w");	

     while((ch=getc(fp))!=EOF){
     putc(ch,fp2);
     count++;
      }
	fclose(fp);
	fclose(fp2);

	return 0;


}

