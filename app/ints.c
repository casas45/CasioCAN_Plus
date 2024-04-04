#include "bsp.h"

void isr_CAN_function( void )
{
    HAL_FDCAN_IRQHandler( &CANHandler );
}

void isr_RTC_function( void )
{
    HAL_RTC_AlarmIRQHandler( &h_rtc );
}

ISR( isr_button )
{
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_15 );
}