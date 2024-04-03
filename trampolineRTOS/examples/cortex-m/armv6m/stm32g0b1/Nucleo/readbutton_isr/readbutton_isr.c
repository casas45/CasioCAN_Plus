#include "tpl_os.h"
#include "pinAccess.h"

#include "stm32g0xx_hal_conf.h"

#define APP_Task_read_button_START_SEC_CODE
#include "tpl_memmap.h"
FUNC(int, OS_APPL_CODE) main(void)
{

    pinMode(GPIOA,5,OUTPUT); //led

    pinMode(GPIOC,0,OUTPUT); //led

    //pinMode(GPIOB,15,INPUT); //Button

    GPIO_InitTypeDef GPIO_InitStruct;

    //__HAL_RCC_GPIOB_CLK_ENABLE( );

    /*SW1 configuration Interrupt mode*/
    GPIO_InitStruct.Mode  = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Pin   = GPIO_PIN_3;
    HAL_GPIO_Init( GPIOA, &GPIO_InitStruct );

    // HAL_NVIC_SetPriority( EXTI4_15_IRQn, 3, 0 );
    // HAL_NVIC_EnableIRQ( EXTI4_15_IRQn );

    digitalToggle(GPIOC, 0);
    
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}

TASK(read_button)
{
    static int a = 0;
    if (a == 0) {
        SetRelAlarm(blink_alarm, 100, 100);
        a = 1;
    }
    else {
        CancelAlarm(blink_alarm);
        a = 0;
    }
    TerminateTask();
}
#define APP_Task_read_button_STOP_SEC_CODE
#include "tpl_memmap.h"

#define APP_Task_blink_START_SEC_CODE
#include "tpl_memmap.h"
TASK(blink)
{
    digitalToggle(GPIOC, 0);
    TerminateTask();
}
#define APP_Task_blink_STOP_SEC_CODE
#include "tpl_memmap.h"

#define APP_ISR_isr_button_START_SEC_CODE
#include "tpl_memmap.h"
ISR(isr_button)
{
    ActivateTask(read_button);
}
#define APP_ISR_isr_button_STOP_SEC_CODE
#include "tpl_memmap.h"
