/*
 * pong.c
 *
 *  Created on: Sep 27, 2022
 *      Author: julie
 */
#include "main.h"

#include "../lib/ssd1306.h"
#include "../lib/ssd1306_tests.h"

int8_t x = 64;
int8_t sensx = 2;
int8_t y = 32;
int8_t sensy = 1;
int8_t fill = 0;
int8_t start = 0;

void pong(void){
	InputButton buttonStats = getButtonStats();
	/*
	if(x>=128){
		sensx=-sensx;
	}else if(x<=10){
		sensx=-sensx;
	}
	if(y>=64){
		sensy=-sensy;
	}else if(y<=10){
		sensy=-sensy;
	}
	x+=sensx;
	y+=sensy;
	*/
	if(buttonStats.Start){
		start = 1;
	}
	if(!start){
		if(buttonStats.Left){
			x--;
		}else if(buttonStats.Right){
			x++;
		}
		if(buttonStats.Bottom){
			y++;
		}else if(buttonStats.Top){
			y--;
		}
		if(buttonStats.A){
			fill = 1;
		}else if(buttonStats.B){
			fill = 0;
		}
		if(buttonStats.Select){
			x = 64;
			y = 32;
		}

		if(fill){
			ssd1306_Fill(Black);
		}else{
			ssd1306_Fill(White);
		}
		ssd1306_DrawCircle(x-5, y-5, 5, White);
		ssd1306_UpdateScreen();
	}
}

