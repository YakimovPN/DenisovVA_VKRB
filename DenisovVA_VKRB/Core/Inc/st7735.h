#ifndef __ST7735_H__
#define __ST7735_H__

#include "stm32f0xx_hal.h"
#include <stdint.h>

#define ST7735_WIDTH  128
#define ST7735_HEIGHT 128

// Цвета в формате RGB565
#define ST7735_BLACK   0x0000
#define ST7735_BLUE    0x001F
#define ST7735_RED     0xF800
#define ST7735_GREEN   0x07E0
#define ST7735_CYAN    0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW  0xFFE0
#define ST7735_WHITE   0xFFFF

void ST7735_Init(void);
void ST7735_FillScreen(uint16_t color);
void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ST7735_WriteChar(char ch, uint16_t x, uint16_t y, uint16_t color, uint16_t bgcolor);
void ST7735_WriteString(const char* str, uint16_t x, uint16_t y, uint16_t color, uint16_t bgcolor);

#endif
