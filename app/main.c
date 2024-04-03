#include "bsp.h"
#include "serial.h"

void Hearbeat_InitTask( void );

void CasioCAN_InitRoutine( void );


FUNC(int, OS_APPL_CODE) main(void) {

    CasioCAN_InitRoutine( );

    StartOS(OSDEFAULTAPPMODE);
    
    return 0;
}


void CasioCAN_InitRoutine( void )
{
    Hearbeat_InitTask( );
    Serial_InitTask( );
}

void Hearbeat_InitTask ( void )
{
    GPIO_InitTypeDef HearbeatPin_Struct;

    __HAL_RCC_GPIOA_CLK_ENABLE();

    HearbeatPin_Struct.Mode     = GPIO_MODE_OUTPUT_PP;
    HearbeatPin_Struct.Pull     = GPIO_NOPULL;
    HearbeatPin_Struct.Speed    = GPIO_SPEED_FREQ_LOW;
    HearbeatPin_Struct.Pin      = GPIO_PIN_5;

    HAL_GPIO_Init( GPIOA, &HearbeatPin_Struct );
}

TASK( Hearbeat_PeriodicTask )
{
    HAL_GPIO_TogglePin( GPIOA, GPIO_PIN_5 );
}