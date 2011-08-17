#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

#include "linux_simuaudio.h"
#include "linux_simunet.h"
#include "log.h"
#include "linux_simuled.h"
#include "properties.h"

// Ncurses des logs
WINDOW * window_LOG_BOX;
WINDOW * window_LOG;
WINDOW * window_INFO;

int local_log_msk = LOG_INIT | LOG_VM | LOG_SIMUNET | LOG_SIMUAUDIO | LOG_SIMULEDS | LOG_SIMUMOTORS;
int log_pos[2];

void WLOG_Display(void) {
	if ( local_log_msk & LOG_INIT ) 
		mvwprintw(window_INFO,log_pos[1]+0,log_pos[0],"on ");
	else
		mvwprintw(window_INFO,log_pos[1]+0,log_pos[0],"off");
	if ( local_log_msk & LOG_VM ) 
		mvwprintw(window_INFO,log_pos[1]+1,log_pos[0],"on ");
	else
		mvwprintw(window_INFO,log_pos[1]+1,log_pos[0],"off");
	if ( local_log_msk & LOG_SIMUNET ) 
		mvwprintw(window_INFO,log_pos[1]+2,log_pos[0],"on ");
	else
		mvwprintw(window_INFO,log_pos[1]+2,log_pos[0],"off");
	if ( local_log_msk & LOG_SIMUAUDIO ) 
		mvwprintw(window_INFO,log_pos[1]+3,log_pos[0],"on ");
	else
		mvwprintw(window_INFO,log_pos[1]+3,log_pos[0],"off");
	if ( local_log_msk & LOG_SIMULEDS ) 
		mvwprintw(window_INFO,log_pos[1]+4,log_pos[0],"on ");
	else
		mvwprintw(window_INFO,log_pos[1]+4,log_pos[0],"off");
	if ( local_log_msk & LOG_SIMUMOTORS ) 
		mvwprintw(window_INFO,log_pos[1]+5,log_pos[0],"on ");
	else
		mvwprintw(window_INFO,log_pos[1]+5,log_pos[0],"off");
	wrefresh(window_LOG);
	wrefresh(window_INFO);
}

void WINFO_Base(int x , int y ) {
	mvwprintw(window_INFO,y,x+14,"Divers");
	mvwprintw(window_INFO,y+2,x,"Logs Init    :");
	mvwprintw(window_INFO,y+3,x,"Logs VM      :");
	mvwprintw(window_INFO,y+4,x,"Logs Net     :");
	mvwprintw(window_INFO,y+5,x,"Logs Audio   :");
	mvwprintw(window_INFO,y+6,x,"Logs LEDs    :");
	mvwprintw(window_INFO,y+7,x,"Logs Moteurs :");
	log_pos[0] = x+17;
	log_pos[1] = y+2;
	return;
}

int WLOG_Init(void) {

    window_LOG_BOX = newwin(52, 103, 0, 45);
    window_LOG = newwin(49, 98, 2, 48);
    window_INFO = newwin(18, 40, 34, 2);
    scrollok(window_LOG,1);
    box(window_INFO,0,0);
    box(window_LOG_BOX,0,0);
    WINFO_Base(3,1 );
    refresh();
    wrefresh(window_LOG_BOX);
    return 0;
}

void WLOG_Add(int log, const char * buff) {
	if ( window_LOG != NULL && log & local_log_msk )
		wprintw(window_LOG,buff);
}

int simuKeys(void) {
	int key;

	key = getch();

	if ( key == 'a' )
		if ( local_log_msk & LOG_INIT )
			local_log_msk &= LOG_VM | LOG_SIMUNET | LOG_SIMUAUDIO | LOG_SIMULEDS | LOG_SIMUMOTORS;
		else
			local_log_msk |= LOG_INIT;
	else if ( key == 'z' )
		if ( local_log_msk & LOG_VM )
			local_log_msk &= LOG_INIT | LOG_SIMUNET | LOG_SIMUAUDIO | LOG_SIMULEDS | LOG_SIMUMOTORS;
		else
			local_log_msk |= LOG_VM;
	else if ( key == 'e' )
		if ( local_log_msk & LOG_SIMUNET )
			local_log_msk &= LOG_VM | LOG_INIT | LOG_SIMUAUDIO | LOG_SIMULEDS | LOG_SIMUMOTORS;
		else
			local_log_msk |= LOG_SIMUNET;
	else if ( key == 'r' )
		if ( local_log_msk & LOG_SIMUAUDIO )
			local_log_msk &= LOG_VM | LOG_SIMUNET | LOG_INIT | LOG_SIMULEDS | LOG_SIMUMOTORS;
		else
			local_log_msk |= LOG_SIMUAUDIO;
	else if ( key == 't' )
		if ( local_log_msk & LOG_SIMULEDS )
			local_log_msk &= LOG_VM | LOG_SIMUNET | LOG_SIMUAUDIO | LOG_INIT | LOG_SIMUMOTORS;
		else
			local_log_msk |= LOG_SIMULEDS;
	else if ( key == 'y' )
		if ( local_log_msk & LOG_SIMUMOTORS )
			local_log_msk &= LOG_VM | LOG_SIMUNET | LOG_SIMUAUDIO | LOG_SIMULEDS | LOG_INIT;
		else
			local_log_msk |= LOG_SIMUMOTORS;
	return 0;
}
