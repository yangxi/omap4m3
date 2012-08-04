/*
 * Copyright (c) 2012 Xi Yang (hiyangxi@gmail.com).  All rights reserved.
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


  struct fw_rsc_carveout {
    unsigned int type;
    unsigned int da;
    unsigned int pa;
    unsigned int len;
    unsigned int flags;
    unsigned int reserved;
    char name[32];
  };

  struct fw_rsc_devmem {
    unsigned int type;
    unsigned int da;
    unsigned int pa;
    unsigned int len;
    unsigned int flags;
    unsigned int reserved;
    char name[32];
  };

  struct fw_rsc_trace {
    unsigned int type;
    unsigned int da;
    unsigned int len;
    unsigned int reserved;
    char name[32];
  };

  struct fw_rsc_vdev_vring {
    unsigned int da; /* device address */
    unsigned int align;
    unsigned int num;
    unsigned int notifyid;
    unsigned int reserved;
  };

  struct fw_rsc_vdev {
    unsigned int type;
    unsigned int id;
    unsigned int notifyid;
    unsigned int dfeatures;
    unsigned int gfeatures;
    unsigned int config_len;
    char status;
    char num_of_vrings;
    char reserved[2];
  };

  struct resource_table {
    unsigned int version;
    unsigned int num;
    unsigned int reserved[2];
    unsigned int offset[3];
    /* data carveout entry */
    struct fw_rsc_carveout data_cout;
    struct fw_rsc_devmem l4_wkup;
    struct fw_rsc_trace trace;
  };

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBBSP_ARM_OMAP4M3_OMAP4M3_H */
