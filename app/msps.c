#include "bsp.h"

void HAL_MspInit( void )
{
    __HAL_RCC_GPIOC_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE( );
    
    HAL_StatusTypeDef Status = HAL_ERROR;

    RCC_OscInitTypeDef        RCC_OscInitStruct = {0};
    RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct = {0};

    RCC_ClkInitTypeDef  RCC_ClkInitStruct       = {0};

    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();
    
    /*Enable backup domain*/
    HAL_PWREx_ControlVoltageScaling( PWR_REGULATOR_VOLTAGE_SCALE1 );

    HAL_PWR_EnableBkUpAccess();
    __HAL_RCC_LSEDRIVE_CONFIG( RCC_LSEDRIVE_LOW );

    /*reset previous RTC source clock*/
    PeriphClkInitStruct.PeriphClockSelection    = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection       = RCC_RTCCLKSOURCE_NONE;

    HAL_RCCEx_PeriphCLKConfig( &PeriphClkInitStruct );
    

    /** 
     * Init the LSE oscillator and PLL
     * The PLL is configured with the HSI, M = 1 and N = 8 
     * fVCO = fPLLIN x ( N / M ) = 16MHz x (8 / 1) = 128MHz
     * fPLLP = fVCO / P = 128MHz / 2 = 64MHz
     * fPLLQ = fVCO / Q = 128MHz / 2 = 64MHz
     * fPLLR = fVCO / R = 128MHz / 2 = 64MHz
    */
    RCC_OscInitStruct.OscillatorType        = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState              = RCC_HSI_ON;
    RCC_OscInitStruct.HSIDiv                = RCC_HSI_DIV1;
    RCC_OscInitStruct.HSICalibrationValue   = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState          = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource         = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM              = RCC_PLLM_DIV1;
    RCC_OscInitStruct.PLL.PLLN              = 8;
    RCC_OscInitStruct.PLL.PLLP              = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ              = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR              = RCC_PLLR_DIV2;
    
    RCC_OscInitStruct.LSEState              = RCC_LSE_ON;    /*enable LSE*/
    RCC_OscInitStruct.LSIState              = RCC_LSI_OFF;   /*disable LSI*/
    
    HAL_RCC_OscConfig( &RCC_OscInitStruct ); 

    /*Set LSE as source clock for the RTC*/
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    
    HAL_RCCEx_PeriphCLKConfig( &PeriphClkInitStruct );
    
    __HAL_RCC_RTC_ENABLE();         /*Enable the clock for the RTC */
    __HAL_RCC_RTCAPB_CLK_ENABLE();

    /* Initializes the CPU, AHB and APB buses clocks */
    RCC_ClkInitStruct.ClockType         = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1;        /* HCLK, SYSCLK and PCLK1*/
    RCC_ClkInitStruct.SYSCLKSource      = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider     = RCC_SYSCLK_DIV1;          /* AHB - 64 MHz */
    RCC_ClkInitStruct.APB1CLKDivider    = RCC_HCLK_DIV2;            /* APB - 32 MHz */
    
    HAL_RCC_ClockConfig( &RCC_ClkInitStruct, FLASH_LATENCY_2 );
    
}

void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef *hfdcan)
{
    (void) hfdcan;
    GPIO_InitTypeDef GpioCanStruct;

    __HAL_RCC_FDCAN_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    
    GpioCanStruct.Mode      = GPIO_MODE_AF_PP;
    GpioCanStruct.Alternate = GPIO_AF3_FDCAN1;
    GpioCanStruct.Pin       = GPIO_PIN_0 | GPIO_PIN_1;
    GpioCanStruct.Pull      = GPIO_NOPULL;
    GpioCanStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init( GPIOD, &GpioCanStruct );

    HAL_NVIC_SetPriority(TIM16_FDCAN_IT0_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(TIM16_FDCAN_IT0_IRQn);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    (void) htim;
    
    __HAL_RCC_GPIOC_CLK_ENABLE( );
    __HAL_RCC_GPIOB_CLK_ENABLE( );
    __HAL_RCC_TIM14_CLK_ENABLE( );
    __HAL_RCC_TIM3_CLK_ENABLE( );

    GPIO_InitTypeDef GPIO_Buzzer    = {0};
    GPIO_InitTypeDef GPIO_Backlight = {0};

    /* Configuration PWM chanel C12 (buzzer) */
    GPIO_Buzzer.Mode      = GPIO_MODE_AF_PP;
    GPIO_Buzzer.Pull      = GPIO_PULLUP;
    GPIO_Buzzer.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_Buzzer.Pin       = GPIO_PIN_12;
    GPIO_Buzzer.Alternate = GPIO_AF2_TIM14;

    HAL_GPIO_Init( GPIOC, &GPIO_Buzzer );

    /* Configuration PWM chanel B4 (backlight) */
    GPIO_Backlight.Mode      = GPIO_MODE_AF_PP;
    GPIO_Backlight.Pull      = GPIO_PULLUP;
    GPIO_Backlight.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_Backlight.Pin       = GPIO_PIN_4;
    GPIO_Backlight.Alternate = GPIO_AF1_TIM3;

    HAL_GPIO_Init( GPIOB, &GPIO_Backlight );
}

void HAL_SPI_MspInit( SPI_HandleTypeDef *hspi )
{
    (void) hspi;

    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_SPI1_CLK_ENABLE( );
    __HAL_RCC_GPIOD_CLK_ENABLE( );

    GPIO_InitStruct.Mode        = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull        = GPIO_PULLUP;
    GPIO_InitStruct.Speed       = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate   = GPIO_AF1_SPI1;                        /*Alternate function SPI1*/
    GPIO_InitStruct.Pin         = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_8; /*Pins for CLK, MISO and MOSI*/
    
    HAL_GPIO_Init( GPIOD, &GPIO_InitStruct );
}

void HEL_LCD_MspInit( LCD_HandleTypeDef *hlcd )
{
    (void) hlcd;

    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_GPIOB_CLK_ENABLE( );
    __HAL_RCC_GPIOD_CLK_ENABLE( );

    GPIO_InitStruct.Mode    = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull    = GPIO_PULLUP;
    GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Pin     = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4; /*Rst | Cs | Rs*/

    HAL_GPIO_Init( GPIOD, &GPIO_InitStruct );
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    (void) htim;
    __HAL_RCC_TIM2_CLK_ENABLE( );
    __HAL_RCC_DMA1_CLK_ENABLE( );
}

void HAL_ADC_MspInit( ADC_HandleTypeDef* hadc )
{
    (void) hadc;

    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_ADC_CLK_ENABLE( );
    __GPIOA_CLK_ENABLE( );

    GPIO_InitStruct.Pin     = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode    = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull    = GPIO_NOPULL;
    HAL_GPIO_Init( GPIOA, &GPIO_InitStruct );
}