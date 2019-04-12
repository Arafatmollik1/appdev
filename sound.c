#include<stdio.h>
#include "sound.h"
#include<math.h>
#include "screen.h"
// this function gets in an array of decibel values and finds out the number of peaks in this array
int findPeaks(int d[])
{
	int i, c=0;
	for(i=1;i<80;i++)
	{
		if(d[i]>=75 && d[i-1]<75) c++;
	}
	if(d[0]>=75) c++;
	return c;
}

/* this function takes 1 second of samples which is 16000
and calculate 80 pieces of RMS value and the turn these values into decibles and display them as a
barchart
*/

void displayWAVDATA(short s[])
{
	double rms[80];/* because we have 16000 samples sp 16000/80  makes 200*/
	int db[80];	// therefore every 2000 samples makes 1 RMS
	int i,j;	// nested loop coundters
	short *ptr = s;// for decibel values
	for(i=0; i<80; i++)			// outer loop repeats 80 times
	{
		double sum=0;			// initialize the sum
		for(j=0; j<200; j++)
		{
			sum += (*ptr)*(*ptr);	// accumulate the sum
			ptr++;
		}
		rms[i]= sqrt(sum/200);
		db[i] = 20*log10(rms[i]);	// decibel value
#ifdef DEBUG
		printf("RMS[%d] = %f\n", i, rms[i]);
#endif
	}
#ifndef DEBUG
	barChart(db);		// get the number of peak
	int peaks=findPeaks(db);// set the colors
	setColors(WHITE,bg(BLACK));// go to row 1, col 41
	printf("\033[1;41H");
	printf("Peaks: %d \n", peaks);
#endif
}

void showID(char *name, char *value)
{
	printf("%s: " , name);
	for(int i=0; i<4 ; i++)
		printf("%c" , value[i]);
	puts("");
}
// function definition
void displayWAVHDR(struct WAVHDR h)
{
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
	printf("Duration=%.2f    \n", (float)h.SubChunk2Size/h.ByteRate);
#endif
	// to be continued for the other flds
}
void fillID (char *dst, const char *m)
{
	for (int i=0; i<4; i++)
	{
		*dst++ = *m++;
	}
}
void testTone(int c, int f, float d)
{
	if(f<30 || f>16000)
	{
		printf("frequency is out of range, \n");
		return;
	}
	if(c<1 || c>2)
	{
		printf("number of channel is not okay \n");
		return;
	}
	if(d<1 || d>10)
	{
		printf("duration is not okay. \n");
		return;
	}
	struct WAVHDR h;	//we need to prepare fro WAV header
	fillID(h.ChunkID, "RIFF");
	fillID(h.Format, "WAVE");
	fillID(h. SubChunk1ID, "fmt ");
	fillID(h.SubChunk2ID, "data");
	h.SubChunk1Size= 16;
	h.AudioFormat=1;
	h.NumChannels=c;
	h.SampleRate=44100;
	h.BitsPerSample=16;
	if(c==1)
	{
		h.ByteRate = h.SampleRate * c * h.BitsPerSample;
		h.BlockAlign= c* h.BitsPerSample/16;
		h.SubChunk2Size= d * h.SampleRate * h.BlockAlign;
		h.ChunkSize= h.SubChunk2Size + 36;
	}
	short data [441000]; //(d * h.SampleRate)
	for(int i=0; i<d*h.SampleRate; i++)
	{
		data[i]= 32768*sin(2*PI*i/44100);
	}
	FILE *fp =fopen("testTone.wav" , "w");
	if(fp==NULL)
	{
		printf("we cannot open file");
	return;
	}
	fwrite(&h, sizeof(h), 1, fp);
	fwrite(data, d*h.SampleRate*sizeof(short), 1, fp);
	fclose(fp);
	printf("test tone is generated!\n");
}
