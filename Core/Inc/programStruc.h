/*
 * programStruc.h
 *
 *  Created on: Oct 24, 2022
 *      Author: elouanlerissel
 */

#ifndef SRC_PROGRAMSTRUC_H_
#define SRC_PROGRAMSTRUC_H_

#include "../lib/ssd1306.h"
#include "../lib/music.h"

#define SIZE_CODE 1024
#define SIZE_RAM 1024

typedef struct{
	int8_t Top;
	int8_t Start;
	int8_t Right;
	int8_t A;
	int8_t Left;
	int8_t B;
	int8_t Bottom;
}InputButton;

typedef struct{
	void (*ssd1306_Fill)(SSD1306_COLOR color);
	void (*ssd1306_UpdateScreen)(void);
	void (*ssd1306_Line)(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
	void (*ssd1306_DrawCircle)(uint8_t par_x, uint8_t par_y, uint8_t par_r, SSD1306_COLOR color);
	void (*ssd1306_DrawRectangle)(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
	void (*getButtonStats)(InputButton *btn);
	void (*MUSIC_PlaySound)(Sound sound);
	void (*MUSIC_PlayMusic)(Music music);
	void (*MUSIC_Stop)(void);
}Driver_t;



typedef struct{
		uint8_t code[SIZE_CODE];
		uint8_t ram[SIZE_RAM];
		Driver_t *driver;
		uint8_t state;
}Program_t;


typedef void(*game_fun_t)(Program_t *prog); //Type pointeur sur fonction

typedef struct{
	Program_t prog;
	game_fun_t pGame;
}CompleteGame;

#endif /* SRC_PROGRAMSTRUC_H_ */
