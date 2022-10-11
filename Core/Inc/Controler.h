/*
 * Controler.h
 *
 *  Created on: Oct 11, 2022
 *      Author: julie
 */

#ifndef INC_CONTROLER_H_
#define INC_CONTROLER_H_

typedef struct{
	int8_t Select;
	int8_t Top;
	int8_t Start;
	int8_t Right;
	int8_t A;
	int8_t Left;
	int8_t B;
	int8_t Bottom;
}InputButton;


void readButton(void);
void getButtonStats(InputButton *btn);


#endif /* INC_CONTROLER_H_ */
