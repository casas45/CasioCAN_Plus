#include "bsp.h"

void isr_CAN_function( void )
{
    HAL_FDCAN_IRQHandler( &CANHandler );
}

void isr_RTC_function( void )
{
    HAL_RTC_AlarmIRQHandler( &h_rtc );
}

/* cppcheck-suppress misra-c2012-2.7 ; The parameters aren't used in the task */
/* cppcheck-suppress misra-c2012-8.2 ; This macro forms part of tpl source code */
ISR( isr_button )
{
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_15 );
}

void isr_WWDG_function( void )
{
    HAL_WWDG_IRQHandler( &h_watchdog );
}