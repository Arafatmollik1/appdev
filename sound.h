//Constants Definition
#define RATE 16000
#define CMD "arecord -r16000 -c1 -f s16_LE -d1 -q test.wav"
//data structures

struct WAVHDR{
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

void displayWAVHDR(struct WAVHDR h);
void displayWAVDATA(short []);
