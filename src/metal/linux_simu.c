#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include  <ncurses.h>

#include "linux_simuaudio.h"
#include "linux_simunet.h"
#include "log.h"
#include "linux_simu.h"

// LEDs
int diodeval[NBLED];
int diodepos[NBLED/3][2];
int detaildiodepos[2];

// Ncurses des LEDs
WINDOW * window_local;

// Ncurses couleurs
int ncurses_color[7][3]= {
	{255,255,255}, // Blanc
	{0,0,0}, // Noir
	{255,0,0}, // Rouge
	{0,0,255}, // Bleu
	{0,255,0}, // Vert
	{255,128,0}, // Violet
	{255,0,255} // Cyan
};

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

int round_256(int val) {
	if ( val - 128 > 64 )
		val = 255;
	else if ( val - 128 > 0 || val - 192 > -64 )
		val = 128;
	else
		val = 0;
	return val;
}

int select_color(int a,int b,int c){
	int i;
	a = round_256(a);
	b = round_256(b);
	c = round_256(c);
	for ( i = 0; i < 7; i++ ) {
		if ( a == ncurses_color[i][0] && \
                     b == ncurses_color[i][1] && \
                     c == ncurses_color[i][2] ) {
			return i+1;
		}
	}
	return 8;
}

// fonction d'affichage des diodes
int simuDisplay(int* intensity)
{
	int i;
	for (i = 0;i < NBLED/3;i++ ){
		wattron(window_local,COLOR_PAIR(select_color(diodeval[3*i],diodeval[3*i+1],diodeval[3*i+2])));
		mvwprintw(window_local,diodepos[i][1],diodepos[i][0],"   ");
		wattroff(window_local,COLOR_PAIR(select_color(diodeval[3*i],diodeval[3*i+1],diodeval[3*i+2])));
		mvwprintw(window_local,detaildiodepos[1]+i,detaildiodepos[0],"%03d, %03d, %03d",diodeval[3*i],diodeval[3*i+1],diodeval[3*i+2]);
	}
	wrefresh(window_local);
	return 0;
}

void print_dessin(int x, int y) {
	mvwprintw(window_local,y+ 0,x,"     \\\\     ______    //");
	mvwprintw(window_local,y+ 1,x,"      \\\\   /      \\  //");
	mvwprintw(window_local,y+ 2,x,"       \\\\ /        \\//");
	mvwprintw(window_local,y+ 3,x,"         /          \\");
	mvwprintw(window_local,y+ 4,x,"        /            \\");
	mvwprintw(window_local,y+ 5,x,"       /              \\");
	mvwprintw(window_local,y+ 6,x,"      /                \\");
	mvwprintw(window_local,y+ 7,x,"     /                  \\");
	mvwprintw(window_local,y+ 8,x,"    /                    \\");
	mvwprintw(window_local,y+ 9,x,"   /                      \\");
	mvwprintw(window_local,y+10,x,"  /                        \\");
	mvwprintw(window_local,y+11,x," /                          \\");
	mvwprintw(window_local,y+12,x,"------------------------------");
	mvwprintw(window_local,y+16,x," couleur nez    :");
	mvwprintw(window_local,y+17,x," couleur gauche :");
	mvwprintw(window_local,y+18,x," couleur milieu :");
	mvwprintw(window_local,y+19,x," couleur droite :");
	mvwprintw(window_local,y+20,x," couleur base   :");

	diodepos[0][0] = x + 13;
	diodepos[0][1] = y + 4;
	diodepos[1][0] = x + 7;
	diodepos[1][1] = y + 9;
	diodepos[2][0] = x + 13;
	diodepos[2][1] = y + 9;
	diodepos[3][0] = x + 19;
	diodepos[3][1] = y + 9;
	diodepos[4][0] = x + 13;
	diodepos[4][1] = y + 13;

	detaildiodepos[0] = x + 16;
	detaildiodepos[1] = y + 16;

	return ;
}

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
    window_local = newwin(30, 50, 0, 0);
    refresh();
    box(window_local,0,0);
    print_dessin(50 / 2 - 30 / 2,2);
    return 0;
}

// initialisation du simulateur
long simuInit()
{
	int i;

	for(i=0;i<NBLED;i++) diodeval[i]=255;
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
	simuDisplay(diodeval);
	return 0;
}



// réglagle d'une led
void simuSetLed(int i,int val)
{
	i*=3;
	if ((i<0)||(i>=NBLED)) return;
	diodeval[i]=(val>>16)&255;
	diodeval[i+1]=(val>>8)&255;
	diodeval[i+2]=(val)&255;

	my_printf(LOG_SIMULEDS, "Setting led %d: [%d %d %d]\n", i/3, diodeval[i], diodeval[i+1], diodeval[i+2]);
	my_printf(LOG_SIMULEDS, "All leds state:", i/3, diodeval[i], diodeval[i+1], diodeval[i+2]);
	for (i=0; i<NBLED/3; ++i)
		{
			my_printf(LOG_SIMULEDS, " [%3d %3d %3d]", diodeval[3*i], diodeval[3*i+1], diodeval[3*i+2]);
		}
	my_printf(LOG_SIMULEDS, "\n");
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
