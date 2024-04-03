/* Interrupt table vector */
#include "tpl_compiler.h"
#include "tpl_os.h"
#include "tpl_os_interrupt_kernel.h"
#include "tpl_machine.h"

extern FUNC(void, OS_CODE) tpl_primary_irq_handler_EXTI2_3_IRQ(void);
extern FUNC(void, OS_CODE) EXTI2_3_IRQ_ClearFlag(void);

extern FUNC(void, OS_CODE) tpl_primary_irq_handler_SysTick(void);
extern FUNC(void, OS_CODE) tpl_reset_handler(void);
extern FUNC(void, OS_CODE) NMI_Handler(void);
extern FUNC(void, OS_CODE) HardFault_Handler(void);
extern FUNC(void, OS_CODE) MemManage_Handler(void);
extern FUNC(void, OS_CODE) BusFault_Handler(void);
extern FUNC(void, OS_CODE) UsageFault_Handler(void);
extern FUNC(void, OS_CODE) tpl_sc_handler(void);
extern FUNC(void, OS_CODE) DebugMonitor_Handler(void);
extern FUNC(void, OS_CODE) SysTickHandler(void);
extern FUNC(void, OS_CODE) EXTI2_3_IRQHandler(void);


/* Interrupt table vector */

__attribute__ ((section(".isr_vector"))) CONST(tpl_it_handler, OS_CONST) tpl_it_vectors[48] = {
  (tpl_it_handler)&_estack,
  (tpl_it_handler)tpl_reset_handler,
  (tpl_it_handler)NMI_Handler,
  (tpl_it_handler)HardFault_Handler,
  (tpl_it_handler)MemManage_Handler,
  (tpl_it_handler)BusFault_Handler,
  (tpl_it_handler)UsageFault_Handler,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_sc_handler,
  (tpl_it_handler)DebugMonitor_Handler,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler) tpl_primary_irq_handler_SysTick,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler) tpl_primary_irq_handler_EXTI2_3_IRQ,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it,
  (tpl_it_handler)tpl_null_it
};

