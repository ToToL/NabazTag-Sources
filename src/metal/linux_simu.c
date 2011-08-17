#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

#include "linux_simuaudio.h"
#include "linux_simunet.h"
#include "log.h"
#include "linux_simuled.h"
#include "linux_simulog.h"
#include "linux_simumotor.h"

int getButton() {
	return 0;
}

WINDOW * general_scr;

/***************************
 * La fenetre en general
 ***************************/

int simuDisplayInit(void) {
    general_scr = initscr();
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
    nodelay(general_scr, 1);
    WLED_Init();
    WLOG_Init();
    WMOTOR_Init();
    return 0;
}

int simuDisplay(void){
    WLED_Display();
    WLOG_Display();
    WMOTOR_Display();
    return 0;
}

// initialisation du simulateur
long simuInit()
{
	int i;

	srand(clock());
//	setButton(1);
	simuaudioinit();
	simunetinit();
	simuLedInit();
	simuMotorInit();
	simuDisplayInit();
	return 0;
}

// fonction à appeler régulièrement, pour traiter les messages de la fenêtre du simulateur
long simuDoLoop()
{
	checkNetworkEvents();
	simuFetch();
	simuMotor();
	simuKeys();
	simuDisplay();
	return 0;
}

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
