#include <stdio.h>

#include "log.h"

#define A() my_printf(LOG_SIMUAUDIO, "[[%s]]\n", __func__);

int PlayState;
int PlayStateEof;
int PlayType;

#define PLAYST_IDLE 0
#define PLAYST_START 1
#define PLAYST_PLAY 2

#define PLAYTYPE_MP3 0
#define PLAYTYPE_WAV 1
#define PLAYTYPE_ADPCM 2

#define BUFMP3IN_LENGTH 65536

char bufplayin[BUFMP3IN_LENGTH];

FILE * printmp3;

int RecStart(int rate,int ChannelSize,int nbBuffers) { A(); return 0; }
int RecStop() { A(); return 0; }

void audioSetVolume(int vol) { A(); return ; }

int PlayStop()
{
	A();
	PlayState=PLAYST_IDLE;
	return 0;
}

int PlayEof()
{
	A();
	PlayStateEof=1;
	return 0;
}

int simuaudioinit()
{
	PlayState=PLAYST_IDLE;
	PlayStateEof=1;
	return 0;
}


void simuFetchStart()
{
	my_printf(LOG_SIMUAUDIO,"START\n");
	system("rm -f /tmp/toto.mp3");
	printmp3 = fopen("/tmp/toto.mp3","a+");
	PlayType=PLAYTYPE_MP3;
	my_printf(LOG_SIMUAUDIO,"Detect MP3\n");
	PlayState=PLAYST_PLAY;
}

int simuFetchPlay(void)
{
	my_printf(LOG_SIMUAUDIO,"PLAY\n");
	int len=BUFMP3IN_LENGTH;
	if (len) len=audioPlayFetch(bufplayin,len);
	my_printf(LOG_SIMUAUDIO,"simuFetchStart get=%d\n",len);

	if (!len)
	{
		if (PlayStateEof) {PlayState=PLAYST_IDLE;
			fclose(printmp3);}
		return;
	}

	fwrite(bufplayin,sizeof(char),len,printmp3);

	return 0;
}

int simuFetch(void)
{
	if (PlayState==PLAYST_IDLE) return 0;
	if (PlayState==PLAYST_START) simuFetchStart();
	if (PlayState==PLAYST_PLAY) return simuFetchPlay();
	return 0;
}

int PlayStart()
{
	A();
	PlayState=PLAYST_START;
	PlayStateEof=0;
	bufplaystart=0;
	bufplayout_i=0;
}
