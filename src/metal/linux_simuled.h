#ifndef _MY_SIMULED_H_
#define _MY_SIMULED_H_

#define NBLED 15

// Colorer une LED
void simuSetLed(int i,int val); 

int simuLedInit(void);

/******************************
 * Fenetre des LEDs du NabazTag
 ******************************/

int round_256(int val);
int WLED_SelectColor(int a,int b,int c);
void WLED_Display(void);
void WLED_Base(int y, int x);
int WLED_Init(void);

#endif
