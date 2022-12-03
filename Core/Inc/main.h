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
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "cmsis_os.h"
#include "string.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define HALL_W_Pin GPIO_PIN_0
#define HALL_W_GPIO_Port GPIOA
#define HALL_V_Pin GPIO_PIN_1
#define HALL_V_GPIO_Port GPIOA
#define HALL_U_Pin GPIO_PIN_2
#define HALL_U_GPIO_Port GPIOA
#define KEY1_Pin GPIO_PIN_4
#define KEY1_GPIO_Port GPIOA
#define IA_Pin GPIO_PIN_5
#define IA_GPIO_Port GPIOA
#define IB_Pin GPIO_PIN_6
#define IB_GPIO_Port GPIOA
#define Accele_Pin GPIO_PIN_7
#define Accele_GPIO_Port GPIOA
#define FLT_Pin GPIO_PIN_4
#define FLT_GPIO_Port GPIOC
#define Voltage_Pin GPIO_PIN_5
#define Voltage_GPIO_Port GPIOC
#define IBUS_Pin GPIO_PIN_0
#define IBUS_GPIO_Port GPIOB
#define IC_Pin GPIO_PIN_1
#define IC_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_10
#define KEY2_GPIO_Port GPIOB
#define KEY2_EXTI_IRQn EXTI15_10_IRQn
#define KEY3_Pin GPIO_PIN_11
#define KEY3_GPIO_Port GPIOB
#define KEY3_EXTI_IRQn EXTI15_10_IRQn
#define led2_Pin GPIO_PIN_12
#define led2_GPIO_Port GPIOB
#define PWM_UL_Pin GPIO_PIN_13
#define PWM_UL_GPIO_Port GPIOB
#define PWM_VL_Pin GPIO_PIN_14
#define PWM_VL_GPIO_Port GPIOB
#define PWM_WL_Pin GPIO_PIN_15
#define PWM_WL_GPIO_Port GPIOB
#define led1_Pin GPIO_PIN_8
#define led1_GPIO_Port GPIOC
#define led0_Pin GPIO_PIN_9
#define led0_GPIO_Port GPIOC
#define PWM_UH_Pin GPIO_PIN_8
#define PWM_UH_GPIO_Port GPIOA
#define PWM_VH_Pin GPIO_PIN_9
#define PWM_VH_GPIO_Port GPIOA
#define PWM_WH_Pin GPIO_PIN_10
#define PWM_WH_GPIO_Port GPIOA
#define led3_Pin GPIO_PIN_12
#define led3_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
