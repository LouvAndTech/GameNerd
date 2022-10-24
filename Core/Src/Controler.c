/*
 * Controler.c
 *
 *  Created on: Oct 11, 2022
 *      Author: julie
 */

#include "main.h"
#include "Controler.h"


int8_t btnStats[] = {0,0,0,0,0,0,0,0};
InputButton static ibLocal;

void readButton(void){
	ibLocal.A = (int8_t)HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_13);
	ibLocal.B = (int8_t)HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_15);
	ibLocal.Bottom = (int8_t)HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9);
	ibLocal.Top = (int8_t)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15);
	ibLocal.Right = (int8_t)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9);
	ibLocal.Left = (int8_t)HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7);
	ibLocal.Select = (int8_t)HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12);
	ibLocal.Start = (int8_t)HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_14);
}

void getButtonStats(InputButton *btn){
	btn->Select = ibLocal.Select;
	btn->Top = ibLocal.Top;
	btn->Start = ibLocal.Start;
	btn->Right = ibLocal.Right;
	btn->A = ibLocal.A;
	btn->Left = ibLocal.Left;
	btn->B = ibLocal.B;
	btn->Bottom = ibLocal.Bottom;
}

