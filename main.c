// this program will excute first
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<time.h>
#include "screen.h" //for user-defined header always use " "
#include "sound.h"
int main(){
	FILE *f;
	short sd[RATE];
	while(1){
		int ret= system(CMD);
		if(ret== SIGINT) break;
		f = fopen("test.wav" , "r");

		clearScreen();
		setColors(RED, bg(MAGENTA));
		if(f == NULL){
			printf("Cannot open the wav file\n");
			return 1;
		}
		struct WAVHDR h;
		fread(&h, sizeof(h), 1, f);
		displayWAVHDR(h);
		fread(&sd, sizeof(sd) , 1, f);
		displayWAVDATA(sd);
		fclose(f);
	}
}
