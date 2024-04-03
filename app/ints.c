#include "bsp.h"

void isr_CAN_function( void )
{
    HAL_FDCAN_IRQHandler( &CANHandler );
}