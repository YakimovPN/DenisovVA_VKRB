#include "st7735s.h"
#include "font_5x7.h"  // Подключите файл с шрифтом (см. ниже)

static SPI_HandleTypeDef *hspi_st7735;

void ST7735_SendCommand(uint8_t cmd) {
    HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ST7735_DC_PORT, ST7735_DC_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(hspi_st7735, &cmd, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_SET);
}

void ST7735_SendData(uint8_t data) {
    HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ST7735_DC_PORT, ST7735_DC_PIN, GPIO_PIN_SET);
    HAL_SPI_Transmit(hspi_st7735, &data, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_SET);
}

void ST7735_Init(SPI_HandleTypeDef *hspi) {
    hspi_st7735 = hspi;

    // Сброс дисплея
    HAL_GPIO_WritePin(ST7735_RST_PORT, ST7735_RST_PIN, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(ST7735_RST_PORT, ST7735_RST_PIN, GPIO_PIN_SET);
    HAL_Delay(100);

    // Инициализация для ST7735S 128x128
    ST7735_SendCommand(0x11); // Sleep out
    HAL_Delay(120);
    ST7735_SendCommand(0x3A); // RGB565
    ST7735_SendData(0x05);
    ST7735_SendCommand(0x29); // Display on
}

void ST7735_DrawString(uint8_t x, uint8_t y, const char *str, uint16_t color) {
    for (uint8_t i = 0; str[i] != 0; i++) {
        // Рисуем каждый символ шрифта 5x7
        for (uint8_t col = 0; col < 5; col++) {
            uint8_t bits = font_5x7[str[i] - ' '][col];
            for (uint8_t row = 0; row < 7; row++) {
                if (bits & (1 << row)) {
                    // Установите пиксель в позиции (x + i*6 + col, y + row)
                }
            }
        }
    }
}
