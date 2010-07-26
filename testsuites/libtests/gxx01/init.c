/*
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#include <tmacros.h>
#include "test_support.h"
#include "gxx_wrappers.h"

void test_recursive_mutex(void)
{
  int                sc;
   __gthread_mutex_t mutex;

  mutex = 0;
  puts( "rtems_gxx_recursive_mutex_init() - OK" );
  rtems_gxx_recursive_mutex_init(&mutex);
  rtems_test_assert( mutex != 0 );

  puts( "rtems_gxx_recursive_mutex_trylock() - OK" );
  sc = rtems_gxx_recursive_mutex_trylock(&mutex);
  rtems_test_assert( sc == 0 );

  puts( "rtems_gxx_recursive_mutex_trylock() - Nest" );
  sc = rtems_gxx_recursive_mutex_trylock(&mutex);
  rtems_test_assert( sc == 0 );

  puts( "rtems_gxx_recursive_mutex_unlock() - Unnest" );
  sc = rtems_gxx_recursive_mutex_unlock(&mutex);
  rtems_test_assert( sc == 0 );

  puts( "rtems_gxx_recursive_mutex_unlock() - OK" );
  sc = rtems_gxx_recursive_mutex_unlock(&mutex);
  rtems_test_assert( sc == 0 );

  puts( "rtems_gxx_recursive_mutex_lock() - OK" );
  sc = rtems_gxx_recursive_mutex_lock(&mutex);
  rtems_test_assert( sc == 0 );

  puts( "rtems_gxx_recursive_mutex_unlock() - OK" );
  sc = rtems_gxx_recursive_mutex_unlock(&mutex);
  rtems_test_assert( sc == 0 );

  puts( "rtems_gxx_mutex_destroy(mutex) - OK" );
  sc = rtems_gxx_mutex_destroy(&mutex);
  rtems_test_assert( sc == 0 );

  puts( "rtems_gxx_mutex_destroy(mutex) - NOT OK" );
  sc = rtems_gxx_mutex_destroy(&mutex);
  rtems_test_assert( sc == -1 );
}

void test_mutex(void)
{
  int                sc;
   __gthread_mutex_t mutex;

  mutex = 0;
  puts( "rtems_gxx_mutex_init() - OK" );
  rtems_gxx_mutex_init(&mutex);
  rtems_test_assert( mutex != 0 );

  puts( "rtems_gxx_mutex_trylock() - OK" );
  sc = rtems_gxx_mutex_trylock(&mutex);
  rtems_test_assert( sc == 0 );

  puts( "rtems_gxx_mutex_unlock() - OK" );
  sc = rtems_gxx_mutex_unlock(&mutex);
  rtems_test_assert( sc == 0 );

  puts( "rtems_gxx_mutex_lock() - OK" );
  sc = rtems_gxx_mutex_lock(&mutex);
  rtems_test_assert( sc == 0 );

  puts( "rtems_gxx_mutex_unlock() - OK" );
  sc = rtems_gxx_mutex_unlock(&mutex);
  rtems_test_assert( sc == 0 );
}

void once_function(void)
{
  puts( "Running once method" );
}

void test_once(void)
{
  __gthread_once_t once;
  int              sc;

  once = 0;

  puts( "Call once method the first time" );
  sc = rtems_gxx_once(&once, once_function);
  rtems_test_assert( sc == 0 );

  puts( "Call once method the second time" );
  sc = rtems_gxx_once(&once, once_function);
  rtems_test_assert( sc == 0 );
}

volatile bool key_dtor_ran;
void *key_for_testing;

void key_dtor(void *ptr)
{
  key_dtor_ran = true;
}

void test_key(void)
{
  int              sc;
  __gthread_key_t  key;
  void            *p;

  puts( "rtems_gxx_key_create(&key, NULL) - OK" );
  sc = rtems_gxx_key_create(&key, NULL);
  rtems_test_assert( sc == 0 );

  puts( "rtems_gxx_key_delete(key) - OK" );
  sc = rtems_gxx_key_delete(key);
  rtems_test_assert( sc == 0 );

  puts( "rtems_gxx_key_create(&key, key_dtor) - OK" );
  sc = rtems_gxx_key_create(&key, key_dtor);
  rtems_test_assert( sc == 0 );

  puts( "rtems_gxx_setspecific() - OK" );
  sc = rtems_gxx_setspecific(key, (void *)0x1234);
  rtems_test_assert( sc == 0 );

  puts( "rtems_gxx_getspecific(key) already existing - OK" );
  p = rtems_gxx_getspecific(key);
  rtems_test_assert( p == (void *)0x1234 );

  puts( "rtems_gxx_key_delete(key) - OK" );
  sc = rtems_gxx_key_delete(key);
  rtems_test_assert( sc == 0 );
  rtems_test_assert( key_dtor_ran == true );

  puts( "rtems_gxx_getspecific(key_for_testing) non-existent - OK" );
  p = rtems_gxx_getspecific((__gthread_key_t) &key_for_testing);
  rtems_test_assert( p == NULL );
  rtems_test_assert( key_for_testing == NULL );

  key_for_testing = malloc(4);
  rtems_test_assert( key_for_testing != NULL );
  
  puts( "rtems_gxx_key_delete(key_for_testing) - OK" );
  sc = rtems_gxx_key_delete((__gthread_key_t) &key_for_testing);
  rtems_test_assert( sc == 0 );
  rtems_test_assert( key_for_testing == NULL );


  key = (void *)0x1234;
  puts( "rtems_gxx_key_dtor(&key) - OK" );
  sc = rtems_gxx_key_dtor((__gthread_key_t) &key, key_dtor);
  rtems_test_assert( sc == 0 );
  rtems_test_assert( key == NULL );
}

void test_out_of_mutexes(void)
{
   __gthread_mutex_t mutex;

  puts( "rtems_gxx_mutex_init() until exhausted and panic" );
  puts( "rtems_gxx_mutex_init() panic AFTER printing EOF message" );
  puts( "*** END OF TEST GXX 01 ***" );

  while (1) {
    rtems_gxx_mutex_init(&mutex);
    rtems_test_assert( mutex != 0 );
  }
}

rtems_task Init(
  rtems_task_argument argument
)
{
  puts( "\n\n*** TEST GXX 01 ***" );

  test_mutex();
  puts( "" );

  test_recursive_mutex();
  puts( "" );

  test_once();
  puts( "" );

  test_key();
  puts( "" );

  test_out_of_mutexes();

  /* does not return */
}

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_TASKS        1
#define CONFIGURE_MAXIMUM_SEMAPHORES   2
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT

#include <rtems/confdefs.h>
/* end of file */