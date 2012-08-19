/*
 * Copyright (c) 2012 Xi Yang (hiyangxi@gmail.com).  All rights reserved.
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

/*Global variables*/

#include <rtems.h>
#include <bsp.h>
#include <rtems/bspIo.h>
#include <rtems/bspsmp.h>
#include <bsp/omap4m3.h>
#include <rtems/score/armv7m.h>


volatile unsigned int bsp_online_cpus = 0;
volatile unsigned int bsp_ap_stack_end = 0;

void printk(const char *, ...);

#ifdef 0
#define Debug printk
#endif

static void m3_ap_ipi_handler(void);

void bsp_smp_secondary_cpu_initialize(int cpu)
{
  Debug("bsp_smp_secondary_cpu_init is called\n");
  Debug("cpu 1: stack at %p\n", &cpu);
  /*setup interrupt here*/
  _ARMV7M_Set_exception_priority_and_handler(
    ARMV7M_VECTOR_IRQ(IPI_ISR_NUM),
    BSP_ARMV7M_IRQ_PRIORITY_DEFAULT,
    m3_ap_ipi_handler
  );
  
  bsp_interrupt_vector_enable(IPI_ISR_NUM);
}


int bsp_smp_initialize(int maximum)
{  
  Debug("bsp_smp_initialize(%d)\n", maximum);
  if ( rtems_configuration_smp_maximum_processors > 1 ){
    bsp_ap_stack_end = _Per_CPU_Information_p[1]->interrupt_stack_high;
    Debug("set up ap's stack to %p\n", bsp_ap_stack_end);
    /*wake ap up */
    TOUCH_REG(CLK_RESET_REG) = 0;
    while(bsp_online_cpus < 2)
      ;
    //    Debug("ap should be up now\n");
    return BSP_MAX_CPUS;
  }
  return 1;
}


/*IRQ 19 on Core1 can be interupted by writing register CORTEXM3_CTRL_REG(0x5508 1000)*/

static void m3_ap_ipi_handler(void)
{
  _ARMV7M_Interrupt_service_enter();
  Debug("cpu:%d in ipi isr\n",bsp_smp_processor_id());
  TOUCH_REG16(M3_IPI_CORE1) &= ~(0x1);
  rtems_smp_process_interrupt();
  _ARMV7M_Interrupt_service_leave();
  if ( _Thread_Dispatch_necessary &&
       (_Thread_Dispatch_disable_level == 0) )
    _Thread_Dispatch();
}

/*send interrupt from main processor to application processor*/
void bsp_smp_interrupt_cpu(int cpu)
{
  Debug("CPU:%d ipi to CPU %d\n",bsp_smp_processor_id(), cpu);
  TOUCH_REG16(M3_IPI_CORE1) |= 0x1;
}

void bsp_smp_broadcast_interrupt(void)
{  
  Debug("BC to cpu 1\n");
  bsp_smp_interrupt_cpu(1);
  Debug("cpu 0 handle broadcast\n");
  rtems_smp_process_interrupt();
}

void bsp_smp_delay(int max)
{
  volatile int count = 0;

  for(count=0; count <=max; count++)
    ;
}

void bsp_smp_wait_for( volatile unsigned int *address,
		       unsigned int desired,
		       int maximum_usecs)
{
  volatile unsigned int i;
  
  if (desired == RTEMS_BSP_SMP_FIRST_TASK){
    while(*address!=desired)
      for(i=0;i<1000000;i++)
	;
    while( _ARMV7M_NVIC_Is_pending(3) == 0)
      ;   
    TOUCH_REG16(M3_IPI_CORE1) &= ~(0x1);
    _ARMV7M_NVIC_Clear_pending(3);
    Debug("IRQ 3 is %d,%d\n", _ARMV7M_NVIC_Is_pending(3), _ARMV7M_NVIC_Is_active(3));
    rtems_smp_process_interrupt();
    //    __builtin_unreachable();
    Debug("I should not here\n");
    /*never return here*/
  }
  
  /*for other message, just fall in the loop*/
  while(*address!=desired)
    for(i=0;i<1000000;i++)
      ;
}


void bsp_init_hwspinlock(void)
{
  Debug("HW_SPIN_CLK status is %x\n", TOUCH_REG(HW_SPIN_CLK));
  TOUCH_REG(HW_SPIN_SYSCONFIG) |= 0x2;
  while(!(TOUCH_REG(HW_SPIN_SYSSTATUS) & 0x1))
    ;
  Debug("HW_SPIN_CLK is inited, %x\n", TOUCH_REG(HW_SPIN_SYSSTATUS));
}



Context_Control _CPU_Context_ap;

void __attribute__((naked)) _CPU_Context_first_task_smp_restore(
  Context_Control *heir
)
{
  Debug("First task\n");
  _ISR_Nest_level = 0;
  _Thread_Dispatch_disable_level = 1;
  _ISR_Enable_on_this_core(0);		
  _ARMV7M_Start_multitasking(&_CPU_Context_ap, heir);
  __builtin_unreachable();
}

