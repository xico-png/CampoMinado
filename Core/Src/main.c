/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

 int bomba[4][4]= {};
 int somadosbut = 0;
 int somadosbutparte2 = 0;
char linhaecoluna[] = "xx";
char xy[2]={'x','x'};
char *xin ="";
char *yin = "";
char x;
char y;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

void piscaled(int tempo1,int tempo2);
void SetBuzzer(int tempo);
int verifica_o_Botao();
void pisca1nled(int tempo1);
int BotaBomba();
void fimdejogo();
void jogadacerta();
void verifica_o_Botao_coluna();
void verificalinha(char *coluna);
int explodebomba();
void ZeraMatriz();

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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


  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */


	BotaBomba();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */



  while (1)
  {


	  if(explodebomba()==0){
		  jogadacerta();
		  //piscaled(2000,1000);
	  }


	  else
	  {
		  fimdejogo();
	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PC15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB10 PB11
                           PB12 PB13 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA8 PA9 PA11 PA12
                           PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3 PB4 PB5 PB6
                           PB7 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
int explodebomba(){
	int X = 0;
	int Y = 0;
	verifica_o_Botao_coluna();
	char x = xy[0];
	char y = xy[1];
	if(x == 'A')
	{
		X = 0;
	}
	if(x == 'B')
	{
		X = 1;
	}
	if(x == 'C')
	{
		X = 2;
	}
	if(x == 'D')
	{
		X = 3;
	}
	if(y == '0')
	{
		Y = 0;
	}
	if(y == '1')
	{
		Y = 1;
	}
	if(y == '2')
	{
		Y = 2;
	}
	if(y == '3')
	{
		Y = 3;
	}

	if(bomba[X][Y] == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void verificalinha(char* coluna)
{
char tranca1 =  '0';
while(tranca1 == '0')
{
	if(coluna!='x')
	{
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == 0) //0
		{
			*xin = 'A';
			tranca1 = '1';
		}
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15)== 0) //1
		{ 			 //return 1;
			*xin = 'B';
			tranca1 = '1';
		}

		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7) == 0) //2
		{
			*xin = 'C';
			tranca1 = '1';

		}
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == 0) //3
		{
			*xin = 'D';
			tranca1 = '1';
		}
	}

	else
	{
		xy[0] = 'x';
		xy[1]= 'x';
		tranca1 = '1';
	}
}
}


void verifica_o_Botao_coluna(){
xin = &xy[0];
yin = &xy[1];

char tranca = '0';


		//Pin B9 = button 0;
		//Pin C15 = button 1;
		//Pin B7 = button 2;
		//Pin B6 = button 3;
		//Pin B5 = button 4;
		//Pin B4 = button 5;
		//Pin B3 = button 6;
		//Pin A15 = button 7;
		//Pin A12 = button 8;
		//Pin A11 = button 9;
while(tranca == '0'){
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == 0) //0 // funciona
		{
			*yin = 'x';
			*xin = 'x';
			tranca = '1';
		}


		 if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15)== 0) //1 //  entrou
		{ 			 //return 1;
			 	 	*yin = 'x';
			 		*xin = 'x';
					tranca = '1';
		}

		 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7) == 0) //3 // funciona
		{
			 	 	*yin = 'x';
			 		*xin = 'x';
					tranca = '1';
		}
		 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == 0) //4 // funciona
		{
		*yin = 'x';
		*xin = 'x';
		tranca = '1';
		}
		 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 0) //5 // funcioona
		 {
			 *yin = '0';
			 verificalinha(*yin);
				tranca = '1';
		 }
		 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)== 0) //6 // funcuioan
		{
			 *yin = '1';
			 verificalinha(*yin);
				tranca = '1';

		}
		 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0) //7 // funcina
		 {
			 *yin ='2';
			 verificalinha(*yin);
				tranca = '1';
		 }
		 if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0) //8 // idem
		{
			 *yin='3';
			 verificalinha(*yin);
				tranca = '1';
		 }

}



}
void jogadacerta(){
	piscaled(1000,1000);

}
void fimdejogo(){

	piscaled(200,200);
	SetBuzzer(3000); // o certo é 3 segundos

    while(verifica_o_Botao() != 36){
		piscaled(500,500);
		BotaBomba();
	}


}

