#ifndef __STM32F0xx_HAL_CONF_H
#define __STM32F0xx_HAL_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* ########################## Module Selection ############################## */
#define HAL_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_SPI_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_TIM_MODULE_ENABLED
#define HAL_EXTI_MODULE_ENABLED

/* ########################## Oscillator Values adaptation ####################*/
#define HSE_VALUE    ((uint32_t)8000000U)
#define HSE_STARTUP_TIMEOUT    ((uint32_t)100U)
#define HSI_VALUE    ((uint32_t)8000000U)
#define HSI_STARTUP_TIMEOUT   ((uint32_t)5000U)
#define LSI_VALUE  ((uint32_t)40000U)
#define LSE_VALUE  ((uint32_t)32768U)
#define LSE_STARTUP_TIMEOUT ((uint32_t)5000U)
#define EXTERNAL_CLOCK_VALUE  ((uint32_t)12288000U)

/* ########################### System Configuration ######################### */
#define  VDD_VALUE                    ((uint32_t)3300U)
#define  TICK_INT_PRIORITY            ((uint32_t)0U)
#define  USE_RTOS                     0U
#define  PREFETCH_ENABLE              1U
#define  INSTRUCTION_CACHE_ENABLE     0U
#define  DATA_CACHE_ENABLE            0U

/* ########################### Assert Selection ############################## */
/* #define USE_FULL_ASSERT    1U */

/* ################## Register callback feature configuration ############### */
/* #define USE_HAL_SPI_REGISTER_CALLBACKS        0U */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal_rcc.h"
#include "stm32f0xx_hal_gpio.h"
#include "stm32f0xx_hal_spi.h"
#include "stm32f0xx_hal_cortex.h"
#include "stm32f0xx_hal_pwr.h"
#include "stm32f0xx_hal_tim.h"
#include "stm32f0xx_hal_exti.h"
#include "stm32f0xx_hal_flash.h"

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0xx_HAL_CONF_H */
