/*
 * Copyright (c) 2012 Xi Yang (hiyangxi@gmail.com).  All rights reserved.
 * Copyright (c) 2011 Sebastian Huber.  All rights reserved.
 *
 *  embedded brains GmbH
 *  Obere Lagerstr. 30
 *  82178 Puchheim
 *  Germany
 *  <rtems@embedded-brains.de>
 *
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


/*When Linux loads the ELF image to remote M3 cores, it checks ".resource_table"
  section to load the image correctly*/

__attribute__ ((section(".resource_table")))
struct resource_table resources = {
  1, /* we're the first version that implements this */
  3, /* number of entries in the table */
  0, 0, /* reserved, must be zero */
	/* offsets to entries */
  {
    (unsigned int)(&(((struct resource_table *)(0))->data_cout)),
    (unsigned int)(&(((struct resource_table *)(0))->l4_wkup)),
    (unsigned int)(&(((struct resource_table *)(0))->trace)),
  },	
  { TYPE_CARVEOUT, IMAGE_VIR_ADDR, IMAGE_PHY_ADDR, IMAGE_RESERVE_SIZE, 0x0, 0, "text" },
  { TYPE_DEVMEM, L4_WKUP_VIRADDR, L4_WKUP_PHYADDR, L4_WKUP_SIZE, 0x0, 0, "l4wkup" },
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
  /* Do nothing */
}

void BSP_START_TEXT_SECTION bsp_start_hook_1(void)
{
  /* Do nothing */
}


void bsp_reset(void)
{
  /*Do nothing to reset*/
  /*Linux side could shutdown RTEMS via remoteproce*/
}
