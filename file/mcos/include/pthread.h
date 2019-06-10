/* 
 * Copyright (C) 2019 eSOL Co.,Ltd. Tokyo, Japan
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE FREEBSD PROJECT ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL THE FREEBSD PROJECT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*============================================================================
 pthread.h   POSIX Layer   Main pthread header
============================================================================*/
#ifndef __PTHREAD_H__
#define __PTHREAD_H__

#if !defined COMPILER_RESTRICT
#if defined __cplusplus
#define COMPILER_RESTRICT
#else /* __cplusplus */
#define COMPILER_RESTRICT restrict
#endif /* __cplusplus */
#endif /* COMPILER_RESTRICT */

#include <sys/types.h>
#include <sched.h>
#include <time.h>

#ifdef  __cplusplus
extern  "C" {
#endif

/* Initializers */
#define PTHREAD_COND_INITIALIZER            {0}
#define PTHREAD_ONCE_INIT                   {0}

 /* For LIBC and older POSIX compatibility */
#define PTHREAD_RWLOCK_INITIALIZER          {0}

/* Returned to only one thread waiting at the barrier */
#define PTHREAD_BARRIER_SERIAL_THREAD      -1

/* Cancel state control */
#define PTHREAD_CANCEL_ENABLE               1
#define PTHREAD_CANCEL_DISABLE              0

/* Cancel type control */
#define PTHREAD_CANCEL_ASYNCHRONOUS         1
#define PTHREAD_CANCEL_DEFERRED             0

 /* Exit status of a canceled thread */
#define PTHREAD_CANCELED           ((void*)-1)

/* Thread detached states */
#define PTHREAD_CREATE_DETACHED             1
#define PTHREAD_CREATE_JOINABLE             0

/* Thread scheduling types */
#define PTHREAD_EXPLICIT_SCHED              0
#define PTHREAD_INHERIT_SCHED               1

/* Mutex types */
#define PTHREAD_MUTEX_NORMAL                0
#define PTHREAD_MUTEX_ERRORCHECK            1
#define PTHREAD_MUTEX_RECURSIVE             2
#define PTHREAD_MUTEX_DEFAULT               PTHREAD_MUTEX_NORMAL

/* Robust mutex definitions */
#define PTHREAD_MUTEX_STALLED               0
#define PTHREAD_MUTEX_ROBUST                1

/* Mutex priority inversion control */
#define PTHREAD_PRIO_NONE                   0
#define PTHREAD_PRIO_INHERIT                1
#define PTHREAD_PRIO_PROTECT                2

/* Process sharing attribute */
#define PTHREAD_PROCESS_PRIVATE             0
#define PTHREAD_PROCESS_SHARED              1

/* Scheduling scope */
#define PTHREAD_SCOPE_SYSTEM                0
#define PTHREAD_SCOPE_PROCESS               1   /* Unsupported */


/* Prototypes */
int   pthread_atfork(void (*)(void), void (*)(void), void(*)(void));

/* Thread attributes */
int   pthread_attr_init(pthread_attr_t *);
int   pthread_attr_destroy(pthread_attr_t *);

int   pthread_attr_getdetachstate(const pthread_attr_t *, int *);
int   pthread_attr_setdetachstate(pthread_attr_t *, int);

int   pthread_attr_getguardsize(const pthread_attr_t *COMPILER_RESTRICT, size_t *COMPILER_RESTRICT);   /* Unsupported */
int   pthread_attr_setguardsize(pthread_attr_t *, size_t);   /* Unsupported */

int   pthread_attr_getinheritsched(const pthread_attr_t *COMPILER_RESTRICT, int *COMPILER_RESTRICT);
int   pthread_attr_setinheritsched(pthread_attr_t *, int);

int   pthread_attr_getschedparam(const pthread_attr_t *COMPILER_RESTRICT, struct sched_param *COMPILER_RESTRICT);
int   pthread_attr_setschedparam(pthread_attr_t *COMPILER_RESTRICT, const struct sched_param *COMPILER_RESTRICT);

int   pthread_attr_getschedpolicy(const pthread_attr_t *COMPILER_RESTRICT, int *COMPILER_RESTRICT);
int   pthread_attr_setschedpolicy(pthread_attr_t *, int);

int   pthread_attr_getscope(const pthread_attr_t *COMPILER_RESTRICT, int *COMPILER_RESTRICT);
int   pthread_attr_setscope(pthread_attr_t *, int);

int   pthread_attr_getstack(const pthread_attr_t *COMPILER_RESTRICT, void **COMPILER_RESTRICT, size_t *COMPILER_RESTRICT);
int   pthread_attr_setstack(pthread_attr_t *, void *, size_t);

int   pthread_attr_getstackaddr(const pthread_attr_t *COMPILER_RESTRICT, void **COMPILER_RESTRICT);
int   pthread_attr_setstackaddr(pthread_attr_t *, void *);

int   pthread_attr_getstacksize(const pthread_attr_t *COMPILER_RESTRICT, size_t *COMPILER_RESTRICT);
int   pthread_attr_setstacksize(pthread_attr_t *, size_t);

 /* Non-standard attributes */
int   pthread_attr_getlcid_np(const pthread_attr_t *COMPILER_RESTRICT, int *COMPILER_RESTRICT);
int   pthread_attr_setlcid_np(pthread_attr_t *, int);

int   pthread_attr_getname_np(const pthread_attr_t* attr, char* name);
int   pthread_attr_setname_np(pthread_attr_t* attr, const char* name);

/* One time library initialization */
int   pthread_once(pthread_once_t *, void (*)(void));

/* Threads */
pthread_t pthread_self(void);
int   pthread_create(pthread_t *COMPILER_RESTRICT, const pthread_attr_t *COMPILER_RESTRICT, void *(*)(void *), void *COMPILER_RESTRICT);
int   pthread_detach(pthread_t);
int   pthread_equal(pthread_t, pthread_t);
void  pthread_exit(void *);
int   pthread_join(pthread_t, void **);
 /* Macro implementation */
#define pthread_equal(_x_, _y_)  ((_x_) == (_y_))

/* Cancelation */
int   pthread_cancel(pthread_t);
void  pthread_testcancel(void);

int   pthread_setcancelstate(int, int *);
int   pthread_setcanceltype(int, int *);

 /* Non-standard */
int   pthread_sleep_np(void);
int   pthread_timedsleep_np(const struct timespec*);
int   pthread_wakeup_np(pthread_t);

/* Thread CPU clock */
int   pthread_getcpuclockid(pthread_t, clockid_t *);

/* Thread scheduling */
int   pthread_getschedparam(pthread_t, int *COMPILER_RESTRICT, struct sched_param *COMPILER_RESTRICT);
int   pthread_setschedparam(pthread_t, int, const struct sched_param *);

int   pthread_getconcurrency(void);
int   pthread_setconcurrency(int);

int   pthread_setschedprio(pthread_t, int);

/* Thread-specific data */
int   pthread_key_create(pthread_key_t *, void (*)(void *));
int   pthread_key_delete(pthread_key_t);

void *pthread_getspecific(pthread_key_t);
int   pthread_setspecific(pthread_key_t, const void *);

/* Barriers */
int   pthread_barrierattr_init(pthread_barrierattr_t *);
int   pthread_barrierattr_destroy(pthread_barrierattr_t *);

int   pthread_barrierattr_getpshared(const pthread_barrierattr_t *COMPILER_RESTRICT, int *COMPILER_RESTRICT);
int   pthread_barrierattr_setpshared(pthread_barrierattr_t *, int);

int   pthread_barrier_init(pthread_barrier_t *COMPILER_RESTRICT, const pthread_barrierattr_t *COMPILER_RESTRICT, unsigned);
int   pthread_barrier_destroy(pthread_barrier_t *);

int   pthread_barrier_wait(pthread_barrier_t *);

/* Condition variables */
int   pthread_cond_destroy(pthread_cond_t *);
int   pthread_cond_init(pthread_cond_t *COMPILER_RESTRICT, const pthread_condattr_t *COMPILER_RESTRICT);

int   pthread_cond_signal(pthread_cond_t *);
int   pthread_cond_broadcast(pthread_cond_t *);

int   pthread_cond_wait(pthread_cond_t *COMPILER_RESTRICT, pthread_mutex_t *COMPILER_RESTRICT);
int   pthread_cond_timedwait(pthread_cond_t *COMPILER_RESTRICT, pthread_mutex_t *COMPILER_RESTRICT, const struct timespec *COMPILER_RESTRICT);

/* Condition attributes */
int   pthread_condattr_init(pthread_condattr_t *);
int   pthread_condattr_destroy(pthread_condattr_t *);

int   pthread_condattr_getclock(const pthread_condattr_t *COMPILER_RESTRICT, clockid_t *COMPILER_RESTRICT);
int   pthread_condattr_setclock(pthread_condattr_t *, clockid_t);

int   pthread_condattr_getpshared(const pthread_condattr_t *COMPILER_RESTRICT, int *COMPILER_RESTRICT);
int   pthread_condattr_setpshared(pthread_condattr_t *, int);

/* Mutexes */
int   pthread_mutex_init(pthread_mutex_t *COMPILER_RESTRICT, const pthread_mutexattr_t *COMPILER_RESTRICT);
int   pthread_mutex_destroy(pthread_mutex_t *);

int   pthread_mutex_getprioceiling(const pthread_mutex_t *COMPILER_RESTRICT, int *COMPILER_RESTRICT);
int   pthread_mutex_setprioceiling(pthread_mutex_t *COMPILER_RESTRICT, int, int *COMPILER_RESTRICT);

int   pthread_mutex_trylock(pthread_mutex_t *);
int   pthread_mutex_lock(pthread_mutex_t *);
int   pthread_mutex_timedlock(pthread_mutex_t *COMPILER_RESTRICT, const struct timespec *COMPILER_RESTRICT);
int   pthread_mutex_consistent(pthread_mutex_t *);
int   pthread_mutex_unlock(pthread_mutex_t *);

/* Mutex attributes */
int   pthread_mutexattr_init(pthread_mutexattr_t *);
int   pthread_mutexattr_destroy(pthread_mutexattr_t *);

int   pthread_mutexattr_getprotocol(const pthread_mutexattr_t *COMPILER_RESTRICT, int *COMPILER_RESTRICT);
int   pthread_mutexattr_setprotocol(pthread_mutexattr_t *, int);

int   pthread_mutexattr_getpshared(const pthread_mutexattr_t *COMPILER_RESTRICT, int *COMPILER_RESTRICT);
int   pthread_mutexattr_setpshared(pthread_mutexattr_t *, int);

int   pthread_mutexattr_gettype(const pthread_mutexattr_t *COMPILER_RESTRICT, int *COMPILER_RESTRICT);
int   pthread_mutexattr_settype(pthread_mutexattr_t *, int);

int   pthread_mutexattr_getrobust(const pthread_mutexattr_t *COMPILER_RESTRICT, int *COMPILER_RESTRICT);
int   pthread_mutexattr_setrobust(pthread_mutexattr_t *, int);

int   pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *COMPILER_RESTRICT, int *COMPILER_RESTRICT);
int   pthread_mutexattr_setprioceiling(pthread_mutexattr_t *, int);

