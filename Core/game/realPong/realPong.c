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

#define SIZE_BALL 5
#define SIZE_PLAYER 5


typedef enum{
	READ_BUTTON = 0,
	MOVE_PLAYER,
	MOVE_BALL,
	CHECK_COLISION,
	DISPLAY,
	GAME_OVER
}State;

typedef struct{
	State state;
	int8_t playerY;
	int8_t ballX;
	int8_t ballY;
	int8_t ball_moveX;
	int8_t ball_moveY;
	uint16_t last;
	InputButton button;
}ram_realPong;


void realPong(Program_t *prog){
	//Init the ram
	ram_realPong *myRam = (ram_realPong*) prog->ram;
	prog->driver->ssd1306_Fill(Black);
	//Init the variable into the ram
	myRam->state = READ_BUTTON;
	myRam->playerY = 32; //The player stay at the X = 5 and mesure 5pix
	myRam->ballX = 64;
	myRam->ballY = 32;
	myRam->ball_moveX = 1; //Move to the right(1) left(0)
	myRam->ball_moveY = 1; //Move to the top(1) bottom(0)
	myRam->last = 0;


	while(1){
		switch(myRam->state){
			case READ_BUTTON:{
				//update the button states
				prog->driver->getButtonStats(&myRam->button);
				//If the player want to act :
				if(myRam->button.Top | myRam->button.Bottom){
					myRam->state = MOVE_PLAYER;
				}else{ //Else move on
					myRam->state = MOVE_BALL;
				}
				break;
			}
			case MOVE_PLAYER:{
				//Update the pos of the player but check if not out limit
				if (myRam->button.Top){
					myRam->playerY = (myRam->playerY>=64)? 64: myRam->playerY+1;
				}else{
					myRam->playerY = (myRam->playerY<=0)? 0: myRam->playerY-1;
				}
				myRam->state = MOVE_BALL;
				break;
			}
			case MOVE_BALL:{
				myRam->last++;
				if (myRam->last >= 10){
					myRam->ballX += (myRam->ball_moveX)? 1: -1;
					myRam->ballY += (myRam->ball_moveY)? 1: -1;
					myRam->last = 0;
				}
				myRam->state = CHECK_COLISION;
				break;
			}
			case CHECK_COLISION:{
				if (myRam->ballX==5){
					if(((myRam->ballY + SIZE_BALL) <= (myRam->playerY - SIZE_PLAYER)) | ((myRam->ballY - SIZE_BALL) >= (myRam->playerY + SIZE_PLAYER))){
						myRam->ball_moveX = !myRam->ball_moveX;
					}
				}
				if (((myRam->ballY - SIZE_BALL) <= 0) | ((myRam->ballY + SIZE_BALL) >= 64)){
					myRam->ball_moveY = !myRam->ball_moveY;
				}
				if ((myRam->ballX + SIZE_BALL) >= 128){
					myRam->ball_moveX = !myRam->ball_moveX;
				}
				if ((myRam->ballX - SIZE_BALL) <= 0){
					myRam->state = GAME_OVER;
				}
				myRam->state = DISPLAY;
				break;
			}
			case DISPLAY:{
				prog->driver->ssd1306_Fill(Black);
				prog->driver->ssd1306_DrawCircle(myRam->ballX, myRam->ballY, SIZE_BALL, White);
				prog->driver->ssd1306_Line(5,myRam->playerY+SIZE_PLAYER,5,myRam->playerY-SIZE_PLAYER,White);
				prog->driver->ssd1306_UpdateScreen();
				myRam->state = READ_BUTTON;
				break;
			}
			case GAME_OVER:{
				prog->driver->ssd1306_Fill(White);
				prog->driver->ssd1306_UpdateScreen();
				break;
			}
		}

	}

}

