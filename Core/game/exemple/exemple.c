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

typedef enum{
    INIT=0,
    GAME
}statese;

typedef enum{
	MAIN_GAME = 0,
	TEST
}state_machine_ee;

typedef struct{
	int8_t stateMachine;
	InputButton buttonStat;
	int8_t scorej1;
	int8_t scorej2;
	int8_t barj1;
	int8_t barj2;
	int8_t ballx;
	int8_t bally;
	int8_t speedx;
	int8_t speedy;

	char alla[50];
}ram_ponge;


void ponge(Program_t *prog){
    ram_ponge *myRam = (ram_ponge*) prog->ram;
    switch(prog->state){
        case INIT:{
        	myRam->stateMachine = TEST;
        	myRam->barj1 = 32;
        	myRam->barj2 = 32;
        	myRam->ballx = 64;
        	myRam->bally = 32;
        	myRam->scorej1 = 0;
        	myRam->scorej2 = 0;
        	myRam->speedx = 1;
        	myRam->speedy = 1;
        	prog->state = GAME;
            break;
            }
        case GAME:{
        	prog->driver->getButtonStats(&myRam->buttonStat);
        	switch(myRam->stateMachine){
				case MAIN_GAME:


					if(myRam->buttonStat.Top && myRam->barj1>10){
						myRam->barj1-=2;
					}
					if(myRam->buttonStat.Bottom && myRam->barj1<54){
						myRam->barj1+=2;
					}
					if(myRam->buttonStat.A && myRam->barj2>10){
						myRam->barj2-=2;
					}
					if(myRam->buttonStat.B && myRam->barj2<54){
						myRam->barj2+=2;
					}


					if(myRam->ballx==121 && myRam->bally<myRam->barj2+10 && myRam->bally>myRam->barj2-10){
						myRam->speedx=-myRam->speedx;
					}
					if(myRam->ballx==8 && myRam->bally<myRam->barj1+10 && myRam->bally>myRam->barj1-10){
						myRam->speedx=-myRam->speedx;
					}
					if(myRam->bally==0){
						myRam->speedy=-myRam->speedy;
					}
					if(myRam->bally==64){
						myRam->speedy=-myRam->speedy;
					}


					if(myRam->ballx==0 || myRam->ballx==-126){
						if(myRam->ballx==0){
							myRam->speedx=1;
						}
						if(myRam->ballx==-126){
							myRam->speedx=-1;
						}
						myRam->ballx=64;
						myRam->bally = 32;
						myRam->speedy = 1;
						myRam->barj1 = 32;
						myRam->barj2 = 32;
					}


					myRam->ballx+=myRam->speedx;
					myRam->bally+=myRam->speedy;
					prog->driver->ssd1306_Fill(Black);
					prog->driver->ssd1306_Line(5, myRam->barj1-10, 5, myRam->barj1+10, White);
					prog->driver->ssd1306_Line(122, myRam->barj2-10, 122, myRam->barj2+10, White);
					prog->driver->ssd1306_DrawCircle(myRam->ballx-1, myRam->bally-1, 1, White);
					prog->driver->ssd1306_UpdateScreen();
					break;


				case TEST:
					prog->driver->sprintf(myRam->alla,"x:%03d y:%03d",myRam->ballx, myRam->bally);
					//ssd1306_TestAll();
					prog->driver->ssd1306_SetCursor(2,0);
					prog->driver->ssd1306_WriteString(myRam->alla, Font_6x8, White);

					prog->driver->ssd1306_UpdateScreen();
					break;
        	}

            break;
        }
    }
}
