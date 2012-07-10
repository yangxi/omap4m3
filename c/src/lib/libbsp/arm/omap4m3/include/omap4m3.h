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

#ifndef LIBBSP_ARM_OMAP4M3_OMAP4M3_H
#define LIBBSP_ARM_OMAP4M3_OMAP4M3_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define IMAGE_PHY_ADDR (0xb0000000)
#define IMAGE_VIR_ADDR (0x0)
#define IMAGE_RESERVE_SIZE (0x2000000)

  /*Use TYPE_TRACE as terminal*/
#define TRACEBUF_START (0x1000000)
#define TRACEBUF_LEN (0x100000)
#define TRACEBUF_END (TRACEBUF_START + TRACEBUF_LEN)


  /*Map L4 registers space to 0xfff00000*/
#define L4_WKUP_PHYADDR (0x4a300000)
#define L4_WKUP_VIRADDR (0xfff00000)
#define L4_WKUP_SIZE (0x100000)

  /*Reset register*/
#define RM_MPU_M3_RSTCTRL (0x6910 + L4_WKUP_VIRADDR)

#define TOUCH_REG(reg) (*(volatile unsigned int*)(reg))

  /* Resource info: Must match include/linux/remoteproc.h: */
#define TYPE_CARVEOUT    0
#define TYPE_DEVMEM      1
#define TYPE_TRACE       2
#define TYPE_VDEV  3

  typedef unsigned int u32;

  struct fw_rsc_carveout {
    u32 type;
    u32 da;
    u32 pa;
    u32 len;
    u32 flags;
    u32 reserved;
    char name[32];
  };

  struct fw_rsc_devmem {
    u32 type;
    u32 da;
    u32 pa;
    u32 len;
    u32 flags;
    u32 reserved;
    char name[32];
  };

  struct fw_rsc_trace {
    u32 type;
    u32 da;
    u32 len;
    u32 reserved;
    char name[32];
  };

  struct fw_rsc_vdev_vring {
    u32 da; /* device address */
    u32 align;
    u32 num;
    u32 notifyid;
    u32 reserved;
  };

  struct fw_rsc_vdev {
    u32 type;
    u32 id;
    u32 notifyid;
    u32 dfeatures;
    u32 gfeatures;
    u32 config_len;
    char status;
    char num_of_vrings;
    char reserved[2];
  };

  struct resource_table {
    u32 version;
    u32 num;
    u32 reserved[2];
    u32 offset[3];
    /* data carveout entry */
    struct fw_rsc_carveout data_cout;
    struct fw_rsc_devmem l4_wkup;
    struct fw_rsc_trace trace;
  };

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBBSP_ARM_OMAP4M3_OMAP4M3_H */
