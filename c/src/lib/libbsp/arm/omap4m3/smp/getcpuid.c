/*
 * Copyright (c) 2012 Xi Yang (hiyangxi@gmail.com).  All rights reserved.
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

#include <bsp/omap4m3.h>


int bsp_smp_processor_id(void)
{
  return TOUCH_REG(CPUID_REG);
}

