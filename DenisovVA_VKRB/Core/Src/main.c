/* main.c */
#include "stm32f0xx_hal.h"
#include "st7735s.h"

// Определение пинов (адаптируйте под вашу схему!)
#define BUTTON_A_PIN    GPIO_PIN_0
#define BUTTON_A_PORT   GPIOA
// Аналогично для B, C, D, Center
#define BUZZER_PIN      GPIO_PIN_1
#define BUZZER_PORT     GPIOA

SPI_HandleTypeDef hspi1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);

int main(void) {
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_SPI1_Init();

  ST7735_Init(&hspi1); // Инициализация дисплея

  while (1) {
    // Опрос кнопок
    if (HAL_GPIO_ReadPin(BUTTON_A_PORT, BUTTON_A_PIN) == GPIO_PIN_RESET) {
      ST7735_DrawString(10, 10, "Button A Pressed", ST7735_WHITE);
    }
    // Аналогично для других кнопок

    if (HAL_GPIO_ReadPin(BUTTON_CENTER_PORT, BUTTON_CENTER_PIN) == GPIO_PIN_RESET) {
      ST7735_DrawString(10, 30, "Center Pressed", ST7735_WHITE);
      HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET);
      HAL_Delay(100);
      HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
    }
  }
}

// Настройка SPI (пример для PA5-SCK, PA7-MOSI)
void MX_SPI1_Init(void) {
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  HAL_SPI_Init(&hspi1);
}

// Настройка GPIO
void MX_GPIO_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // Кнопки (с подтяжкой к питанию)
  GPIO_InitStruct.Pin = BUTTON_A_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BUTTON_A_PORT, &GPIO_InitStruct);

  // Динамик
  GPIO_InitStruct.Pin = BUZZER_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);
}
