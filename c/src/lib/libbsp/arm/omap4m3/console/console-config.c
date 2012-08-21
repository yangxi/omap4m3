/*
 * Copyright (c) 2012 Xi Yang (hiyangxi@gmail.com).  All rights reserved.
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

#include <bspopts.h>
#include <bsp/irq.h>
#include <bsp/omap4m3.h>

#include <bsp.h>
#include <rtems/libio.h>
#include <termios.h>
#include <rtems/bspIo.h>
#include <libchip/serial.h>
#include <libchip/sersupp.h>

///////////////// trace_uart_fns //////////////////////////////
/* static function prototypes */
static int     trace_first_open(int major, int minor, void *arg);
static int     trace_last_close(int major, int minor, void *arg);
static int     trace_read(int minor);
static ssize_t trace_write(int minor, const char *buf, size_t len);
static void    trace_init(int minor);
static void    trace_write_polled(int minor, char c);
static int     trace_set_attributes(int minor, const struct termios *t);

/* Pointers to functions for handling the UART. */
console_fns trace_uart_fns =
{
    libchip_serial_default_probe,
    trace_first_open,
    trace_last_close,
    trace_read,
    trace_write,
    trace_init,
    trace_write_polled,   /* not used in this driver */
    trace_set_attributes,
    FALSE      /* TRUE if interrupt driven, FALSE if not. */
};


/*
 * This is called the first time each device is opened. Since
 * the driver is polled, we don't have to do anything. If the driver
 * were interrupt driven, we'd enable interrupts here.
 */
static int trace_first_open(int major, int minor, void *arg)
{
    return 0;
}


/*
 * This is called the last time each device is closed.  Since
 * the driver is polled, we don't have to do anything. If the driver
 * were interrupt driven, we'd disable interrupts here.
 */
static int trace_last_close(int major, int minor, void *arg)
{
    return 0;
}


/*
 * Read one character from UART.
 *
 * return -1 if there's no data, otherwise return
 * the character in lowest 8 bits of returned int.
 */
static int trace_read(int minor)
{
  printk("trace_read is called\n");
  return 0;
}


/*
 * Write buffer to UART
 *
 * return 1 on success, -1 on error
 */
static ssize_t trace_write(int minor, const char *buf, size_t len)
{
  int i;
    for (i = 0; i < len; i++)
      BSP_output_char(buf[i]);
    return 1;
}


static void trace_init(int minor)
{
}

/* I'm not sure this is needed for the shared console driver. */
static void trace_write_polled(int minor, char c)
{
  BSP_output_char(c);
}

/* This is for setting baud rate, bits, etc. */
static int trace_set_attributes(int minor, const struct termios *t)
{
    return 0;
}

/***********************************************************************/
/*
 * The following functions are not used by TERMIOS, but other RTEMS
 * functions use them instead.
 */
/***********************************************************************/
/*
 * Read from UART. This is used in the exit code, and can't
 * rely on interrupts.
 */
int trace_poll_read(int minor)
{
    return trace_read(minor);
}


console_tbl Console_Configuration_Ports [] = {
    {
      .sDeviceName = "/dev/ttyS0",
      .pDeviceFns = &trace_uart_fns,
    },
};

unsigned long Console_Configuration_Count = 1;


char * tracebuf_cursor = TRACEBUF_START;

static void output_char(char c)
{
  if((unsigned int)tracebuf_cursor >= TRACEBUF_END)
    tracebuf_cursor = (char *)TRACEBUF_START;

  *tracebuf_cursor++ = c;
}

BSP_output_char_function_type BSP_output_char = output_char;

BSP_polling_getchar_function_type BSP_poll_char = NULL;



