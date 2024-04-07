#include "bsp.h"
#include "serial.h"
#include "clock.h"
#include "analogs.h"
#include "display.h"

#define WINDOW_VALUE_WWDG       127u        /*!< Watchdog window value */
#define COUNTER_VALUE_WWDG      127u        /*!< Watchdog counter value */
#define LEDS                    0xFFU       /*!< LEDs on port C */
#define SAFE_STATE              1u          /*!< definition to infinite while loop */

/** @brief  struct to handle the WWDG*/
WWDG_HandleTypeDef h_watchdog;

void Hearbeat_InitTask( void );

void Watchdog_InitTask( void );

void CasioCAN_InitRoutine( void );

void safe_state( const char *file, uint32_t line, uint8_t error );


/* cppcheck-suppress unknownMacro ; FUNC macro is defined in tpl source files */
FUNC(int, OS_APPL_CODE) main(void) {

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

    //__HAL_RCC_WWDG_CLK_ENABLE( );

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

    TerminateTask( );
}

/**
 * @brief WWDG EWI callback.
 * 
 * When the watchdog wasn't refreshed this callback send to the safe state.
 * 
 * @param hwwdg pointer to the WWDG handle struct.
*/
void HAL_WWDG_EarlyWakeupCallback( WWDG_HandleTypeDef *hwwdg )
{
    HAL_WWDG_Refresh( hwwdg );
    assert_error( 0u, WWDG_RESET_ERROR );   /* Send to the safe state */
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


/**
 * @brief   Safe state function.
 * 
 * Function where the used modules are disabled, output the corresponding error code using,
 * the PORTC LEDs and enter on an infinite loop.
 * 
 * @param   file String to indicate in which file is the error.
 * @param   line Line where the error its detected.
 * @param   error Error code. 
*/
void safe_state( const char *file, uint32_t line, uint8_t error )
{
    __disable_irq();        /* Disable interrupts */

    (void) file;
    (void) line;

    GPIO_InitTypeDef GPIO_Init;

    __HAL_RCC_GPIOC_CLK_ENABLE( );

    GPIO_Init.Mode      = GPIO_MODE_OUTPUT_PP;
    GPIO_Init.Pull      = GPIO_NOPULL;
    GPIO_Init.Speed     = GPIO_SPEED_FREQ_LOW;
    GPIO_Init.Pin       = LEDS;

    HAL_GPIO_Init( GPIOC, &GPIO_Init );

    HAL_GPIO_WritePin( GPIOC, error, SET );             /* output error code using LEDs on PORTC */

    HAL_GPIO_WritePin( GPIOA, GPIO_PIN_5, RESET );      /* Heartbeat LED turn off */

    (void) HEL_LCD_Backlight( &LCD_Handler, LCD_OFF );             

    HAL_RTC_DeInit( &h_rtc );                               

    HAL_FDCAN_DeInit( &CANHandler );                       

    HAL_SPI_DeInit( &SPI_Handler );
    
    ShutdownOS( error );

    while ( SAFE_STATE == TRUE )
    { 
        HAL_WWDG_Refresh( &h_watchdog );
    }

}
