#include "bsp.h"
#include "serial.h"
#include "clock.h"
#include "analogs.h"
#include "display.h"

#define WINDOW_VALUE_WWDG       127u        /*!< Watchdog window value */
#define COUNTER_VALUE_WWDG      127u        /*!< Watchdog counter value */

/** @brief  struct to handle the WWDG*/
WWDG_HandleTypeDef h_watchdog;

void Hearbeat_InitTask( void );

void CasioCAN_InitRoutine( void );

//extern void initialise_monitor_handles(void);

FUNC(int, OS_APPL_CODE) main(void) {


    //initialise_monitor_handles();

    CasioCAN_InitRoutine( );

    StartOS(OSDEFAULTAPPMODE);
    
    return 0;
}


void CasioCAN_InitRoutine( void )
{
    HAL_Init( );
    
    Hearbeat_InitTask( );
    Serial_InitTask( );
    Clock_InitTask( );
    Analogs_Init( );
    Display_InitTask( );
    Watchdog_InitTask( );
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

void Watchdog_InitTask( void )
{
    HAL_StatusTypeDef Status = HAL_ERROR;

    __HAL_RCC_WWDG_CLK_ENABLE( );

    h_watchdog.Instance         = WWDG;
    h_watchdog.Init.Prescaler   = WWDG_PRESCALER_32;
    h_watchdog.Init.Counter     = COUNTER_VALUE_WWDG;    
    h_watchdog.Init.Window      = WINDOW_VALUE_WWDG;
    h_watchdog.Init.EWIMode     = WWDG_EWI_ENABLE;

    HAL_NVIC_SetPriority( WWDG_IRQn, 2, 0 );
    HAL_NVIC_EnableIRQ( WWDG_IRQn );

    Status = HAL_WWDG_Init( &h_watchdog );
    assert_error( Status == HAL_OK, WWDG_RET_ERROR );
}

TASK( Watchdog_PeriodicTask )
{
    HAL_StatusTypeDef Status = HAL_ERROR;

    Status = HAL_WWDG_Refresh( &h_watchdog );

    assert_error( Status == HAL_OK, WWDG_RET_ERROR );
}

TASK( Hearbeat_PeriodicTask )
{
    HAL_GPIO_TogglePin( GPIOA, GPIO_PIN_5 );

    TerminateTask( );
}


ALARMCALLBACK( TimerAlarmOneSecond )
{
    TimerAlarmOneSecond_Callback( );
}

ALARMCALLBACK( TimerDeactivateAlarm )
{
    TimerDeactivateAlarm_Callback( );
}