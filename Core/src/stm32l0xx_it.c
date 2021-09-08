/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Bleeper board GPIO driver implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
/**
  ******************************************************************************
  * @file    stm32l0xx_it.c
  * @author  MCD Application Team
  * @brief   manages interupt
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hw.h"
#include "vcom.h"
#include "stm32l0xx_it.h"
#include "modbus_master.h"
#include "ringbuffer.h"
#include "trans_recieve_buff_control.h"
#include "main.h"


/** @addtogroup STM32L1xx_HAL_Examples
  * @{
  */

/** @addtogroup SPI_FullDuplex_ComPolling
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern UART_HandleTypeDef huart2;
int bytecount;

int varcheck;
int varcheckt35;

uint8_t handler;
uint8_t thandler;
uint8_t t7handler;
uint8_t telapsehandler;
int bytecount;
int TotalCharsReceived;
uint8_t recieve_reghand;
int rec_count;
uint8_t timercount;
uint8_t interruptflag;
uint8_t interruptsource;
int aftertimercount;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */

void NMI_Handler(void)
{
}


/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */


void HardFault_Handler(void)
{
  while (1)
  {
    __NOP();
  }

}


/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/******************************************************************************/
/*                 STM32L1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l1xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


void USART2_IRQHandler(void)
{
	handler++;
  /* USER CODE BEGIN USART1_IRQn 0 */
	HAL_TIM_Base_Stop_IT(&htim6);	//DISABLE TIMER 6
	TIM6->CNT=0U;		//CLEAR COUNTER VALUES
	HAL_TIM_Base_Stop_IT(&htim7);	//DISABLE TIMER 6
	TIM7->CNT=0U;		//CLEAR COUNTER VALUES
	
		//DISABLE TIMER 7
	
			//CLEAR
		Modbus_Master_Rece_Handler();
  /* USER CODE END USART2_IRQn 0 */
  //HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */
	
		//ENABLE TI2MER 6
    	//ENABLE TI2MER 6
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);
	if(__HAL_TIM_GET_FLAG(&htim6,TIM_IT_UPDATE) != RESET)
	{
		interruptflag = 0x01;
	}
	else
		{
			interruptflag = 0x02;
		}
	
if(__HAL_TIM_GET_IT_SOURCE(&htim6,TIM_IT_UPDATE) != RESET)
	{
		interruptsource = 0x01;
	}
	else
		{
			interruptsource = 0x02;
		}
	timercount = __HAL_TIM_GET_COUNTER(&htim6);
	aftertimercount++;
  /* USER CODE END USART1_IRQn 0 */
  //HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART1_IRQn 1 */
	
  /* USER CODE END USART1_IRQn 1 */
}


/**
  * @brief This function handles TIM6 global interrupt and DAC1/DAC2 underrun error interrupts.
  */
void TIM6_DAC_IRQHandler(void)
{
	
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */
	
		if(__HAL_TIM_GET_FLAG(&htim6,TIM_IT_UPDATE) != RESET)
	{
		interruptflag = 0x01;
		
	}
	else
		{
			interruptflag = 0x02;
		}
	
		if(__HAL_TIM_GET_FLAG(&htim6,TIM_IT_UPDATE) != RESET)
		{
			thandler ++;
			HAL_TIM_Base_Stop_IT(&htim6);	 //STOP THE 1.5CHAR TIMER
			TIM6->CNT=0U;		    //CLEAR COUNTER
			varcheck = 1;	 //clear the Indexer and start over
			__HAL_TIM_CLEAR_IT(&htim6, TIM_IT_UPDATE)	;		//CLEARING 1.5CHAR TIMER INTERRUPT (IF ANY)
	}
		
  /* USER CODE END TIM6_DAC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
  * @brief This function handles TIM7 global interrupt.
  */
void TIM7_IRQHandler(void)
{
  /* USER CODE BEGIN TIM7_IRQn 0 */
	t7handler++;
	if(__HAL_TIM_GET_FLAG(&htim7,TIM_IT_UPDATE) != RESET)
		{
			thandler ++;
			HAL_TIM_Base_Stop_IT(&htim7);	 //STOP THE 1.5CHAR TIMER
			TIM7->CNT=0U;		    //CLEAR COUNTER
			varcheckt35 = 1;	 //clear the Indexer and start over
			__HAL_TIM_CLEAR_IT(&htim7, TIM_IT_UPDATE)	;		//CLEARING 1.5CHAR TIMER INTERRUPT (IF ANY)
	}
	
  /* USER CODE END TIM7_IRQn 0 */
  HAL_TIM_IRQHandler(&htim7);
  /* USER CODE BEGIN TIM7_IRQn 1 */

  /* USER CODE END TIM7_IRQn 1 */
}

uint8_t T15_fcheck (void)
{
	if(varcheck != 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t T35_fcheck (void)
{
	if(varcheckt35 != 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}




void USARTx_DMA_TX_IRQHandler(void)
{
  vcom_DMA_TX_IRQHandler();
}


void RTC_IRQHandler(void)
{
  HW_RTC_IrqHandler();
}

void EXTI0_1_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}

void EXTI2_3_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
}


void EXTI4_15_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
