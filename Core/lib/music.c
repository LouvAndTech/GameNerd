/*
 * music.c
 *
 *  Created on: Oct 18, 2022
 *      Author: elouanlerissel
 */

#include "../lib/music.h"

typedef enum{
	START = 0,
	PREP,
	INIT,
	WAIT,
	SEND,
}State_music;

static uint8_t buff[8]; //Data to send
static State_music state = RESET;
static uint32_t lastCall = 0;

void MUSIC_Process_main(void){
	switch(state){
		case START : {
			Reset_buff();
			lastCall = Get_Time();
			state = PREP;
			break;
		}
		case PREP : {
			Chip_reset();
			send();
			reset_buff();
			if (Get_Time()-lastCall >= 1000){
				lastCall = Get_Time();
				state = INIT;
			}
			break;
		}
		case INIT : {
			Init();
			send();
			reset_buff();
			SetVolume(0x05);
			send();
			reset_buff();
			if (Get_Time()-lastCall >= 1000){
				lastCall = Get_Time();
				state = INIT;
			}
			break;
		}
		case WAIT : {
			if (buff[3]){
				state = SEND;
			}
			break;
		}
		case SEND : {
			send();
			reset_buff();
			state = WAIT;
			break;
		}

	}
}


/**
 * init the mp3 player
 */
void Init(){
	//select the divers
	buff[3] = 0x09;
	buff[6] = 0x02;
}
/**
 * Play a sound effect
 * @param a Sound from the enum
 */
void MUSIC_PlaySound(Sound sound){
	buff[3] = 0x0f;
	buff[5] = 0x01;
	buff[6] = sound;
}
/**
 * Play the music
 * @param A music un the enum
 */
void MUSIC_PlayMusic(Music music){
	buff[3] = 0x0f;
	buff[5] = 0x02;
	buff[6] = music;
}

/**
 * Set the volume of the output
 * @param the volume in Hexa : 0xff max 0x01 min
 */
void MUSIC_SetVolume(uint8_t vol){
	buff[3] = 0x06;
	buff[6] = vol;
}

/**
 * Stop the music playing now
 */
void MUSIC_Stop(void){
	buff[3] = 0x16;
}

/**
 * Reset the MP3 chip
 */
void Chip_reset(){
	buff[3] = 0x0C;
}

/**
 * Send the prebuild command over UART
 */
void Send(){
	HAL_UART_Transmit(&huart4,&buff,sizeof(buff),10);
}
/**
 * Reset the command buffer
 */
void Reset_buff(){
	buff[0] = 0x7e;
	buff[1] = 0xff;
	buff[2] = 0x06;
	buff[3] = 0x00; //command Byte
	buff[4] = 0x00;
	buff[5] = 0x00;
	buff[6] = 0x00;
	buff[7] = 0xef; //ending byte
}


