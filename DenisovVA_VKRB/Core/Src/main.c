/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * Внимание! Этот код предполагает, что:
  * 1. Дисплей ST7735S подключен через SPI1 (PA5-SCK, PA7-MOSI).
  * 2. Кнопки A,B,C,D,Center подключены к PA0, PA1, PA2, PA3, PA15.
  * 3. Динамик HCM1201X подключен к PA8 (TIM1_CH1).
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "st7735s.h"
#include "font_5x7.h"

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
TIM_HandleTypeDef htim1;

/* Private defines -----------------------------------------------------------*/
// Кнопки
#define BUTTON_A_PIN        GPIO_PIN_0
#define BUTTON_A_PORT       GPIOA
#define BUTTON_B_PIN        GPIO_PIN_1
#define BUTTON_B_PORT       GPIOA
#define BUTTON_C_PIN        GPIO_PIN_2
#define BUTTON_C_PORT       GPIOA
#define BUTTON_D_PIN        GPIO_PIN_3
#define BUTTON_D_PORT       GPIOA
#define BUTTON_CENTER_PIN   GPIO_PIN_15
#define BUTTON_CENTER_PORT  GPIOA

// Динамик
#define BUZZER_PIN          GPIO_PIN_8
#define BUZZER_PORT         GPIOA
#define BUZZER_TIM          TIM1
#define BUZZER_TIM_CHANNEL  TIM_CHANNEL_1

// Дисплей
#define DISPLAY_CS_PIN      GPIO_PIN_4
#define DISPLAY_CS_PORT     GPIOA
#define DISPLAY_DC_PIN      GPIO_PIN_6
#define DISPLAY_DC_PORT     GPIOA
#define DISPLAY_RST_PIN     GPIO_PIN_7
#define DISPLAY_RST_PORT    GPIOA

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM1_Init(void);
void Buzzer_Beep(uint16_t duration_ms);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();

  // Инициализация дисплея
  ST7735_Init(&hspi1);
  ST7735_FillScreen(ST7735_BLACK);

  while (1) {
    // Обработка кнопки A
    if (HAL_GPIO_ReadPin(BUTTON_A_PORT, BUTTON_A_PIN) == GPIO_PIN_RESET) {
      HAL_Delay(50);
      if (HAL_GPIO_ReadPin(BUTTON_A_PORT, BUTTON_A_PIN) == GPIO_PIN_RESET) {
        ST7735_FillScreen(ST7735_BLACK);
        ST7735_DrawString(10, 10, "Button A", ST7735_WHITE);
      }
    }

    // Обработка кнопки B
    if (HAL_GPIO_ReadPin(BUTTON_B_PORT, BUTTON_B_PIN) == GPIO_PIN_RESET) {
      HAL_Delay(50);
      if (HAL_GPIO_ReadPin(BUTTON_B_PORT, BUTTON_B_PIN) == GPIO_PIN_RESET) {
        ST7735_FillScreen(ST7735_BLACK);
        ST7735_DrawString(10, 30, "Button B", ST7735_WHITE);
      }
    }

    // Обработка кнопки Center
    if (HAL_GPIO_ReadPin(BUTTON_CENTER_PORT, BUTTON_CENTER_PIN) == GPIO_PIN_RESET) {
      HAL_Delay(50);
      if (HAL_GPIO_ReadPin(BUTTON_CENTER_PORT, BUTTON_CENTER_PIN) == GPIO_PIN_RESET) {
        ST7735_FillScreen(ST7735_BLACK);
        ST7735_DrawString(10, 50, "CENTER", ST7735_RED);
        Buzzer_Beep(200); // Звук 200 мс
      }
    }
    HAL_Delay(10);
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  // Настройка на 48 МГц через PLL
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);
}

/**
  * @brief GPIO Initialization
  * @retval None
  */
static void MX_GPIO_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // Кнопки
  GPIO_InitStruct.Pin = BUTTON_A_PIN | BUTTON_B_PIN | BUTTON_C_PIN
                      | BUTTON_D_PIN | BUTTON_CENTER_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // Динамик (ШИМ)
  GPIO_InitStruct.Pin = BUZZER_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
  HAL_GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);

  // Дисплей (CS, DC, RST)
  GPIO_InitStruct.Pin = DISPLAY_CS_PIN | DISPLAY_DC_PIN | DISPLAY_RST_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // Сброс дисплея
  HAL_GPIO_WritePin(DISPLAY_RST_PORT, DISPLAY_RST_PIN, GPIO_PIN_SET);
}

/**
  * @brief SPI1 Initialization
  * @retval None
  */
static void MX_SPI1_Init(void) {
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  HAL_SPI_Init(&hspi1);
}

/**
  * @brief TIM1 Initialization (ШИМ для динамика)
  * @retval None
  */
static void MX_TIM1_Init(void) {
  TIM_OC_InitTypeDef sConfigOC = {0};

  htim1.Instance = BUZZER_TIM;
  htim1.Init.Prescaler = 47;         // 48 МГц / 48 = 1 МГц
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 999;           // Частота ШИМ = 1 кГц
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_PWM_Init(&htim1);

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 500;             // Скважность 50%
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, BUZZER_TIM_CHANNEL);
}

/**
  * @brief Управление динамиком
  * @param duration_ms Длительность звука в мс
  */
void Buzzer_Beep(uint16_t duration_ms) {
  HAL_TIM_PWM_Start(&htim1, BUZZER_TIM_CHANNEL);
  HAL_Delay(duration_ms);
  HAL_TIM_PWM_Stop(&htim1, BUZZER_TIM_CHANNEL);
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {
  while (1) {}
}
#endif
