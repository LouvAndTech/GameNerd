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
uint8_t actuMenuBool = 1;
InputButton ib;
char gameName[20] = {0};

void actuMenu(){
    W25qxx_ReadSector(nbGame, 0, 0, 1);
    if(nbGame[0] > 0){
        loadNameGame(idG);
    }else {
    	gameName[0] = ' ';
    	gameName[1] = 'N';
    	gameName[2] = 'o';
    	gameName[3] = ' ';
    	gameName[4] = 'G';
    	gameName[5] = 'A';
    	gameName[6] = 'M';
    	gameName[7] = 'E';
    }

    ssd1306_Fill(Black);

    ssd1306_SetCursor(32,0); //32 getMiddle(128, "Game Nerd")
    ssd1306_WriteString("Game Nerd", Font_7x10, White);

    drawBox(24, 16, gameName);
    ssd1306_SetCursor(24+15,16+20); //
    ssd1306_WriteString("Start", Font_6x8, White);

    if(onAnim == 0){
        ssd1306_DrawTriangle(115, 35, 120, 40, 115, 45, White);
        ssd1306_DrawTriangle(13, 35, 8, 40, 13, 45, White);
    }
    ssd1306_UpdateScreen();
}

void menuSon(){
	ssd1306_Fill(Black);
	ssd1306_SetCursor(32,0); //32 getMiddle(128, "Game Nerd")
	ssd1306_WriteString("Game Nerd", Font_7x10, White);
	drawBox(24, 16, "Sound");

	if(onAnim == 0){
		ssd1306_DrawTriangle(115, 35, 120, 40, 115, 45, White);
		ssd1306_DrawTriangle(13, 35, 8, 40, 13, 45, White);
	}
	ssd1306_UpdateScreen();

}

typedef enum{
	Init = 0,
	Jeux_init,
	Jeux_pros,
	Son_init,
	Son,
}MenuState;
static MenuState menu_state = Init;

void drawMenu(uint8_t *run){
	switch(menu_state){
		case Init:{
			actuMenu();
			menu_state = Jeux_init;
			break;
		}
		case Jeux_init:{
			actuMenu();
			menu_state = Jeux_pros;
			break;
		}
		case Jeux_pros:{
			getButtonStats(&ib);
			if (ib.Right){
				menu_state = Son_init;
			}else if(ib.A){
				setIdGame(idG);
				*run = 1;
			}
			break;
		}
		case Son_init:{
			MUSIC_PlayMusic(ALARM);
			menu_state = Son;
			break;
		}
		case Son:{
			static uint8_t vol = 50;
			menuSon();
			getButtonStats(&ib);
			if (ib.Left){
				menu_state = Jeux_init;
			}else if(ib.Top){
				vol = (vol>=100)?100:vol+10;
			}else if(ib.Bottom){
				vol = (vol<=0)?0:vol-10;
			}else if(ib.A){
				MUSIC_SetVolume(vol);
			}
			drawVolBar(vol);
			while(ib.Top || ib.Bottom || ib.A){
				getButtonStats(&ib);
			}
			break;
		}
	}
}

void drawVolBar(uint8_t vol){
	ssd1306_DrawRectangle(14, 21 , 14+100, 21+20, Black);
	ssd1306_DrawRectangle(14, 21 , 14+vol, 21+20, White);
	ssd1306_UpdateScreen();
}

void drawBox(int8_t x, int8_t y, char* name){
    //strlen(name);
    ssd1306_DrawRectangle(x, y, x+80, y+40, White);

    ssd1306_SetCursor(x+2,y+5); //
    ssd1306_WriteString(name, Font_6x8, White);
}

void loadNameGame(){
    uint32_t id1 = (20*(idG-1))+1;
    uint32_t id2 = (20*(idG-1))+20;
    W25qxx_ReadSector(gameName, 0, 1, 20);
}

void actualiseMenu(){
	actuMenuBool = 1;
}
