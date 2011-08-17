#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

#include "linux_simuaudio.h"
#include "linux_simunet.h"
#include "log.h"
#include "linux_simumotor.h"

// Ncurses des MOTORs
WINDOW * window_MOTOR;

// Ncurses Motor Position
int moteur[2][2];

// Moteurs
int motorwheel[256];
int motorval[NBMOTOR];
int motorcount[NBMOTOR];
int motordir[NBMOTOR];


void simuMotor(void) {
	int i,last;
	for(i=0;i<NBMOTOR;i++)
	{
		last=motorwheel[motorval[i]];
		motorval[i]+=motordir[i];
		if (motorval[i]<0)
			motorval[i]=MAXMOTORVAL;
		if (motorval[i]>=MAXMOTORVAL)
			motorval[i]=0;
		if (last<motorwheel[motorval[i]]) motorcount[i]++;
	}
	return;
}

void WMOTOR_Display(void) {
	mvwprintw(window_MOTOR,moteur[0][1],moteur[0][0],"sens : %d, val : %d",motordir[0],motorval[0]);
	mvwprintw(window_MOTOR,moteur[1][1],moteur[1][0],"sens : %d, val : %d",motordir[1],motorval[1]);
	wrefresh(window_MOTOR);
	return;
}

void WMOTOR_Base(int y, int x) {
	mvwprintw(window_MOTOR,y+-2,x+14,"MOTORs");
	mvwprintw(window_MOTOR,y+0,x,"Moteur gauche :");
	mvwprintw(window_MOTOR,y+1,x,"Moteur droit  :");
	moteur[0][0] = x+16;
	moteur[1][0] = x+16;
	moteur[0][1] = y;
	moteur[1][1] = y+1;
	return;
}

int WMOTOR_Init(void) {
    window_MOTOR = newwin(7, 40, 26, 2);
//    wattron(window_MOTOR,A_BOLD);
    refresh();
    box(window_MOTOR,0,0);
    WMOTOR_Base(3,40/2 - 34/2);
    return 0;
}

int simuMotorInit(void) {
	int i;
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
	return 0;
}


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
