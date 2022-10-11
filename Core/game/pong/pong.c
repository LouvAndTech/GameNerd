/*
 * pong.c
 *
 *  Created on: Sep 27, 2022
 *      Author: julie
 */
#include "main.h"

#include "../lib/ssd1306.h"
#include "../lib/ssd1306_tests.h"
#include "../game/pong/pong.h"

typedef struct{
	int8_t x;
	int8_t sensx;
	int8_t y;
	int8_t sensy;
	int8_t fill;
	int8_t start;
	InputButton buttonStat;
}ram_pong;


void pong(Program_t *prog){
	//Init the ram
	ram_pong *myRam = (ram_pong*) prog->ram;
	//Init the variable into the ram
	myRam->x = 64;
	myRam->y = 32;
	myRam->fill = 0;
	myRam->start = 0;
	myRam->sensx = 2;
	myRam->sensy = 1;

	while(1){
		prog->driver->getButtonStats(&myRam->buttonStat);
		//InputButton buttonStats = getButtonStats();
		if(myRam->buttonStat.Start){
			myRam->start = 1;
		}
		if(!myRam->start){
			if(myRam->buttonStat.Left){
				myRam->x--;
			}else if(myRam->buttonStat.Right){
				myRam->x++;
			}
			if(myRam->buttonStat.Bottom){
				myRam->y++;
			}else if(myRam->buttonStat.Top){
				myRam->y--;
			}
			if(myRam->buttonStat.A){
				myRam->fill = 1;
			}else if(myRam->buttonStat.B){
				myRam->fill = 0;
			}
			if(myRam->buttonStat.Select){
				myRam->x = 64;
				myRam->y = 32;
			}

			if(myRam->fill){
				prog->driver->ssd1306_Fill(Black);
			}else{
				prog->driver->ssd1306_Fill(White);
			}
			prog->driver->ssd1306_DrawCircle(myRam->x-5, myRam->y-5, 5, White);
			prog->driver->ssd1306_UpdateScreen();
		}
	}
}

