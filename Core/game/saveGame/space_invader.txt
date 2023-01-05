/*
 * pong.c
 *
 *  Created on:
 *      Author:
 */
#include "main.h"

#include "../lib/ssd1306.h"
#include "../lib/ssd1306_tests.h"
#include "../game/pong/pong.h"

typedef enum{
    INIT=0,
    GAME
}states;

typedef struct{
	InputButton buttonStat;
	int8_t xPl;
	int8_t yPl;
	int8_t fireOn;
	int8_t xFire;
	int8_t yFire;
	int8_t xTarget;
	int32_t yTarget;
	int8_t targetOn;
	int8_t lose;
}ram_pong;


void pong(Program_t *prog){
    ram_pong *myRam = (ram_pong*) prog->ram;
    switch(prog->state){
        case INIT:{
        	prog->state = GAME;

        	// your code of initialisation
        	myRam->xPl=4;
        	myRam->yPl=32;
        	myRam->yTarget=13;
        	myRam->targetOn=0;
        	myRam->lose=0;
            break;
            }
        case GAME:{
        	prog->driver->getButtonStats(&myRam->buttonStat);

        	// your code of game
        	if(myRam->lose==0){


				if(myRam->buttonStat.Top && myRam->yPl>5){
					myRam->yPl-=1;
				}
				if(myRam->buttonStat.Bottom && myRam->yPl<59){
					myRam->yPl+=1;
				}
				if(myRam->buttonStat.A && myRam->fireOn==0){
					myRam->xFire=4;
					myRam->yFire=myRam->yPl;
					myRam->fireOn=1;
				}
				if(myRam->xFire>=126){
					myRam->fireOn=0;
				}

				if(myRam->targetOn==1){
					myRam->xTarget-=1;
				}
				if(myRam->targetOn==0){
					myRam->xTarget=127;
					myRam->yTarget = (1664525*myRam->yTarget+1013904223)%63;
					if(myRam->yTarget<5){
						myRam->yTarget+=10;
					}
					myRam->targetOn=1;
				}

				if((myRam->yFire==myRam->yTarget-3 || myRam->yFire==myRam->yTarget-2 || myRam->yFire==myRam->yTarget-1 || myRam->yFire==myRam->yTarget || myRam->yFire==myRam->yTarget-4 || myRam->yFire==myRam->yTarget-5 || myRam->yFire==myRam->yTarget-6) && myRam->xFire>myRam->xTarget){
					myRam->fireOn=0;
					myRam->targetOn=0;
				}

				if(myRam->xTarget<=3){
					myRam->targetOn=0;
					myRam->lose=1;
				}




				prog->driver->ssd1306_Fill(Black);

				if(myRam->fireOn==1){
					myRam->xFire+=2;
					prog->driver->ssd1306_Line(myRam->xFire, myRam->yFire, myRam->xFire+1, myRam->yFire, White);
				}

				if(myRam->targetOn==1){
					prog->driver->ssd1306_DrawCircle(myRam->xTarget-3, myRam->yTarget-3, 3, White);
				}

				prog->driver->ssd1306_Line(4, myRam->yPl-3, 4, myRam->yPl+3, White);
				prog->driver->ssd1306_Line(4, myRam->yPl-3, 7, myRam->yPl, White);
				prog->driver->ssd1306_Line(4, myRam->yPl+3, 7, myRam->yPl, White);
				prog->driver->ssd1306_UpdateScreen();
        	}
        	if(myRam->lose==1){

        		if(myRam->buttonStat.A){
        			myRam->lose=0;
        		}

        		prog->driver->ssd1306_Fill(Black);

        		prog->driver->sprintf("%4d","lose");
        		prog->driver->ssd1306_SetCursor(49,0);
        		prog->driver->ssd1306_WriteString("lose",Font_6x8,White);

        		prog->driver->ssd1306_UpdateScreen();

        	}
            break;
        }
    }
}
