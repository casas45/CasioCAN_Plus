/**
 * @file tpl_app_config.c
 *
 * @section desc File description
 *
 * OS data structure generated from application casioCAN_plus
 * Automatically generated by goil on Www Mmm dd hh:mm:ss yyyy
 * from root OIL file CasioCANplus.oil
 *
 * @section copyright Copyright
 *
 * Trampoline OS
 *
 * Trampoline is copyright (c) IRCCyN 2005-2007
 * Trampoline is protected by the French intellectual property law.
 *
 * This software is distributed under the Lesser GNU Public Licence
 *
 * @section infos File informations
 *
 * $Date$
 * $Rev$
 * $Author$
 * $URL$
 */

#include <stdbool.h>
#include <stdint.h>

#include "tpl_app_config.h"

#include "bsp.h"  

#include "tpl_os_internal_types.h"
#include "tpl_machine.h"
#include "tpl_os_interrupt.h"
#include "tpl_os_interrupt_kernel.h"
#include "tpl_os_alarm_kernel.h"
#include "tpl_os_alarm.h"
#include "tpl_os_resource_kernel.h"
#include "tpl_os_resource.h"
#include "tpl_os_event_kernel.h"
#include "tpl_os_event.h"
#include "tpl_os_action.h"
#include "tpl_os_kernel.h"
#include "tpl_os_definitions.h"


#include "tpl_com_notification.h"
#include "tpl_com_mo.h"
#include "tpl_com_internal.h"
#include "tpl_com_internal_com.h"
/*#include "tpl_com_external_com.h"*/
#include "tpl_com_app_copy.h"
#include "tpl_com_filters.h"

/*=============================================================================
 * Application Modes tables for tasks, alarms and schedule tables
 * Application Modes masks are as follow:
 * std = 1
 */

CONST(tpl_application_mode, OS_CONST) std = 0; /* mask = 1 */
CONST(tpl_application_mode, OS_CONST) OSDEFAULTAPPMODE = 0;
CONST(tpl_appmode_mask, OS_CONST) tpl_task_app_mode[TASK_COUNT] = {
  0 /* task Serial_PeriodicTask :  */ ,
  0 /* task Hearbeat_PeriodicTask :  */ 
};

CONST(tpl_appmode_mask, OS_CONST) tpl_alarm_app_mode[ALARM_COUNT] = {
  1 /* alarm HeatbeatAlarm : std */ ,
  1 /* alarm SerialAlarm : std */ 
};

#define API_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Declaration of processes IDs
 */

/* Task Serial_PeriodicTask identifier */
#define Serial_PeriodicTask_id 0
CONST(TaskType, AUTOMATIC) Serial_PeriodicTask = Serial_PeriodicTask_id;

/* Task Hearbeat_PeriodicTask identifier */
#define Hearbeat_PeriodicTask_id 1
CONST(TaskType, AUTOMATIC) Hearbeat_PeriodicTask = Hearbeat_PeriodicTask_id;

/*=============================================================================
 * Declaration of Alarm IDs
 */

/* Alarm HeatbeatAlarm identifier */
#define HeatbeatAlarm_id 0
CONST(AlarmType, AUTOMATIC) HeatbeatAlarm = HeatbeatAlarm_id;

/* Alarm SerialAlarm identifier */
#define SerialAlarm_id 1
CONST(AlarmType, AUTOMATIC) SerialAlarm = SerialAlarm_id;

/*=============================================================================
 * Declaration of receive messages IDs
 */

/* Message serialMsgReceive identifier */
#define serialMsgReceive_id 0
CONST(MessageIdentifier, AUTOMATIC) serialMsgReceive = serialMsgReceive_id;

/*=============================================================================
 * Declaration of send messages IDs
 */

/* Message serialMsgSend identifier */
#define serialMsgSend_id 0
CONST(MessageIdentifier, AUTOMATIC) serialMsgSend = serialMsgSend_id;

