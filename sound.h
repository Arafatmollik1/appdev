//Constants Definition
#define DEBUG
#define RATE 16000 //samples per second
#define CMD "arecord -r16000 -c1 -f s16_LE -d1 -q test.wav"
#define PI 3.1415926
//data structures

struct WAVHDR
{
	char ChunkID[4];	//it has to be "RIFF"
	int ChunkSize;		//4-byte Number
	char Format[4];		//it has to be WAVE

	char SubChunk1ID[4];	// "fmt"
	int SubChunk1Size;	//PCM =16
	short AudioFormat;	//should be 1
	short NumChannels;	//should be 1 for mono
	int SampleRate;		//1600
	int ByteRate;		//1600 "NumChannels*BitsPerSample/8 "
	short BlockAlign;	//NumChannels*BitsPerSample/8
	short BitsPerSample;	//in our app, 16 (-f S16_LE)

	char SubChunk2ID[4];	//"data"
	int SubChunk2Size;
};
// function declarations
void displayWAVHDR(struct WAVHDR h);
void displayWAVDATA(short []);
void testTone(int , int, float);
