#include "pinAccess.h"

#ifndef IS_GPIO_ALL_INSTANCE
#define IS_GPIO_ALL_INSTANCE(INSTANCE)  (((INSTANCE) == GPIOA) || \
                                         ((INSTANCE) == GPIOB) || \
                                         ((INSTANCE) == GPIOC) || \
                                         ((INSTANCE) == GPIOD) || \
                                         ((INSTANCE) == GPIOE) || \
                                         ((INSTANCE) == GPIOF))
#endif

void clockForGpio(GPIO_TypeDef *port)
{
	if     (port == GPIOA) RCC->IOPENR |= (1<<0);
	else if(port == GPIOB) RCC->IOPENR |= (1<<1);
	else if(port == GPIOC) RCC->IOPENR |= (1<<2);
	else if(port == GPIOD) RCC->IOPENR |= (1<<3);
	else if(port == GPIOE) RCC->IOPENR |= (1<<4); 
	else if(port == GPIOF) RCC->IOPENR |= (1<<5);
}

int pinMode(GPIO_TypeDef *port, 
            unsigned char numBit,
            mode m)
{
    int mask2Bits; //mask for 2bit fields
    //check arguments
    if(!IS_GPIO_ALL_INSTANCE(port)) return -1;
    if(numBit > 15) return -1;
    //
    clockForGpio(port);
    mask2Bits = (3U << (numBit*2)); 
    switch(m)
    {
        case UNUSED: //MODER = 0, PUPDR = 0
            port->MODER &= ~mask2Bits;
            port->PUPDR &= ~mask2Bits;
            break;
        case OUTPUT: //MODER = 1, PUPDR = 0
            port->MODER &= ~mask2Bits;
            port->MODER |= (1<<(numBit*2));
            port->PUPDR &= ~mask2Bits;
            break;
        case INPUT: //MODER = 0, PUPDR = 0
            port->MODER &= ~mask2Bits;
            port->PUPDR &= ~mask2Bits;
            break;
        case INPUT_PULLUP: //MODER = 0, PUPDR = 1
            port->MODER &= ~mask2Bits;
            port->PUPDR &= ~mask2Bits;
            port->PUPDR |= (1<<(numBit*2));
            break;
        case INPUT_PULLDOWN: //MODER = 0, PUPDR = 3
            port->MODER &= ~mask2Bits;
            port->PUPDR &= ~mask2Bits;
            port->PUPDR |= (1<<((numBit*2)+1));
            break;
        default:
            break;
    }
    return 0;
}

void digitalWrite(GPIO_TypeDef *port, 
                  unsigned char numBit,
                  unsigned int value)
{
    if(!IS_GPIO_ALL_INSTANCE(port)) return;
    if(numBit > 15) return;
    
    if(value) port->BSRR = 1U << numBit;
    else      port->BSRR = 1U << (numBit+16);
}

void digitalToggle(GPIO_TypeDef *port, 
                  unsigned char numBit)
{
    if(!IS_GPIO_ALL_INSTANCE(port)) return;
    if(numBit > 15) return;

    if(port->IDR & (1U << numBit)) //if is set
        port->BSRR = 1U << (numBit+16);    //reset
    else
        port->BSRR = 1U << numBit;        //set
}


unsigned char digitalRead(GPIO_TypeDef *port,
                          unsigned char numBit)
{
    if(!IS_GPIO_ALL_INSTANCE(port)) return 0xFF;
    if(numBit > 15) return 0xFF;
    if(port->IDR & (1U<<numBit)) //if is set
        return 1;
    return 0;
}

unsigned char pinAlt(GPIO_TypeDef *port,
                     uint32_t numBit,
                     uint32_t AFId)
{
    if(!IS_GPIO_ALL_INSTANCE(port)) return 0xFF;
    if(numBit > 15) return 0xFF;
    if(AFId > 15) return 0xFF;
    //clock
    clockForGpio(port);
    //set MODER to 10
    uint32_t mask2Bits = (3U << (numBit*2));
    port->MODER &= ~mask2Bits;
    port->MODER |= (2U<<(numBit*2));
    //set alternate function
    uint32_t shift;
    int AFRReg;
    if(numBit < 8U) //AFRL
    {
        shift = numBit<<2;
        AFRReg = 0;
    } else { //AFRH
        shift = (numBit-8U)<<2;
        AFRReg = 1;
    }
    port->AFR[AFRReg] &= ~(0xfU<<shift);
    port->AFR[AFRReg] |=  (AFId<<shift);
    return 0;
}

unsigned char pinAnalog(GPIO_TypeDef *port, uint32_t numBit)
{
    uint32_t mask2Bits; //mask for 2bit fields
    if(!IS_GPIO_ALL_INSTANCE(port)) return 0xFF;
    if(numBit > 15) return 0xFF;
    //clock
    clockForGpio(port);
    port->MODER |= (3U<<(numBit*2));    //analog config
    mask2Bits = (3U << (numBit*2));
    port->PUPDR &= ~mask2Bits; //remove pull-up/down
    return 0;
}
