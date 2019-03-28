// this program will excute first
#include<stdio.h>
#include<stdlib.h>
#include "screen.h" //for user-defined header always use " "
int main(){
	int arr[80];
	for(int i=0; i<80;i++)
		arr[i]= rand()%70 + 30;

	clearScreen();
	setColors(RED, bg(MAGENTA));
	barChart(arr);
	resetColors();
	getchar();
}
