#include "bsp.h"

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