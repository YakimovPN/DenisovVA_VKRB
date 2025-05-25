#ifndef ST7735S_H
#define ST7735S_H

#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_spi.h"

// Параметры дисплея
#define ST7735_CS_PIN    GPIO_PIN_4
#define ST7735_CS_PORT   GPIOA
#define ST7735_DC_PIN    GPIO_PIN_6
#define ST7735_DC_PORT   GPIOA
#define ST7735_RST_PIN   GPIO_PIN_7
#define ST7735_RST_PORT  GPIOA

// Цвета (RGB565)
#define ST7735_BLACK    0x0000
#define ST7735_WHITE    0xFFFF
#define ST7735_RED      0xF800
#define ST7735_GREEN    0x07E0
#define ST7735_BLUE     0x001F

void ST7735_Init(SPI_HandleTypeDef *hspi);
void ST7735_DrawString(uint8_t x, uint8_t y, const char *str, uint16_t color);
void ST7735_FillScreen(uint16_t color);

#endif
