
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f0xx_hal.h"

// === Определения пинов TFT-дисплея ===
#define TFT_CS_Pin         GPIO_PIN_0
#define TFT_CS_GPIO_Port   GPIOA
#define TFT_DC_Pin         GPIO_PIN_1
#define TFT_DC_GPIO_Port   GPIOA
#define TFT_RST_Pin        GPIO_PIN_2
#define TFT_RST_GPIO_Port  GPIOA

// === Определения пинов джойстика ===
#define JOY_UP_Pin         GPIO_PIN_3
#define JOY_UP_GPIO_Port   GPIOA
#define JOY_DOWN_Pin       GPIO_PIN_4
#define JOY_DOWN_GPIO_Port GPIOA
#define JOY_LEFT_Pin       GPIO_PIN_5
#define JOY_LEFT_GPIO_Port GPIOA
#define JOY_RIGHT_Pin      GPIO_PIN_6
#define JOY_RIGHT_GPIO_Port GPIOA
#define JOY_CENTER_Pin     GPIO_PIN_7
#define JOY_CENTER_GPIO_Port GPIOA

// === Пин бипера ===
#define BUZZER_Pin         GPIO_PIN_8
#define BUZZER_GPIO_Port   GPIOA

void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
