/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
typedef enum
{
  Lock=0,
  Reset,
  Timeout,
  Enrollment,
  Menu,
}StateType;
#define printf_debug            1
#if printf_debug
    #define DEBUG_PRINT(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...)
#endif
#define sector_name             11
#define sector_base_address     0x080E0000
#define BrandNew_address        0
#define Nusers_address          1
#define WrongPassword_address   2
#define GlobalSalt_address      3
#define MemDatastartpoint       11
#define TimeoutValue            120 //in second
//#include "usbd_cdc_if.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "printf_redirect.h"
#include "MY_FLASH.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"
//#include "bitmap.h"
#include "cmox_crypto.h"
#include "Button.h"
#include "Crypto.h"
#include "RNG.h"
#include "Menu.h"
#include "Timer.h"

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
#define UP_Pin GPIO_PIN_4
#define UP_GPIO_Port GPIOC
#define DOWN_Pin GPIO_PIN_5
#define DOWN_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
