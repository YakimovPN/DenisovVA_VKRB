#include "st7735s.h"
#include "font_5x7.h"
#include <string.h>

static SPI_HandleTypeDef *hspi_st7735;

// Отправка команды на дисплей
void ST7735_SendCommand(uint8_t cmd) {
    HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ST7735_DC_PORT, ST7735_DC_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(hspi_st7735, &cmd, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_SET);
}

// Отправка данных на дисплей
void ST7735_SendData(uint8_t data) {
    HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ST7735_DC_PORT, ST7735_DC_PIN, GPIO_PIN_SET);
    HAL_SPI_Transmit(hspi_st7735, &data, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_SET);
}

// Инициализация дисплея
void ST7735_Init(SPI_HandleTypeDef *hspi) {
    hspi_st7735 = hspi;

    // Сброс дисплея
    HAL_GPIO_WritePin(ST7735_RST_PORT, ST7735_RST_PIN, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(ST7735_RST_PORT, ST7735_RST_PIN, GPIO_PIN_SET);
    HAL_Delay(100);

    // Команды инициализации для ST7735S 128x128
    ST7735_SendCommand(0x11); // Sleep out
    HAL_Delay(120);
    ST7735_SendCommand(0x3A); // RGB565
    ST7735_SendData(0x05);
    ST7735_SendCommand(0x29); // Display on
}

// Заливка экрана цветом
void ST7735_FillScreen(uint16_t color) {
    // Пример реализации (адаптируйте под ваш дисплей)
    // ...
}

// Вывод строки
void ST7735_DrawString(uint8_t x, uint8_t y, const char *str, uint16_t color) {
    for (uint8_t i = 0; str[i] != 0; i++) {
        // Реализация вывода символов из font_5x7.h
        // ...
    }
}
