// this program will excute first
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "screen.h" //for user-defined header always use " "
#include "sound.h"
int main(){
	FILE *f;
	f= fopen("test.wav" , "r");
	//int arr[80];
	//for(int i=0; i<80;i++)
		//arr[i]= rand()%70 + 30;

	clearScreen();
	setColors(RED, bg(MAGENTA));
	if(f == NULL){
	printf("Cannot open the wav file\n");
	return 1;
	}
	struct WAVHDR h;
	fread(&h, sizeof(h), 1, f);
	displayWAVHDR(h);
	resetColors();
	printf("Another message\n");
	getchar();
}
