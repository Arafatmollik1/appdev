#include<stdio.h>
#include "sound.h"

void showID(char *name, char *value){
	printf("%s: " , name);
	for(int i=0; i<4 ; i++)
		printf("%c" , value[i]);
	puts("");
}
void displayWAVHDR(struct WAVHDR h){
	showID("Chunk ID" , h.ChunkID);
	printf("Chunk size : %d \n" , h.ChunkSize);
	showID("Format", h.Format);
	showID("Subchunk1 ID" , h.SubChunk1ID);
	printf("Subchunk1 size: %d \n" , h.SubChunk1Size);
	
}
