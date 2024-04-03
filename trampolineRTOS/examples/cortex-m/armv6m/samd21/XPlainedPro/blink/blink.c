#include "tpl_os.h"
//the READY tasks state definition conflicts with registers definition (in sam.h)
#undef READY
#include "sam.h"

#define APP_Task_blink_START_SEC_CODE
#include "tpl_memmap.h"

typedef struct 
{
    volatile unsigned long CR;
    volatile unsigned long ICSCR;
    volatile unsigned long CFGR;
    volatile unsigned long PLLCFGR;
    volatile unsigned long RESERVED;
    volatile unsigned long CRRCR;
    volatile unsigned long CIER;
    volatile unsigned long CIFR;
    volatile unsigned long CICR;
    volatile unsigned long IOPRSTR;
    volatile unsigned long AHBRSTR;
    volatile unsigned long APBRSTR1;
    volatile unsigned long APBRSTR2;
    volatile unsigned long IOPENR;
    volatile unsigned long AHBENR;
    volatile unsigned long APBENR1;
    volatile unsigned long APBENR2;
    volatile unsigned long IOPSMENR;
    volatile unsigned long AHBSMENR;
    volatile unsigned long APBSMENR1;
    volatile unsigned long APBSMENR2;
    volatile unsigned long CCIPR;
    volatile unsigned long CCIPR2;
    volatile unsigned long BDCR;
    volatile unsigned long CSR;
}RCC_TypeDef;

typedef struct 
{
    volatile unsigned long MODER;
    volatile unsigned long OTYPER;
    volatile unsigned long OSPEEDR;
    volatile unsigned long PUPDR;
    volatile unsigned long IDR;
    volatile unsigned long ODR;
    volatile unsigned long BSRR;
    volatile unsigned long LCKR;
    volatile unsigned long AFRL;
    volatile unsigned long AFRH;
    volatile unsigned long BRR;
}GPIO_TypeDef;

#define RCC         ((RCC_TypeDef*)0x40021000)

#define GPIOF       ((GPIO_TypeDef*)0x50001400)
#define GPIOE       ((GPIO_TypeDef*)0x50001000)
#define GPIOD       ((GPIO_TypeDef*)0x50000C00)
#define GPIOC       ((GPIO_TypeDef*)0x50000800)
#define GPIOB       ((GPIO_TypeDef*)0x50000400)
#define GPIOA       ((GPIO_TypeDef*)0x50000000)


FUNC(int, OS_APPL_CODE) main(void)
{
  /* Enable GPIOA clock */
    RCC->IOPENR |= 0x01;
    
    /* Set pin 5 from port A as output */
    GPIOA->MODER &= ~( 2 << (5 << 1) );

  StartOS(OSDEFAULTAPPMODE);
  return 0;
}

TASK(blink)
{
  /* Toggle pin 5 where the led is conected  */
        GPIOA->ODR ^= (1 << 5);

  TerminateTask();
}
#define APP_Task_blink_STOP_SEC_CODE
#include "tpl_memmap.h"

