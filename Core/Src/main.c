/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

//include screen lib
#include "stdio.h"
#include "../lib/ssd1306_tests.h"
#include "../lib/music.h"
#include "config.h"

//include flash lib
#include "w25qxx.h"

//include game
//#include "../game/realPong/realPong.h"
#include "../inc/Controler.h"

#if (MEMORY_FLASH == 1)

#include "../game/pong/pong.h"

#endif

//include menu interface

//include menu interface

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */




/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/*
int8_t buttonStats[] = {0,0,0,0,0,0,0,0};

uint8_t indexFlash[1] = {0};
uint8_t buffer1[20];
uint8_t buffer2[100] = {0};
*/

#if (MEMORY_FLASH == 1)

int8_t buttonStats[] = {0,0,0,0,0,0,0,0};

uint8_t indexFlash[1] = {0};
uint8_t buffer1[SIZE_CODE];

#else

stepMenu step = STEP_INIT;
uint8_t idGame = 0;

//initialise the program :
static Program_t myGame;
static game_fun_t pGame;

#endif

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  HAL_Delay(1000);

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */

  W25qxx_Init();

  //Init The screen
  ssd1306_Init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
#if (MEMORY_FLASH == 0)

  while (1)
  {
	/* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
	static uint8_t game_running = 0;
	switch(step){
		case STEP_INIT : {
			step = STEP_MENU;
			break;
		}
		case STEP_MENU : {
			game_running = 0;
			drawMenu(&game_running);
			if (game_running){
				step = STEP_LOAD_GAME;
			}else{
				step = STEP_BACKGROUND;
			}
			break;
		}
		case STEP_LOAD_GAME: {
			loadGame();
			step = STEP_GAME;
			break;
		}
		case STEP_GAME : {
			runGame();
			step = STEP_BACKGROUND;
			break;
		}
		case STEP_BACKGROUND : {
			MUSIC_Process_main();

			if (!game_running){
				step = STEP_MENU;
				actualiseMenu();
			}else if(getSelectButton()){
				step = STEP_MENU;
				actualiseMenu();
			}else{
				step = STEP_GAME;
			}
			break;
		}
		}

  	}
#else

  	//0x8003ca4
	extern uint8_t _begin_game;
	extern uint8_t _end_game;

	volatile uint8_t *pbegin = &_begin_game;
	volatile uint8_t *pend = &_end_game;

	/*while(1){
	  ssd1306_TestCircle();
	}*/
	//initialise the program :
	static Program_t myGame;
	static game_fun_t pGame;


	//Copy the game into the ram
	//Copy(myGAME.code)
	uint8_t * pG;
	pG = (uint8_t *)pGame;
	uint32_t i = 0;
	while ((pbegin+i) < pend){
	  myGame.code[i] = pbegin[i];
	  i++;
	}


	W25qxx_EraseSector(0);
	int8_t b[1] = {1};
	W25qxx_WriteSector(b, 0, 0, 1);
	char text[20] = MEMORY_NAME;
	W25qxx_WriteSector(text, 0, 1, 20);


	W25qxx_EraseSector(1);
	W25qxx_WriteSector(myGame.code,1, 0, SIZE_CODE);

	W25qxx_ReadSector(buffer1, 1, 0, SIZE_CODE);

	//Init the struct with the drivers
	static Driver_t drivers;
	init_drivers(&drivers);
	myGame.driver = &drivers;

	//Start the program :
	pGame = (&myGame.code[0]) + 1;
	myGame.state = 0;
	volatile uint8_t never = 0;
	if(never)
	  pong(&myGame);
	while(1){
	  //pong(&myGame);
	  pGame(&myGame);
	}


	//Make sur the function isn't dump by the compilator

	//realPong(&myGame);
	pong(&myGame);


#endif
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void init_drivers(Driver_t *d){
	d->getButtonStats = &getButtonStats;
	d->ssd1306_DrawCircle = &ssd1306_DrawCircle;
	d->ssd1306_DrawRectangle = &ssd1306_DrawRectangle;
	d->ssd1306_Fill = &ssd1306_Fill;
	d->ssd1306_Line = &ssd1306_Line;
	d->ssd1306_UpdateScreen = &ssd1306_UpdateScreen;
	d->MUSIC_PlayMusic = &MUSIC_PlayMusic;
	d->MUSIC_PlaySound = &MUSIC_PlaySound;
	d->MUSIC_Stop = &MUSIC_Stop;
	d->ssd1306_SetCursor = &ssd1306_SetCursor;
	d->ssd1306_WriteString = &ssd1306_WriteString;
	d->sprintf = &sprintf;
}

#if (MEMORY_FLASH == 0)
void loadGame(){
	//The commented code is used for uploading game to the flash
	/*extern uint8_t _begin_game;
	extern uint8_t _end_game;

	volatile uint8_t * pbegin = &_begin_game;
	volatile uint8_t * pend = &_end_game;


	//Copy the game into the ram
	//Copy(myGAME.code)
	uint8_t * pG;
	pG = (uint8_t *)pGame;
	uint32_t i = 0;*/


	//Load game from flash to ram
	W25qxx_ReadSector(myGame.code, idGame, 0, SIZE_CODE);


	//Init the struct with the drivers
	static Driver_t drivers;
	init_drivers(&drivers);
	myGame.driver = &drivers;

	//Start the program :
	pGame = (&myGame.code[0]) + 1;
	myGame.state = 0;
}

void runGame(){
	pGame(&myGame);
	//realPong(&myGame); //DEBUG
}

void setStep(uint8_t newStep){
	step = newStep;
}
void setIdGame(uint8_t newID){
	idGame = newID;
}
#endif

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
