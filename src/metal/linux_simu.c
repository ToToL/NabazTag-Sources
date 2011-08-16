#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include  <ncurses.h>

#include "linux_simuaudio.h"
#include "linux_simunet.h"
#include "log.h"
#include "linux_simu.h"
#include "linux_simuled.h"

// Moteurs
#ifdef VL_MOTORS
int motorwheel[256];
int motorval[NBMOTOR];
int motorcount[NBMOTOR];
int motordir[NBMOTOR];
#endif

int getButton() {
	return 0;
}

/***************************
 * La fenetre en general
 ***************************/

int simuDisplayInit(void) {
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_RED);
    init_pair(4, COLOR_BLACK, COLOR_BLUE);
    init_pair(5, COLOR_BLACK, COLOR_GREEN);
    init_pair(6, COLOR_BLACK, COLOR_YELLOW);
    init_pair(7, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(8, COLOR_BLACK, COLOR_CYAN);
    noecho();
    cbreak();
    WLED_Init();
    return 0;
}

int simuDisplay(void){
    WLED_Display();
    return 0;
}

// initialisation du simulateur
long simuInit()
{
	int i;

	srand(clock());
#ifdef VL_MOTORS
	for(i=0;i<NBMOTOR;i++)
	{
		motorval[i]=60;//(rand()&255)*MAXMOTORVAL/256;
		motorcount[i]=motordir[i]=0; 
	}
	for(i=0;i<256;i++) motorwheel[i]=0;
	for(i=0;i<MAXMOTORVAL;i++)
	{
		if ((i*2*NBHOLES/MAXMOTORVAL)&1) motorwheel[i]=1;
		if (i*NBHOLES/MAXMOTORVAL>=NBHOLES-MASKEDHOLES) motorwheel[i]=1;
	}
#endif
//	setButton(1);
	simuaudioinit();
	simunetinit();
	simuDisplayInit();
	return 0;
}



/**
	 Vérifie tous les évènements et fait les actions appropriées
 */
void checkAllEvents(void)
{
	checkNetworkEvents();
	 simuFetch();
}

// fonction à appeler régulièrement, pour traiter les messages de la fenêtre du simulateur
long simuDoLoop()
{
#ifdef VL_MOTORS
	int i,last;
#endif

	checkAllEvents();

#ifdef VL_MOTORS
	for(i=0;i<NBMOTOR;i++)
	{
		last=motorwheel[motorval[i]];
		if (1) motorval[i]+=motordir[i];
		if (motorval[i]<0) motorval[i]+=MAXMOTORVAL;
		if (motorval[i]>=MAXMOTORVAL) motorval[i]-=MAXMOTORVAL;
		if (last<motorwheel[motorval[i]]) motorcount[i]++;
	}
#endif
	simuDisplay();
	return 0;
}

#ifdef VL_MOTORS
// réglagle d'un moteur
void set_motor_dir(int num_motor, int sens)
{
	int tmp_num, tmp_sens;
	tmp_num = num_motor?1:0;
	tmp_sens = (sens==0)?0:((sens==1)?1:-1);
	motordir[tmp_num]=tmp_sens;

	my_printf(LOG_SIMUMOTORS, "Setting motor %d, direction %d (pos: %d)\n", tmp_num, tmp_sens);
}

int get_motor_val(int i)
{
	int tmp_num = i?1:0;
	my_printf(LOG_SIMUMOTORS, "Getting value for motor %d: %d\n", tmp_num, motorcount[tmp_num]);
	return motorcount[tmp_num];
}
#else
int get_motor_val(int i)
{
	return 128;
}
#endif

int get_button3()
{
	// TODO
	return 0;
}

char buf_rfid[256];

char* get_rfid()
{
	// TODO
	return NULL;
}
