//the READY tasks state definition conflicts 
//with registers definition (in stm32g0xx.h)
#ifdef READY
  #undef READY
#endif
#include "stm32g0xx.h"
