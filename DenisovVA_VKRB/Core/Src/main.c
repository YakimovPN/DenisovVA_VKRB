#include "main.h"
#include "st7735s.h"

SPI_HandleTypeDef hspi1;
TIM_HandleTypeDef htim1;

// Кнопки (соответствие схеме Э3)
#define BUTTON_A_PIN      GPIO_PIN_0
#define BUTTON_A_PORT     GPIOA
#define BUTTON_B_PIN      GPIO_PIN_1
#define BUTTON_B_PORT     GPIOA
#define BUTTON_C_PIN      GPIO_PIN_2
#define BUTTON_C_PORT     GPIOA
#define BUTTON_D_PIN      GPIO_PIN_3
#define BUTTON_D_PORT     GPIOA
#define BUTTON_CENTER_PIN GPIO_PIN_15
#define BUTTON_CENTER_PORT GPIOA

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM1_Init(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_SPI1_Init();
    MX_TIM1_Init();
    ST7735_Init(&hspi1);

    while (1) {
        // Обработка кнопки A
        if (HAL_GPIO_ReadPin(BUTTON_A_PORT, BUTTON_A_PIN) == GPIO_PIN_RESET) {
            HAL_Delay(50);
            if (HAL_GPIO_ReadPin(BUTTON_A_PORT, BUTTON_A_PIN) == GPIO_PIN_RESET) {
                ST7735_DrawString(10, 10, "Button A", ST7735_WHITE);
            }
        }
        // Аналогично для B, C, D...

        // Обработка Center с динамиком
        if (HAL_GPIO_ReadPin(BUTTON_CENTER_PORT, BUTTON_CENTER_PIN) == GPIO_PIN_RESET) {
            HAL_Delay(50);
            if (HAL_GPIO_ReadPin(BUTTON_CENTER_PORT, BUTTON_CENTER_PIN) == GPIO_PIN_RESET) {
                ST7735_DrawString(10, 50, "Center", ST7735_RED);
                HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
                HAL_Delay(200);
                HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
            }
        }
    }
}

// Остальные функции (MX_GPIO_Init, MX_SPI1_Init) сгенерированы CubeMX
