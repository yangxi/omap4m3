/*
 *  Copyright (c) 2012 Xi Yang (hiyangxi@gmail.com).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 */
#include <linux/io.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/remoteproc.h>

MODULE_LICENSE("BSD");

struct rproc *dummy_rproc = NULL;

#define M3_RSTCTRL              0x4a306910
#define OMAP2_L4_IO_OFFSET      0xb2000000
#define OMAP2_L4_IO_ADDRESS(pa) IOMEM((pa) + OMAP2_L4_IO_OFFSET)

static int __init rproc_init(void) {

  printk(KERN_ALERT "Start remote Cortex M3 system\n");

  //rproc_get_by_name will load /lib/firmware/ducati-m3-core0.xem3 to the first M3 core.

  dummy_rproc = rproc_get_by_name("ipu_c0");
  if (!dummy_rproc) {
    printk(KERN_ALERT "Can not load the image to M3\n");
  }
  return 0;
}

static void rproc_exit(void) {
  volatile unsigned int *r = OMAP2_L4_IO_ADDRESS(M3_RSTCTRL);
  printk(KERN_ALERT "rproc leaving\n");

  //Release the system, shutdown remote core.
  if (dummy_rproc != NULL){
    printk(KERN_ALERT "Reset Cortex M3 Core2,%x\n",*r);
    *r |= 0x2;
    printk(KERN_ALERT "RSTCTRL reg after reset %x\n",*r);
    printk(KERN_ALERT "Put rproc handle\n");
    rproc_put(dummy_rproc);
  }
}

module_init(rproc_init);
module_exit(rproc_exit);
