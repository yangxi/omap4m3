/*
 * Copyright (c) 2012 Xi Yang (hiyangxi@gmail.com).  All rights reserved.
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

#include <bsp.h>
#include <bsp/start.h>
#include <bsp/omap4m3.h>
#include <bsp/bootcard.h>
#include <bsp/irq-generic.h>
#include <bsp/irq.h>
#include <bsp/linker-symbols.h>


#if 0
#define Debug(format,...) printk( format, __VA_ARGS__)
#else
#define Debug(format,...)
#endif


/*When Linux loads the ELF image to remote M3 cores, it checks ".resource_table"
  section to load the image correctly*/

const static struct resource_table resources __attribute__ ((used,section(".resource_table"))) = {
  1, /* 1st version */
  3, /* number of entries in the table */
  0, 0, /* reserved */
  /* offsets */
  {
    (unsigned int)(&(((struct resource_table *)(0))->data_cout)),
    (unsigned int)(&(((struct resource_table *)(0))->l4_wkup)),
    (unsigned int)(&(((struct resource_table *)(0))->trace)),
  },
  { TYPE_CARVEOUT, IMAGE_VIR_ADDR, IMAGE_PHY_ADDR, IMAGE_RESERVE_SIZE, 0x0, 0, "text" },
  { TYPE_DEVMEM, L4_IO_VIRADDR, L4_IO_PHYADDR, L4_IO_SIZE, 0x0, 0, "l4io" },
  { TYPE_TRACE, TRACEBUF_START, TRACEBUF_LEN, 0x0, "m3trace"},
};


void bsp_start(void)
{
  if (bsp_interrupt_initialize() != RTEMS_SUCCESSFUL) {
    _CPU_Fatal_halt(0xe);
  }
}

void BSP_START_TEXT_SECTION bsp_start_hook_0(void)
{
#ifdef RTEMS_SMP
  unsigned int cpuid = TOUCH_REG(CPUID_REG);


  if (cpuid == 0){
    Debug("cpu %d: init hardware spinlock\n",cpuid);
    bsp_init_hwspinlock();
  }

  if (cpuid == 1){
  Debug("cpu %d: stack at %p, cpu number %d\n",
         cpuid,
         &cpuid,
         bsp_online_cpus);
    rtems_smp_secondary_cpu_initialize();
  }
#endif
}

void BSP_START_TEXT_SECTION bsp_start_hook_1(void)
{
}


void bsp_reset(void)
{
  /*Do nothing to reset*/
  /*Linux side could shutdown RTEMS via remoteproce*/
}
