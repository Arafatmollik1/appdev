#include<stdio.h>

void barChart(int a[]){
	int i,j;
	for(i=0;i<80;i++){
		for(j=0;j<a[i]/3;j++){
			printf("\033[%d;%dH", 35-j,i+1);
#ifdef UNICODE
		printf("%s", "\u2590");
#else
		printf("%c" , ' ');
#endif
		}
	}
}
void clearScreen(void){
	printf("\033[2J");	//clears the screen
	fflush(stdout);		//output the escape sequence immediately

}

void setColors(short fg, short bg){
	printf("\033[%d;%d;1m", fg, bg);	//takes background and foreground color and gives it bright color
	fflush(stdout);		//priints immediately
}

void resetColors(void){
	printf("\033[0m");
	fflush(stdout);
}
