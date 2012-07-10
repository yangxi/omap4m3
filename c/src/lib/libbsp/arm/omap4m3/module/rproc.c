/* Copyright (c) 2012 Xi Yang (hiyangxi@gmail.com).  All rights reserved.*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/remoteproc.h>

MODULE_LICENSE("Dual DSD/GPL");

struct rproc *dummy_rproc = NULL;

static int __init rproc_init(void) {

  printk(KERN_ALERT "Start remote Cortex M3 system\n");
  
  dummy_rproc = rproc_get_by_name("ipu_c0");
  if (!dummy_rproc) {
    printk(KERN_ALERT "Can not load the image to M3\n");
  }
  return 0;
}

static void rproc_exit(void) {
  printk(KERN_ALERT "rproc leaving\n");
  if (dummy_rproc != NULL){  
    printk(KERN_ALERT "Put rproc handle\n");
    rproc_put(dummy_rproc);
  }
}

module_init(rproc_init);
module_exit(rproc_exit);
