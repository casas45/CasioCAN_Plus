#include "pinAccess.h"
#include "tpl_os.h"
#include "stm32g0xx.h"
#include "stm32g0xx_hal_conf.h"

#define APP_Task_blink_START_SEC_CODE
#include "tpl_memmap.h"



// init PB.3 as output (LED 1 on pin 13).
void initUserLed() {
	pinMode(GPIOA,5,OUTPUT);

  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_GPIOC_CLK_ENABLE( );

  /* LED's init*/
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Pin   = 0xFF;
  
  HAL_GPIO_Init( GPIOC, &GPIO_InitStruct );
  
}

FUNC(int, OS_APPL_CODE) main(void) {
  initUserLed();
  StartOS(OSDEFAULTAPPMODE);
  return 0;
}

TASK(blink) {
  digitalToggle(GPIOA, 5);

  HAL_GPIO_TogglePin( GPIOC, 0xFF );
  
  TerminateTask();
}
#define APP_Task_blink_STOP_SEC_CODE
#include "tpl_memmap.h"