void ZeraMatriz()
{
	for(int l = 0; l != 4; l++){

			for(int c = 0; c!= 4; c++){
				bomba[l][c] = 0;
			}
		}
}

int BotaBomba(){
	/*for(int l = 0; l != 4; l++){

		for(int c = 0; c!= 4; c++){
			bomba[l][c] = 0;
		}
	}*/
	ZeraMatriz();
	for(int Bombas = 0; Bombas<4; ){
			int Rlinha  = rand()%5;
			int RColuna = rand()%5;
			if(bomba[Rlinha][RColuna]==0){
				bomba[Rlinha][RColuna] = 1;
				Bombas++;
			}

	}
return bomba[4][4];
}
void piscaled(int tempo1,int tempo2)
{
	//B12 = LedB0
	//B10 = LedB1
	//B11 = LedB2
	//B13 = LedB3
	//B0  = LedB4
	//A7  = LedB5
	//A6  = LedB6
	//A5  = LedB7
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
	HAL_Delay(tempo1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_Delay(tempo2);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 1);
	HAL_Delay(tempo1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 0);
	HAL_Delay(tempo2);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 1);
	HAL_Delay(tempo1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0);
	HAL_Delay(tempo2);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 1);
	HAL_Delay(tempo1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 0);
	HAL_Delay(tempo2);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
	HAL_Delay(tempo1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
	HAL_Delay(tempo2);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
	HAL_Delay(tempo1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
	HAL_Delay(tempo2);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
	HAL_Delay(tempo1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
	HAL_Delay(tempo2);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
	HAL_Delay(tempo1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
	HAL_Delay(tempo2);
}

void pisca1nled(int tempo1)
{
	//12 = LedB0
	//10 = LedB1
	//11 = LedB2
	//13 = LedB3
if(verifica_o_Botao() == 0){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
		HAL_Delay(tempo1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);

}
else if (verifica_o_Botao() == 1){

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 1);
	HAL_Delay(tempo1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 0);

}
else if(verifica_o_Botao() == 2){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 1);
	HAL_Delay(tempo1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0);

}
else if(verifica_o_Botao() == 3){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 1);
	HAL_Delay(tempo1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 0);


	}
if(verifica_o_Botao() == 4){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
		HAL_Delay(tempo1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);

}
else if (verifica_o_Botao() == 5){

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
	HAL_Delay(tempo1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);

}
else if(verifica_o_Botao() == 6){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
	HAL_Delay(tempo1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);

}
else if(verifica_o_Botao() == 7){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
	HAL_Delay(tempo1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
	}
}

void SetBuzzer(int tempo)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
	HAL_Delay(tempo);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);
	//HAL_Delay(tempo);
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);
}

int verifica_o_Botao()
{
	somadosbut = 0;

	//Pin B9 = button 0;
	//Pin B8 = button 1;
	//Pin B7 = button 2;
	//Pin B6 = button 3;
	//Pin B5 = button 4;
	//Pin B4 = button 5;
	//Pin B3 = button 6;
	//Pin A15 = button 7;
	//Pin A12 = button 8;
	//Pin A11 = button 9;
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == 0) //0
	{
		somadosbut = 1;
		somadosbutparte2 += somadosbut;

	}
	 if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15)== 0) //1
	{

		somadosbut = 2;
		somadosbutparte2 += somadosbut;
	}

	 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7) == 0) //2
	{
		somadosbut =3;
		somadosbutparte2 += somadosbut;


	}
	 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == 0) //3
	{
		somadosbut=4;
		somadosbutparte2 += somadosbut;


	}
	 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 0) //4
		{
			somadosbut =5;
			somadosbutparte2 += somadosbut;


		}
		 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)== 0) //5
		{
			somadosbut =6;
			somadosbutparte2 += somadosbut;

		}
		 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0) //6
		{
			somadosbut =7;
			somadosbutparte2 += somadosbut;

		}
		 if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0) //7
		{
			somadosbut =8;
			somadosbutparte2 += somadosbut;

		}
		 if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == 0) //9
		 {

			 somadosbutparte2 = 36;
		 }
		 if(somadosbutparte2 == 36){
			return 36;
		}
		 return somadosbut;

}

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
