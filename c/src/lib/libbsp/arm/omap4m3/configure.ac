##
#
# @file
#
# @brief Configure script of LibBSP for the M3 subsystem on OMAP4 boards.
#

AC_PREREQ([2.68])
AC_INIT([rtems-c-src-lib-libbsp-arm-omap4m3],[_RTEMS_VERSION],[rtems-bugs@rtems.com])
AC_CONFIG_SRCDIR([bsp_specs])
RTEMS_TOP(../../../../../..)

RTEMS_CANONICAL_TARGET_CPU
AM_INIT_AUTOMAKE([no-define nostdinc foreign 1.11.1])
RTEMS_BSP_CONFIGURE

RTEMS_PROG_CC_FOR_TARGET
RTEMS_CANONICALIZE_TOOLS
RTEMS_PROG_CCAS

RTEMS_CHECK_NETWORKING
RTEMS_CHECK_SMP

AM_CONDITIONAL(HAS_NETWORKING,test "$HAS_NETWORKING" = "yes")
AM_CONDITIONAL(HAS_SMP,[test "$rtems_cv_HAS_SMP" = "yes"])

RTEMS_BSP_CLEANUP_OPTIONS(0, 0)
RTEMS_BSP_LINKCMDS

RTEMS_BSPOPTS_SET([BSP_OMAP4M3_SMP],[*],[1])
RTEMS_BSPOPTS_HELP([BSP_OMAP4M3_SMP],
[Always defined for omap4m3 bsp])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
