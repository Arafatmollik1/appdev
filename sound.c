#include<stdio.h>
#include "sound.h"
#include<math.h>
#include "screen.h"
int findPeaks(int d[]){
	int i, c=0;
	for(i=1;i<80;i++){
		if(d[i]>=75 && d[i-1]<75) c++;
	}
	if(d[0]>=75) c++;
	return c;
}

/* this function takes 1 second of samples which is 16000
and calculate 80 pieces of RMS value and the turn these values into decibles and display them as a
barchart
*/
int pickCount = 0;
void displayWAVDATA(short s[]){
	double rms[80];/* because we have 16000 samples sp 16000/80  makes 200*/
	int db[80];
	int i,j,k=0;
	short *ptr = s;
	for(i=0; i<80; i++){
		double sum=0;
		for(j=0; j<200; j++){
			sum += (*ptr)*(*ptr);
			ptr++;
		}
		rms[i]= sqrt(sum/200);
		db[i] = 20*log10(rms[i]);
		if(db[i] > 75) {
			pickCount += 1;
		}
#ifdef DEBUG
		printf("RMS[%d] = %f\n", i, rms[i]);
#endif
	}
#ifndef DEBUG
	barChart(db);
	int peaks=findPeaks(db);
	setColors(MAGENTA,bg(BLACK));
	printf("\033[1;41H");
	printf("Peaks: %d \n", peaks);
#endif
}

void showID(char *name, char *value){
	printf("%s: " , name);
	for(int i=0; i<4 ; i++)
		printf("%c" , value[i]);
	puts("");
}

void displayWAVHDR(struct WAVHDR h){
#ifdef DEBUG
	showID("Chunk ID" , h.ChunkID);
	printf("Chunk size : %d \n" , h.ChunkSize);
	showID("Format", h.Format);
	showID("Subchunk1 ID" , h.SubChunk1ID);
	printf("Subchunk1 size: %d \n" , h.SubChunk1Size);
	printf("Audio Format : %d\n" , h.AudioFormat);
	printf("Number of Channels: %d\n" , h.NumChannels);
	printf("Sample Rate: %d\n" , h.SampleRate);
	printf("Byte Rate: %d\n" , h.ByteRate);
	printf("Block Align: %d\n" , h.BlockAlign);
	printf("Bits per sample: %d\n" , h.BitsPerSample);
	showID("Subchunk 2 ID: " , h.SubChunk2ID);
	printf("Subchunk 2 size: %d\n" , h.SubChunk2Size);
#else
	setColors(RED, bg(BLUE));
	printf("\033[1;H");
	printf("test.wav            \n");
	setColors(YELLOW, bg(GREEN));
	printf("\033[1;21H");
	printf("Sample rate=%d      \n", h.SampleRate);
	setColors(WHITE, bg(MAGENTA));
	printf("\033[1;61H");
	printf("Duration=%.2f sec   \n", (float)h.SubChunk2Size/h.ByteRate);
#endif
}
