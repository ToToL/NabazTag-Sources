#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

#include "linux_simuaudio.h"
#include "linux_simunet.h"
#include "log.h"
#include "linux_simuled.h"

// LEDs
int diodeval[NBLED];
int diodepos[NBLED/3][2];
int detaildiodepos[2];

// Ncurses des LEDs
WINDOW * window_LED;

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

// Colorer une LED
void simuSetLed(int i,int val) {
	i*=3;
	if ((i<0)||(i>=NBLED)) return;
	diodeval[i]=(val>>16)&255;
	diodeval[i+1]=(val>>8)&255;
	diodeval[i+2]=(val)&255;

	my_printf(LOG_SIMULEDS, "Setting led %d: [%d %d %d]\n", i/3, diodeval[i], diodeval[i+1], diodeval[i+2]);
	my_printf(LOG_SIMULEDS, "All leds state:", i/3, diodeval[i], diodeval[i+1], diodeval[i+2]);
	for (i=0; i<NBLED/3; ++i)
		my_printf(LOG_SIMULEDS, " [%3d %3d %3d]", diodeval[3*i], diodeval[3*i+1], diodeval[3*i+2]);
	my_printf(LOG_SIMULEDS, "\n");
}

/******************************
 * Fenetre des LEDs du NabazTag
 ******************************/

int round_256(int val) {
	if ( val - 128 > 64 )
		val = 255;
	else if ( val - 128 > 0 || val - 192 > -64 )
		val = 128;
	else
		val = 0;
	return val;
}

int WLED_SelectColor(int a,int b,int c) {
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

void WLED_Display(void) {
	int i;
	for (i = 0;i < NBLED/3;i++ ){
		wattron(window_LED,COLOR_PAIR(WLED_SelectColor(diodeval[3*i],diodeval[3*i+1],diodeval[3*i+2])));
		mvwprintw(window_LED,diodepos[i][1],diodepos[i][0],"   ");
		wattroff(window_LED,COLOR_PAIR(WLED_SelectColor(diodeval[3*i],diodeval[3*i+1],diodeval[3*i+2])));
		mvwprintw(window_LED,detaildiodepos[1]+i,detaildiodepos[0],"%03d, %03d, %03d",diodeval[3*i],diodeval[3*i+1],diodeval[3*i+2]);
	}
	wrefresh(window_LED);
	return;
}

void WLED_Base(int y, int x) {
	mvwprintw(window_LED,y+-2,x+13,"LEDs");
	mvwprintw(window_LED,y+ 0,x,"    \\\\      ______      //");
	mvwprintw(window_LED,y+ 1,x,"     \\\\    /      \\    //");
	mvwprintw(window_LED,y+ 2,x,"      \\\\  /        \\  //");
	mvwprintw(window_LED,y+ 3,x,"       \\\\/          \\//");
	mvwprintw(window_LED,y+ 4,x,"        /            \\");
	mvwprintw(window_LED,y+ 5,x,"       /              \\");
	mvwprintw(window_LED,y+ 6,x,"      /                \\");
	mvwprintw(window_LED,y+ 7,x,"     /                  \\");
	mvwprintw(window_LED,y+ 8,x,"    /                    \\");
	mvwprintw(window_LED,y+ 9,x,"   /                      \\");
	mvwprintw(window_LED,y+10,x,"  /                        \\");
	mvwprintw(window_LED,y+11,x," /                          \\");
	mvwprintw(window_LED,y+12,x,"------------------------------");
	mvwprintw(window_LED,y+15,x,"couleur nez    :");
	mvwprintw(window_LED,y+16,x,"couleur gauche :");
	mvwprintw(window_LED,y+17,x,"couleur milieu :");
	mvwprintw(window_LED,y+18,x,"couleur droite :");
	mvwprintw(window_LED,y+19,x,"couleur base   :");

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

	detaildiodepos[0] = x + 17;
	detaildiodepos[1] = y + 15;

	return ;
}

int simuLedInit(void) {
    int i;
    
    for( i = 0 ; i < NBLED ; i++ )
        diodeval[i]=255;
 
    return 0;
}

int WLED_Init(void) {

    window_LED = newwin(25, 40, 8, 2);
    wattron(window_LED,A_BOLD);
    refresh();
    box(window_LED,0,0);
    WLED_Base(3,40 / 2 - 30 / 2);
    return 0;
}
