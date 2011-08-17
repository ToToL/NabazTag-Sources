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
WINDOW * window_LOG;
FILE * toread;

void WLOG_Display(void) {
	wrefresh(window_LOG);
}

int WLOG_Init(void) {

    window_LOG = newwin(50, 100, 0, 45);
    scrollok(window_LOG,1);
    refresh();
    toread = fopen(PropGet("LOGFILE"),"r");
    return 0;
}

void WLOG_Add(int log, const char * buff) {
	if ( window_LOG != NULL )
		wprintw(window_LOG,buff);
}