#define API_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/**
 * The scheduler resource descriptor.
 * One scheduler resource is defined per core.
 *
 * @see #RES_SCHEDULER
 */

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
VAR(tpl_resource, OS_VAR) res_sched_rez_desc = {
  RES_SCHEDULER_PRIORITY,   /*  ceiling priority                            */
  0,                        /*  owner_prev_priority                         */
  INVALID_PROC_ID,          /*  owner                                       */
#if WITH_OSAPPLICATION == YES
  INVALID_OSAPPLICATION_ID, /*  OS Application id                           */
#endif

  NULL                      /*  next_res                                    */
};
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
CONSTP2VAR(tpl_resource, AUTOMATIC, OS_APPL_DATA)
tpl_resource_table[RESOURCE_COUNT] = {
  &res_sched_rez_desc
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Definition and initialization of Counters related defines and structures
 */
/*-----------------------------------------------------------------------------
 * Counter SystemCounter descriptor
 */

#define API_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_tick, OS_CONST) OSTICKSPERBASE = 1;
CONST(tpl_tick, OS_CONST) OSMAXALLOWEDVALUE = 65535;
CONST(tpl_tick, OS_CONST) OSMINCYCLE = 1;

#define API_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_counter, OS_VAR) SystemCounter_counter_desc = {
  /* ticks per base       */  1,
  /* max allowed value    */  65535,
  /* minimum cycle        */  1,
  /* current tick         */  0,
  /* current date         */  0,
#if WITH_OSAPPLICATION == YES
    /* OS Application id    */  
#endif
    /* first alarm          */  NULL_PTR,
    /* next alarm to raise  */  NULL_PTR
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#include "tpl_os_kernel.h"          /* tpl_schedule */
#include "tpl_os_timeobj_kernel.h"  /* tpl_counter_tick */
#include "tpl_machine_interface.h"  /* tpl_switch_context_from_it */

#define OS_START_SEC_VAR_32BIT
#include "tpl_memmap.h"
volatile VAR(uint32, OS_VAR) tpl_time_counter = 0;
#define OS_STOP_SEC_VAR_32BIT
#include "tpl_memmap.h"

#define OS_START_SEC_CODE
#include "tpl_memmap.h"

FUNC(tpl_bool, OS_CODE) tpl_tick_SysTick(void)
{
  tpl_counter_tick(&SystemCounter_counter_desc);
  tpl_time_counter++;

  if (tpl_kern.need_schedule == TRUE)
  {
    tpl_schedule_from_running();
    LOCAL_SWITCH_CONTEXT()
  }

  return TRUE;
}

#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

/*=============================================================================
 * Descriptor(s) of the idle task(s)
 */
/*-----------------------------------------------------------------------------
 * Task IDLE_TASK descriptor
 */
#define OS_START_SEC_CODE
#include "tpl_memmap.h"
/*
 * Task IDLE_TASK function prototype
 */

FUNC(void, OS_APPL_CODE) idle_function(void);
#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */
/*
 * Task IDLE_TASK stack
 */
#define APP_Task_IDLE_TASK_START_SEC_STACK
#include "tpl_memmap.h"
VAR(tpl_stack_word, OS_APPL_DATA) IDLE_TASK_stack_zone[IDLE_STACK_SIZE/sizeof(tpl_stack_word)];
#define APP_Task_IDLE_TASK_STOP_SEC_STACK
#include "tpl_memmap.h"

#define IDLE_TASK_STACK {IDLE_TASK_stack_zone, IDLE_STACK_SIZE}

/*
 * Task IDLE_TASK context
 */
#define OS_START_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"
VAR(arm_core_context, OS_VAR) IDLE_TASK_int_context;

#define IDLE_TASK_CONTEXT &IDLE_TASK_int_context

#define OS_STOP_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"




/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task IDLE_TASK
 */
CONST(tpl_proc_static, OS_CONST) IDLE_TASK_task_stat_desc = {
  /* context                  */  IDLE_TASK_CONTEXT,
  /* stack                    */  IDLE_TASK_STACK,
  /* entry point (function)   */  idle_function,
  /* internal ressource       */  NULL,
  /* task id                  */  IDLE_TASK_ID,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  0,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES

  /* execution budget */        0,
  /* timeframe        */        0, 
  /* pointer to the timing
     protection descriptor    */ NULL

#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task IDLE_TASK
 */
VAR(tpl_proc, OS_VAR) IDLE_TASK_task_desc = {
  /* resources                      */  NULL,
#if WITH_OSAPPLICATION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_OSAPPLICATION */
  /* activate count                 */  0,
  /* task priority                  */  0,
  /* task state                     */  SUSPENDED
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"


/*=============================================================================
 * Definition and initialization of Task related defines and structures
 */
/*-----------------------------------------------------------------------------
 * Task Serial_PeriodicTask descriptor
 */
#define APP_Task_Serial_PeriodicTask_START_SEC_CODE

#include "tpl_memmap.h"
/*
 * Task Serial_PeriodicTask function prototype
 */

FUNC(void, OS_APPL_CODE) Serial_PeriodicTask_function(void);
#define APP_Task_Serial_PeriodicTask_STOP_SEC_CODE

#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */
/*
 * Task Serial_PeriodicTask stack
 */
#define APP_Task_Serial_PeriodicTask_START_SEC_STACK
#include "tpl_memmap.h"
VAR(tpl_stack_word, OS_APPL_DATA) Serial_PeriodicTask_stack_zone[300/sizeof(tpl_stack_word)];
#define APP_Task_Serial_PeriodicTask_STOP_SEC_STACK
#include "tpl_memmap.h"

#define Serial_PeriodicTask_STACK {Serial_PeriodicTask_stack_zone, 300}

/*
 * Task Serial_PeriodicTask context
 */
#define OS_START_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"
VAR(arm_core_context, OS_VAR) Serial_PeriodicTask_int_context;

#define Serial_PeriodicTask_CONTEXT &Serial_PeriodicTask_int_context

#define OS_STOP_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"




/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task Serial_PeriodicTask
 */
CONST(tpl_proc_static, OS_CONST) Serial_PeriodicTask_task_stat_desc = {
  /* context                  */  Serial_PeriodicTask_CONTEXT,
  /* stack                    */  Serial_PeriodicTask_STACK,
  /* entry point (function)   */  Serial_PeriodicTask_function,
  /* internal ressource       */  NULL,
  /* task id                  */  Serial_PeriodicTask_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  1,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES

  /* execution budget */        0,
  /* timeframe        */        0, 
  /* pointer to the timing
     protection descriptor    */ NULL

#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task Serial_PeriodicTask
 */
VAR(tpl_proc, OS_VAR) Serial_PeriodicTask_task_desc = {
  /* resources                      */  NULL,
#if WITH_OSAPPLICATION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_OSAPPLICATION */
  /* activate count                 */  0,
  /* task priority                  */  1,
  /* task state                     */  SUSPENDED
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Task Hearbeat_PeriodicTask descriptor
 */
#define APP_Task_Hearbeat_PeriodicTask_START_SEC_CODE

#include "tpl_memmap.h"
/*
 * Task Hearbeat_PeriodicTask function prototype
 */

FUNC(void, OS_APPL_CODE) Hearbeat_PeriodicTask_function(void);
#define APP_Task_Hearbeat_PeriodicTask_STOP_SEC_CODE

#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */
/*
 * Task Hearbeat_PeriodicTask stack
 */
#define APP_Task_Hearbeat_PeriodicTask_START_SEC_STACK
#include "tpl_memmap.h"
VAR(tpl_stack_word, OS_APPL_DATA) Hearbeat_PeriodicTask_stack_zone[300/sizeof(tpl_stack_word)];
#define APP_Task_Hearbeat_PeriodicTask_STOP_SEC_STACK
#include "tpl_memmap.h"

#define Hearbeat_PeriodicTask_STACK {Hearbeat_PeriodicTask_stack_zone, 300}

/*
 * Task Hearbeat_PeriodicTask context
 */
#define OS_START_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"
VAR(arm_core_context, OS_VAR) Hearbeat_PeriodicTask_int_context;

#define Hearbeat_PeriodicTask_CONTEXT &Hearbeat_PeriodicTask_int_context

#define OS_STOP_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"




/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task Hearbeat_PeriodicTask
 */
CONST(tpl_proc_static, OS_CONST) Hearbeat_PeriodicTask_task_stat_desc = {
  /* context                  */  Hearbeat_PeriodicTask_CONTEXT,
  /* stack                    */  Hearbeat_PeriodicTask_STACK,
  /* entry point (function)   */  Hearbeat_PeriodicTask_function,
  /* internal ressource       */  NULL,
  /* task id                  */  Hearbeat_PeriodicTask_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  1,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES

  /* execution budget */        0,
  /* timeframe        */        0, 
  /* pointer to the timing
     protection descriptor    */ NULL

#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task Hearbeat_PeriodicTask
 */
VAR(tpl_proc, OS_VAR) Hearbeat_PeriodicTask_task_desc = {
  /* resources                      */  NULL,
#if WITH_OSAPPLICATION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_OSAPPLICATION */
  /* activate count                 */  0,
  /* task priority                  */  1,
  /* task state                     */  SUSPENDED
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#include "tpl_machine.h"

#define OS_START_SEC_CODE
#include "tpl_memmap.h"
  extern FUNC(void, OS_CODE) isr_CAN_function(void);

FUNC(void, OS_CODE) SysTickHandler(void)
{
  tpl_tick_SysTick();

}

FUNC(void, OS_CODE) TIM16_FDCAN_IT0_IRQHandler(void)
{
  isr_CAN_function();

}

#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
/*=============================================================================
 * Definition and initialization of process tables (tasks and isrs)
 */
CONSTP2CONST(tpl_proc_static, AUTOMATIC, OS_APPL_DATA)
tpl_stat_proc_table[TASK_COUNT+ISR_COUNT+1] = {
  &Serial_PeriodicTask_task_stat_desc,
  &Hearbeat_PeriodicTask_task_stat_desc,
  &IDLE_TASK_task_stat_desc
};

CONSTP2VAR(tpl_proc, AUTOMATIC, OS_APPL_DATA)
tpl_dyn_proc_table[TASK_COUNT+ISR_COUNT+1] = {
  &Serial_PeriodicTask_task_desc,
  &Hearbeat_PeriodicTask_task_desc,
  &IDLE_TASK_task_desc
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*=============================================================================
 * Definition and initialization of Alarm related structures
 */
/*-----------------------------------------------------------------------------
 * Alarm HeatbeatAlarm descriptor
 *
 * This alarm does the activation of task Hearbeat_PeriodicTask
 */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_task_activation_action, OS_CONST) HeatbeatAlarm_action = {
  {
    /* action function  */  tpl_action_activate_task
  },
  /* task id            */  Hearbeat_PeriodicTask_id
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
 
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_alarm_static, OS_CONST) HeatbeatAlarm_static = {
  {
    /* pointer to counter           */  &SystemCounter_counter_desc,
    /* pointer to the expiration    */  tpl_raise_alarm
#if (WITH_ID == YES)
    /* id of the alarm for tracing  */  , HeatbeatAlarm_id
#endif
#if WITH_OSAPPLICATION == YES
    /* OS application id            */  , 
#endif
  },
  /* action of the alarm  */  (tpl_action *)&HeatbeatAlarm_action
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_time_obj, OS_VAR) HeatbeatAlarm_alarm_desc = {
    /* pointer to the static part   */  (tpl_time_obj_static *)&HeatbeatAlarm_static,
    /* next alarm                   */  NULL,
    /* prev alarm                   */  NULL,
    /* cycle                        */  300,
    /* date                         */  300,
    /* State of the alarm           */  ALARM_AUTOSTART
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Alarm SerialAlarm descriptor
 *
 * This alarm does the activation of task Serial_PeriodicTask
 */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_task_activation_action, OS_CONST) SerialAlarm_action = {
  {
    /* action function  */  tpl_action_activate_task
  },
  /* task id            */  Serial_PeriodicTask_id
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
 
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_alarm_static, OS_CONST) SerialAlarm_static = {
  {
    /* pointer to counter           */  &SystemCounter_counter_desc,
    /* pointer to the expiration    */  tpl_raise_alarm
#if (WITH_ID == YES)
    /* id of the alarm for tracing  */  , SerialAlarm_id
#endif
#if WITH_OSAPPLICATION == YES
    /* OS application id            */  , 
#endif
  },
  /* action of the alarm  */  (tpl_action *)&SerialAlarm_action
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_time_obj, OS_VAR) SerialAlarm_alarm_desc = {
    /* pointer to the static part   */  (tpl_time_obj_static *)&SerialAlarm_static,
    /* next alarm                   */  NULL,
    /* prev alarm                   */  NULL,
    /* cycle                        */  10,
    /* date                         */  10,
    /* State of the alarm           */  ALARM_AUTOSTART
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
CONSTP2VAR(tpl_time_obj, AUTOMATIC, OS_APPL_DATA)
  tpl_alarm_table[ALARM_COUNT] = {
  &HeatbeatAlarm_alarm_desc,
  &SerialAlarm_alarm_desc
};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Declaration of flags functions
 */
/* $FLAGSFUNCTIONS$ */


/*=============================================================================
 * Definitions of the custom filter functions
 * filter functions are generated according to the type
 * used for the corresponding message object
 */
/*
 * ALWAYS filter function for type APP_CanTypeDef
 */

/*=============================================================================
 * Definition and initialization of Receive Messages related structures
 */

/*-----------------------------------------------------------------------------
 * Action of message serialMsgReceive
 */
/*-----------------------------------------------------------------------------
 * ALWAYS filter of message object serialMsgReceive
 */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

tpl_noparam_filter_desc serialMsgReceive_filter = {
    /*  filtering function          */  tpl_filter_always
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Static internal receiving queued message object serialMsgReceive
 */
 
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(APP_CanTypeDef, OS_VAR) serialMsgReceive_buffer[20];
VAR(APP_CanTypeDef, OS_VAR) serialMsgReceive_last;

VAR(tpl_queue_dyn, OS_VAR) serialMsgReceive_dyn_queue = {
  /*  current size of the queue           */  0,
  /*  read index                          */  0,
  /*  overflow flag                       */  FALSE
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_internal_receiving_queued_mo, OS_CONST) serialMsgReceive_message = {
  { /* data receiving mo struct   */
    { /* base receiving mo struct */
      /* notification pointer     */  NULL,
      /* next receiving mo        */  NULL
    },
    /*  receiving function      */  (tpl_receiving_func)tpl_receive_static_internal_queued_message,
    /*  copy function           */  (tpl_data_copy_func)tpl_copy_from_queued,
    /*  filter pointer          */  (tpl_filter_desc *)&serialMsgReceive_filter
  },
  { /*  queue structure   */
    /*  pointer to the dynamic descriptor   */  &serialMsgReceive_dyn_queue,
    /*  max size of the queue               */  20*sizeof(APP_CanTypeDef),
    /*  element size of the queue           */  sizeof(APP_CanTypeDef),
    /*  pointer to the buffer               */  (tpl_com_data *)serialMsgReceive_buffer,
    /*  pointer to the last written value   */  (tpl_com_data *)&serialMsgReceive_last
  }
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Definition and initialization of the receive messages table
 */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONSTP2CONST(tpl_base_receiving_mo, AUTOMATIC, OS_CONST)
tpl_receive_message_table[RECEIVE_MESSAGE_COUNT] = {
  (tpl_base_receiving_mo*)&serialMsgReceive_message
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Definition and initialization of Send Messages related structures
 */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Static internal sending static message object serialMsgSend
 */
CONST(tpl_internal_sending_mo, OS_CONST) serialMsgSend_message = {
  { /* base message object       */
    /* sending function          */ tpl_send_static_internal_message
  },
  /* pointer to the receiving mo */ (tpl_base_receiving_mo *)&serialMsgReceive_message
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*=============================================================================
 * Definition and initialization of the send messages table
 */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONSTP2CONST(tpl_base_sending_mo, AUTOMATIC, OS_CONST)
tpl_send_message_table[SEND_MESSAGE_COUNT] = {
  (tpl_base_sending_mo*)&serialMsgSend_message
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
/*=============================================================================
 * Definition and initialization of Ready List structures
 */
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_heap_entry, OS_VAR) tpl_ready_list[5];
VAR(tpl_rank_count, OS_VAR) tpl_tail_for_prio[4] = {
  0,
  0,
  0
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/**
 * @internal
 *
 * tpl_kern gather informations on the current executing object and
 * the previous one
 */
VAR(tpl_kern_state, OS_VAR) tpl_kern =
{
  NULL,                      /* no running task static descriptor   */
  &IDLE_TASK_task_stat_desc, /* elected task to run is idle task    */
  NULL,                      /* no running task dynamic descriptor  */
  &IDLE_TASK_task_desc,      /* elected task to run is idle task    */
  INVALID_PROC_ID,           /* no running task so no ID            */
  INVALID_PROC_ID,           /* idle task has no ID                 */
  NO_NEED_SWITCH,            /* no context switch needed at start   */
  FALSE,                     /* no schedule needed at start         */
#if WITH_MEMORY_PROTECTION == YES
  1,                         /* at early system startup, we run in  */
                             /*  kernel mode, so in trusted mode    */
#endif /* WITH_MEMORY_PROTECTION */
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define API_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
CONSTP2CONST(char, AUTOMATIC, OS_APPL_DATA) proc_name_table[TASK_COUNT + ISR_COUNT + 1] = {

  "Serial_PeriodicTask",
  "Hearbeat_PeriodicTask",
  "*idle*"
};
#define API_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/* End of file tpl_app_config.c */