#include <stdio.h>
#include <stdlib.h> // for exit()

int main(int argc,char * argv[]){
	int ch; // here store ascii code can search man putc for reference
	FILE *fp; 
	long count=0;
	if(argc != 2){
	printf("Usage: %s filename\n",argv[0]);
	exit(1);
	}
	
	if((fp=fopen(argv[1],"r"))==NULL){
		printf("Can't open %s\n",argv[1]);
		exit(1);
	}
	
	while((ch=getc(fp))!=EOF){
	putc(ch,stdout);
	count++;

	}
	fclose(fp);
	printf("File %s has %ld characters\n",argv[1],count);

}
