/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "./programStruc.h"
#include "../lib/music.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */


typedef enum{
    STEP_INIT=0,
	STEP_MENU,
	STEP_LOAD_GAME,
	STEP_GAME,
	STEP_BACKGROUND
}stepMenu;




/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void init_drivers(Driver_t *d);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Flash_CS_Pin GPIO_PIN_15
#define Flash_CS_GPIO_Port GPIOE
#define btn_Select_Pin GPIO_PIN_12
#define btn_Select_GPIO_Port GPIOD
#define btn_A_Pin GPIO_PIN_13
#define btn_A_GPIO_Port GPIOD
#define btn_Start_Pin GPIO_PIN_14
#define btn_Start_GPIO_Port GPIOD
#define btn_B_Pin GPIO_PIN_15
#define btn_B_GPIO_Port GPIOD
#define btn_Left_Pin GPIO_PIN_7
#define btn_Left_GPIO_Port GPIOC
#define btn_Bottom_Pin GPIO_PIN_9
#define btn_Bottom_GPIO_Port GPIOC
#define btn_Right_Pin GPIO_PIN_9
#define btn_Right_GPIO_Port GPIOA
#define btn_Top_Pin GPIO_PIN_15
#define btn_Top_GPIO_Port GPIOA
#define OLED_Res_Pin GPIO_PIN_7
#define OLED_Res_GPIO_Port GPIOB
#define OLED_DC_Pin GPIO_PIN_9
#define OLED_DC_GPIO_Port GPIOB
#define OLED_CS_Pin GPIO_PIN_1
#define OLED_CS_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
