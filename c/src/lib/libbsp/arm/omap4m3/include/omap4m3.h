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

  /*cpuid register*/

#define TOUCH_REG(x) (*((volatile unsigned int*)(x)))
#define TOUCH_REG16(x) (*((volatile unsigned short*)(x)))

#define CPUID_REG (0xe00fe000)
#define CLK_RESET_REG (0xfff06910)

#define BSP_MAX_CPUS (2)

#define IMAGE_PHY_ADDR (0xb0000000)
#define IMAGE_VIR_ADDR (0x0)
#define IMAGE_RESERVE_SIZE (0x2000000)

  /*Use TYPE_TRACE as terminal*/
#define TRACEBUF_START (0x1000000)
#define TRACEBUF_LEN (0x100000)
#define TRACEBUF_END (TRACEBUF_START + TRACEBUF_LEN)

  /*map L4 IO space to 0xffc00000*/
#define L4_IO_PHYADDR (0x4a000000)
#define L4_IO_VIRADDR (0xffc00000)
#define L4_IO_SIZE    (0x400000)

  /*generate/clear ipi interrupt between m3 cores*/
#define M3_IO_VIRADDR (0x55080000)
#define M3_IO_SIZE (0x20000)
#define M3_IPI_CORE0 (M3_IO_VIRADDR + 0x1000)
#define M3_IPI_CORE1 (M3_IO_VIRADDR + 0x1002)
#define IPI_ISR_NUM (3)

/*Map L4 registers space to 0xfff00000*/
#define L4_WKUP_PHYADDR (0x4a300000)
#define L4_WKUP_VIRADDR (0xfff00000)
#define L4_WKUP_SIZE (0x100000)

/*hardware spin lock address*/
#define HW_SPIN_CLK (L4_IO_VIRADDR + 0x8d28)
#define HW_SPIN_BASE (L4_IO_VIRADDR + 0xf6000)
#define HW_SPIN_SYSCONFIG (HW_SPIN_BASE + 0x10)
#define HW_SPIN_SYSSTATUS (HW_SPIN_BASE + 0X14)
#define HW_SPIN_REG(x) (HW_SPIN_BASE + 0x0800+ 4*(x))

  

  /*Reset register*/
#define RM_MPU_M3_RSTCTRL (0x6910 + L4_WKUP_VIRADDR)

#define TOUCH_REG(reg) (*(volatile unsigned int*)(reg))

#define SMP_CPU_SWAP( _address, _value, _previous ) \
    do { \
    while (TOUCH_REG(HW_SPIN_REG(0))!=0);\
    _previous = *_address; \
    *_address = _value;\
    TOUCH_REG(HW_SPIN_REG(0)) = 0;\
    } while (0) 

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
