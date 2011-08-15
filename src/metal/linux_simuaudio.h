#ifndef MY_SIMUAUDIO_H_
#define MY_SIMUAUDIO_H_

#define A() my_printf(LOG_SIMUAUDIO, "[[%s]]\n", __func__);

#define PLAYST_IDLE 0
#define PLAYST_START 1
#define PLAYST_PLAY 2

#define PLAYTYPE_MP3 0
#define PLAYTYPE_WAV 1
#define PLAYTYPE_ADPCM 2

#define BUFMP3IN_LENGTH 65536

int RecStart(int rate,int ChannelSize,int nbBuffers);
int RecStop();

void audioSetVolume(int vol);

int simuaudioinit();

void simuFetchStart();
int simuFetchPlay(void);
int simuFetch(void);

int PlayStart();
int PlayStop();
int PlayEof();

#endif
