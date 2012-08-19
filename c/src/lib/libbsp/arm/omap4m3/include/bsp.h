/*
 * Copyright (c) 2012 Xi Yang (hiyangxi@gmail.com).  All rights reserved.
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

#ifndef LIBBSP_ARM_OMAP4M3_BSP_H
#define LIBBSP_ARM_OMAP4M3_BSP_H

#include <bspopts.h>

#include <rtems.h>
#include <rtems/console.h>
#include <rtems/clockdrv.h>
#include <bsp/omap4m3.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef RTEMS_SMP
  extern volatile unsigned int bsp_online_cpus;
  extern volatile unsigned int bsp_ap_stack_end;
#endif

#define BSP_FEATURE_IRQ_EXTENSION

#define BSP_ARMV7M_IRQ_PRIORITY_DEFAULT (5 << 5)

#define BSP_ARMV7M_SYSTICK_PRIORITY (6 << 5)

#define BSP_ARMV7M_SYSTICK_FREQUENCY (200000000)

#define AVOID_COPYING_VECTOR_TABLE 1

#ifndef ASM

#endif /* ASM */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBBSP_ARM_OMAP4M3_BSP_H */
