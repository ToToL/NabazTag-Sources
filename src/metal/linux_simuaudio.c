#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

#include "log.h"
#include "linux_simuaudio.h"

int PlayState;
int PlayStateEof;
int PlayType;

char bufplayin[BUFMP3IN_LENGTH];

FILE * printmp3;

int RecStart(int rate,int ChannelSize,int nbBuffers) {
	A();
	return 0;
}

int RecStop() {
	A();
	return 0;
}

void audioSetVolume(int vol) {
	A();
	return ;
}

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
	time_t tii;
	struct tm * ti;
	char buff[512];

	my_printf(LOG_SIMUAUDIO,"START\n");

	if ( access ( "Simu_Work/mp3" , F_OK ) != -1 )
		system("rm -rf Simu_Work/mp3");
	mkdir("Simu_Work/mp3", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
       	tii = time(NULL);
       	ti = localtime(&tii);
       	sprintf(buff,"Simu_Work/mp3/%d%d%d%d%d%d.mp3",ti->tm_year,
                                                 ti->tm_mon,
                                                 ti->tm_mday,
                                                 ti->tm_hour,
                                                 ti->tm_min,
                                                 ti->tm_sec);
       	printmp3 = fopen(buff,"a+");
	PlayType=PLAYTYPE_MP3;
	my_printf(LOG_SIMUAUDIO,"Detect MP3\n");
	PlayState=PLAYST_PLAY;

	return ;
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
	return 0;
}
