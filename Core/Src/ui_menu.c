/*
 * UI_Menu.c
 *
 *  Created on: Oct 18, 2022
 *      Author: julie
 */

#include <ui_menu.h>
#include "main.h"
#include "../lib/ssd1306_tests.h"


uint8_t getMiddle(int8_t max, char* str);
uint8_t idGame = 0;
uint8_t onAnim = 0;

void drawMenu(){
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

void drawBox(int8_t x, int8_t y, char* name){
	//strlen(name);
	ssd1306_DrawRectangle(x, y, x+80, y+40, White);

    ssd1306_SetCursor(x+2,y+5); //
	ssd1306_WriteString("Game Nerd", Font_6x8, White);
    ssd1306_SetCursor(x+15,y+20); //
	ssd1306_WriteString("Start", Font_6x8, White);




}

