/*
 * Controler.c
 *
 *  Created on: Oct 11, 2022
 *      Author: julie
 */

#include "main.h"
#include "Controler.h"


int8_t btnStats[] = {0,0,0,0,0,0,0,0};

void readButton(void){
	static int8_t it = 0;
	if(it >= 10){
		it = 0;
		for(int i=0; i<7; i++){
			btnStats[i] = (int8_t)HAL_GPIO_ReadPin(GPIOE, 1<<i);
		}
		btnStats[7] = (int8_t)HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
	}else{
		it++;
	}
}

void getButtonStats(InputButton *btn){
	btn->Select = btnStats[0];
	btn->Top = btnStats[1];
	btn->Start = btnStats[2];
	btn->Right = btnStats[3];
	btn->A = btnStats[4];
	btn->Left = btnStats[5];
	btn->B = btnStats[6];
	btn->Bottom = btnStats[7];
}

