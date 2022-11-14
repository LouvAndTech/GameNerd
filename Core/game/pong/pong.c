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
}states;

typedef enum{
	MAIN_GAME = 0,
}state_machine_e;

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
	char strscore[10];
	int8_t i;
}ram_pong;


void pong(Program_t *prog){
    ram_pong *myRam = (ram_pong*) prog->ram;
    switch(prog->state){
        case INIT:{
        	myRam->stateMachine = MAIN_GAME;
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
						myRam->barj1-=1;
					}
					if(myRam->buttonStat.Bottom && myRam->barj1<54){
						myRam->barj1+=1;
					}
					if(myRam->buttonStat.A && myRam->barj2>10){
						myRam->barj2-=1;
					}
					if(myRam->buttonStat.B && myRam->barj2<54){
						myRam->barj2+=1;
					}


					if(myRam->ballx==121 && myRam->bally<myRam->barj2+10 && myRam->bally>myRam->barj2-10){
						myRam->speedx=-myRam->speedx;
						prog->driver->MUSIC_PlaySound(SHOOT);
					}
					if(myRam->ballx==8 && myRam->bally<myRam->barj1+10 && myRam->bally>myRam->barj1-10){
						myRam->speedx=-myRam->speedx;
						prog->driver->MUSIC_PlaySound(SHOOT);
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
							myRam->scorej2+=1;
							if(myRam->scorej2 > 9){
								myRam->scorej2=0;
							}
							//myRam->scorej2=(myRam->scorej2 >= 10)? 0 : myRam->scorej2+1;
						}
						if(myRam->ballx==-126){
							myRam->speedx=-1;
							myRam->scorej1+=1;
							if(myRam->scorej1 > 9){
								myRam->scorej1=0;
							}
							//myRam->scorej1=(myRam->scorej1 >= 10)? 0 : myRam->scorej1+1;
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
					//prog->driver->sprintf(myRam->strscore,"%1d   %1d",myRam->scorej1,myRam->scorej2);
					myRam->strscore[0] = myRam->scorej1+48;
					prog->driver->ssd1306_SetCursor(58,0);
					prog->driver->ssd1306_WriteString_better(myRam->strscore,White);
					myRam->strscore[0] = myRam->scorej2+48;
					prog->driver->ssd1306_SetCursor(66,0);
					prog->driver->ssd1306_WriteString_better(myRam->strscore,White);

					for(myRam->i=0; myRam->i<8; myRam->i++){
						prog->driver->ssd1306_Line(64, myRam->i*8, 64, (myRam->i*8)+4, White);
					}


					prog->driver->ssd1306_Line(5, myRam->barj1-10, 5, myRam->barj1+10, White);
					prog->driver->ssd1306_Line(122, myRam->barj2-10, 122, myRam->barj2+10, White);
					prog->driver->ssd1306_DrawCircle(myRam->ballx-1, myRam->bally-1, 1, White);
					prog->driver->ssd1306_UpdateScreen();
					break;
        	}

            break;
        }
    }
}
