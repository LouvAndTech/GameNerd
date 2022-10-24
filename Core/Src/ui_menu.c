/*
 * UI_Menu.c
 *
 *  Created on: Oct 18, 2022
 *      Author: julie
 */

#include <ui_menu.h>
#include "main.h"
#include "../lib/ssd1306_tests.h"
#include "Controler.h"
#include "w25qxx.h"


uint8_t getMiddle(int8_t max, char* str);
uint8_t idG = 1;
uint8_t nbGame[1] = {0};
uint8_t onAnim = 0;
InputButton ib;
char gameName[20] = {0};

void menuUiInit(){
	/*
	W25qxx_ReadSector(nbGame, 0, 0, 1);
	if(nbGame[0] > 0){
		loadNameGame(idG);
	}
	*/
	ssd1306_Fill(Black);

	ssd1306_SetCursor(32,0); //32 getMiddle(128, "Game Nerd")
	ssd1306_WriteString("Game Nerd", Font_7x10, White);

	drawBox(24, 16, "Load Game");

	if(onAnim == 0){
		ssd1306_DrawTriangle(115, 35, 120, 40, 115, 45, White);
		ssd1306_DrawTriangle(13, 35, 8, 40, 13, 45, White);
	}
	ssd1306_UpdateScreen();
}

void drawMenu(){
	menuUiInit();
	getButtonStats(&ib);
	if(ib.A){
		setStep(GAME);
		setIdGame(idG);
	}
	if(ib.Right){
		if(nbGame[0] > idG){
			idG++;
			loadNameGame(idG);
		}
	}
	if(ib.Left){
		if(idG > 1){
			idG--;
			loadNameGame(idG);
		}
	}
}

void drawBox(int8_t x, int8_t y, char* name){
	//strlen(name);
	ssd1306_DrawRectangle(x, y, x+80, y+40, White);

    ssd1306_SetCursor(x+2,y+5); //
	ssd1306_WriteString(gameName, Font_6x8, White);
    ssd1306_SetCursor(x+15,y+20); //
	ssd1306_WriteString("Start", Font_6x8, White);
}

void loadNameGame(int8_t nbId){
	W25qxx_ReadSector(gameName, 0, 1, 20);
}

