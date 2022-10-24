/*
 * music.h
 *
 *  Created on: Oct 18, 2022
 *      Author: elouanlerissel
 */

#ifndef LIB_MUSIC_H_
#define LIB_MUSIC_H_


typedef enum{
	SHOOT = 0x01,
	HIT = 0x02,
	MENU_NAV,
	JUMP,
	EXPLOSION,
	WIN,
}Sound;

typedef enum{
	ANIMAL_CROSSING = 0x01,
	ALARM = 0x02,
	GHOST,
}Music;

#include "usart.h"


void MUSIC_Process_main(void);
void MUSIC_setVolume(uint8_t vol);
void MUSIC_PlaySound(Sound sound);
void MUSIC_PlayMusic(Music music);
void MUSIC_Stop(void);



#endif /* LIB_MUSIC_H_ */