/* Read-write locks */
int   pthread_rwlock_init(pthread_rwlock_t *COMPILER_RESTRICT, const pthread_rwlockattr_t *COMPILER_RESTRICT);
int   pthread_rwlock_destroy(pthread_rwlock_t *);

int   pthread_rwlock_tryrdlock(pthread_rwlock_t *);
int   pthread_rwlock_rdlock(pthread_rwlock_t *);
int   pthread_rwlock_timedrdlock(pthread_rwlock_t *COMPILER_RESTRICT, const struct timespec *COMPILER_RESTRICT);

int   pthread_rwlock_trywrlock(pthread_rwlock_t *);
int   pthread_rwlock_wrlock(pthread_rwlock_t *);
int   pthread_rwlock_timedwrlock(pthread_rwlock_t *COMPILER_RESTRICT, const struct timespec *COMPILER_RESTRICT);

int   pthread_rwlock_unlock(pthread_rwlock_t *);

/* Rwlock attributes */
int   pthread_rwlockattr_init(pthread_rwlockattr_t *);
int   pthread_rwlockattr_destroy(pthread_rwlockattr_t *);

int   pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *COMPILER_RESTRICT, int *COMPILER_RESTRICT);
int   pthread_rwlockattr_setpshared(pthread_rwlockattr_t *, int);

/* Spinlocks */
int   pthread_spin_init(pthread_spinlock_t *, int);
int   pthread_spin_destroy(pthread_spinlock_t *);
int   pthread_spin_trylock(pthread_spinlock_t *);
int   pthread_spin_lock(pthread_spinlock_t *);
int   pthread_spin_unlock(pthread_spinlock_t *);

/* Cleanup handlers */
struct _pthread_cleanup
{
    void                   (*_func_)(void*);
    void                    *_para_;
    struct _pthread_cleanup *_prev_;
};
extern void _pthread_cleanup_push(struct _pthread_cleanup*, void (*)(void *), void *);
extern void _pthread_cleanup_pop(struct _pthread_cleanup*, int);

#define pthread_cleanup_push(_func_, _para_) \
{                                            \
    struct _pthread_cleanup _data_;          \
    _pthread_cleanup_push(&_data_, _func_, _para_)

#define pthread_cleanup_pop(_exec_)          \
   _pthread_cleanup_pop(&_data_, _exec_);    \
}

#ifdef  __cplusplus
}
#endif

#endif /* __PTHREAD_H__ */
