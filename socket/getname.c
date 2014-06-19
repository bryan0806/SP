/* 此程式取得主機資訊 利用gethostname gethostbyname */

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char * argv[]){
	char *host, **names, **addrs;
	struct hostent *hostinfo;

	// 利用gethostname() 取得host 名稱 或是直接根據使用者傳入的參數
	if(argc ==1){
		char myname[256];
		gethostname(myname,255);
		host = myname;
	}else
		host = argv[1];
	// 呼叫gethostbyname() 如果沒有看到資訊就會回報錯誤
	hostinfo = gethostbyname(host);
	if(!hostinfo){
		fprintf(stderr,"cannot get info for host: %s \n",host);
		exit(1);
	}

	// 顯示主機名稱 還有他可能的別名
	printf("results for host %s:\n",host);
	printf("Name: %s\n",hostinfo -> h_name);
	printf("Aliases:");
	names = hostinfo -> h_aliases;
	while(*names){
		printf(" %s",names);
		names++;
	}
	printf("\n");

	//如果主機不是一個ip主機 就會警示且離開
	if(hostinfo -> h_addrtype != AF_INET){
		fprintf(stderr,"not an IP host!\n");
		exit(1);
	}
	// 否則會顯示ip 位址
	addrs=hostinfo -> h_addr_list;
	while(*addrs){
		printf(" %s",inet_ntoa(*(struct in_addr *)*addrs));
		addrs++;
	}
	printf("\n");
	exit(0);
}
	
