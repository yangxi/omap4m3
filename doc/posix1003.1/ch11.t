@c
@c  COPYRIGHT (c) 1988-1998.
@c  On-Line Applications Research Corporation (OAR).
@c  All rights reserved.
@c
@c  $Id$
@c

@chapter Synchronization

@section Semaphore Characteristics

@section Semaphore Functions

@subsection Initialize an Unnamed Semaphore

@example
sem_init(), Function
@end example

@subsection Destroy an Unnamed Semaphore

@example
sem__destroy(), Function
@end example

@subsection Initialize/Open a Named Semaphore

@example
sem_open(), Function
@end example

@subsection Close a Named Semaphore

@example
sem_close(), Function
@end example

@subsection Remove a Named Semaphore

@example
sem_unlink(), Function
@end example

@subsection Lock a Semaphore

@example
sem_wait(), Function
sem_trywait(), Function
@end example

@subsection Unlock a Semaphore

@example
sem_post(), Function
@end example

@subsection Get the Value of a Semaphore

@example
sem_getvalue(), Function
@end example

@section Mutexes

@subsection Mutex Initialization Attributes

@example
pthread_mutexattr_init(), Function
pthread_mutexattr_destroy(), Function
pthread_mutexattr_getpshared(), Function
pthread_mutexattr_setpshared(), Function
@end example

@subsection Initializing and Destroying a Mutex

@example
pthread_mutex_init(), Function
pthread_mutex_destroy(), Function
@end example

@subsection Locking and Unlocking a Mutex

@example
pthread_mutex_lock(), Function
pthread_mutex_trylock(), Function
pthread_mutex_unlock(), Function
@end example

@section Condition Variables

@subsection Condition Variable Initialization Attributes

@example
pthread_condattr_init(), Function
pthread_condattr_destroy(), Function
pthread_condattr_getpshared(), Function
pthread_condattr_setpshared(), Function
@end example

@subsection Initialization and Destroying Condition Variables

@example
pthread_cond_init(), Function
pthread_cond_destroy(), Function
@end example

@subsection Broadcasting and Signaling a Condition

@example
pthread_cond_signal(), Function
pthread_cond_broadcast(), Function
@end example

@subsection Waiting on a Condition

@example
pthread_cond_wait(), Function
pthread_cond_timedwait(), Function
@end example

