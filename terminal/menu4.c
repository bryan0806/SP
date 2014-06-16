// menu4.c 解決menu3 enter 輸入多餘問題
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

char *menu[] = {
    "a - add new record",
    "d - delete record",
    "q - quit",
    NULL,
};

int getchoice(char *greet, char *choices[],FILE *in,FILE *out); // 這邊多兩個變數 為檔案指標

int main()
{
    int choice = 0;
	FILE *input;
	FILE *output;
	struct termios initial_settings,new_settings; // 後面變更設定使用
	if(!isatty(fileno(stdout))){
         fprintf(stderr,"You are not a terminal!\n");
         exit(1);
      }
	
	input=fopen("/dev/tty","r"); // 表示input 指向鍵盤
	output=fopen("/dev/tty","w"); // 表示output 指向鍵盤
	if(!input || !output){
		fprintf(stderr,"Unable to open /dev/tty\n");
		exit(1);
	}
	// 這邊開始使用變更終端機設定來解決此問題
	tcgetattr(fileno(input),&initial_settings);
	new_settings=initial_settings;
	new_settings.c_lflag &= ~ICANON; // 關閉標準輸入功能
	new_settings.c_cc[VMIN]=1; // 至少一個字元
	new_settings.c_cc[VTIME]=0; //等待時間0秒
	new_settings.c_lflag &= ~ISIG; // 關閉訊號功能
	if(tcsetattr(fileno(input),TCSANOW,&new_settings)!=0){
		fprintf(stderr,"Could not set attributes\n");
	}

    do
    {
        choice = getchoice("Please select an action", menu,input,output);
        printf("You have chosen: %c\n", choice);
    } while (choice != 'q');
    exit(0);
}

int getchoice(char *greet, char *choices[],FILE *in,FILE *out)
{
    int chosen = 0;
    int selected;
    char **option;

    do {
        fprintf(out,"Choice: %s\n",greet);
        option = choices;
        while(*option) {
            fprintf(out,"%s\n",*option);
            option++;
        }


        selected = getchar();
        option = choices;
        while(*option) {
            if(selected == *option[0]) {
                chosen = 1;
                break;
            }
            option++;
        }
        if(!chosen) {
            printf("Incorrect choice, select again\n");
        }
    } while(!chosen);
    return selected;
}
