#include "st7735.h"
#include "fonts.h"
#include <string.h>

extern SPI_HandleTypeDef hspi1;

#define DC_LOW()  HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_RESET)
#define DC_HIGH() HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_SET)
#define CS_LOW()  HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET)
#define CS_HIGH() HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_SET)
#define RST_LOW() HAL_GPIO_WritePin(TFT_RST_GPIO_Port, TFT_RST_Pin, GPIO_PIN_RESET)
#define RST_HIGH() HAL_GPIO_WritePin(TFT_RST_GPIO_Port, TFT_RST_Pin, GPIO_PIN_SET)

static void ST7735_SendCommand(uint8_t cmd) {
    DC_LOW();
    CS_LOW();
    HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
    CS_HIGH();
}

static void ST7735_SendData(uint8_t *data, uint16_t size) {
    DC_HIGH();
    CS_LOW();
    HAL_SPI_Transmit(&hspi1, data, size, HAL_MAX_DELAY);
    CS_HIGH();
}

static void ST7735_Reset(void) {
    RST_LOW();
    HAL_Delay(50);
    RST_HIGH();
    HAL_Delay(50);
}

void ST7735_SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
    uint8_t data[4];
    ST7735_SendCommand(0x2A); // Column addr set
    data[0] = 0x00; data[1] = x0;
    data[2] = 0x00; data[3] = x1;
    ST7735_SendData(data, 4);

    ST7735_SendCommand(0x2B); // Row addr set
    data[1] = y0;
    data[3] = y1;
    ST7735_SendData(data, 4);

    ST7735_SendCommand(0x2C); // Write to RAM
}

void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    if ((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
    ST7735_SetAddressWindow(x, y, x, y);
    uint8_t data[] = { color >> 8, color & 0xFF };
    ST7735_SendData(data, 2);
}

void ST7735_FillScreen(uint16_t color) {
    ST7735_SetAddressWindow(0, 0, ST7735_WIDTH - 1, ST7735_HEIGHT - 1);
    uint8_t data[] = { color >> 8, color & 0xFF };
    DC_HIGH();
    CS_LOW();
    for (uint16_t i = 0; i < ST7735_WIDTH * ST7735_HEIGHT; i++) {
        HAL_SPI_Transmit(&hspi1, data, 2, HAL_MAX_DELAY);
    }
    CS_HIGH();
}

void ST7735_Init(void) {
    ST7735_Reset();

    ST7735_SendCommand(0x01); // Software Reset
    HAL_Delay(150);
    ST7735_SendCommand(0x11); // Sleep Out
    HAL_Delay(150);

    ST7735_SendCommand(0x3A); // Interface Pixel Format
    uint8_t data = 0x05; // 16-bit/pixel
    ST7735_SendData(&data, 1);

    ST7735_SendCommand(0x29); // Display ON
    HAL_Delay(100);
}

void ST7735_WriteChar(char ch, uint16_t x, uint16_t y, uint16_t color, uint16_t bgcolor) {
    if ((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT - 16)) return;

    for (uint8_t i = 0; i < 11; i++) {
        uint16_t line = Font11x18[ch - 32][i];
        for (uint8_t j = 0; j < 18; j++) {
            if (line & (1 << j)) {
                ST7735_DrawPixel(x + i, y + j, color);
            } else {
                ST7735_DrawPixel(x + i, y + j, bgcolor);
            }
        }
    }
}

void ST7735_WriteString(const char* str, uint16_t x, uint16_t y, uint16_t color, uint16_t bgcolor) {
    while (*str) {
        ST7735_WriteChar(*str++, x, y, color, bgcolor);
        x += 11;
    }
}
