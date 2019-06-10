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

/****************************************************************************
[svc_if_pthread.h] - SVC interface library header (POSIX Thread)
****************************************************************************/

#ifndef SVC_IF_PTHREAD_H
#define SVC_IF_PTHREAD_H

#include <svc/svc_if.h>

/*
 * SVC Function ID
 */
#define SVCID_PTHREAD_CREATE                (SVCID_PTHREAD | 0x00000000)
#define SVCID_PTHREAD_EXIT                  (SVCID_PTHREAD | 0x00000001)
#define SVCID_PTHREAD_JOIN                  (SVCID_PTHREAD | 0x00000002)
#define SVCID_PTHREAD_SELF                  (SVCID_PTHREAD | 0x00000003)
#define SVCID_PTHREAD_DETACH                (SVCID_PTHREAD | 0x00000004)
#define SVCID_SCHED_YIELD                   (SVCID_PTHREAD | 0x00000005)
#define SVCID_PTHREAD_KEY_CREATE            (SVCID_PTHREAD | 0x00000006)
#define SVCID_PTHREAD_KEY_DELETE            (SVCID_PTHREAD | 0x00000007)
#define SVCID_PTHREAD_GETSPECIFIC           (SVCID_PTHREAD | 0x00000008)
#define SVCID_PTHREAD_SETSPECIFIC           (SVCID_PTHREAD | 0x00000009)
#define SVCID_PTHREAD_GETSCHEDPARAM         (SVCID_PTHREAD | 0x0000000a)
#define SVCID_PTHREAD_SETSCHEDPARAM         (SVCID_PTHREAD | 0x0000000b)
#define SVCID_PTHREAD_SETSCHEDPRIO          (SVCID_PTHREAD | 0x0000000c)
#define SVCID_PTHREAD_SLEEP_NP              (SVCID_PTHREAD | 0x0000000d)
#define SVCID_PTHREAD_TIMEDSLEEP_NP         (SVCID_PTHREAD | 0x0000000e)
#define SVCID_PTHREAD_WAKEUP_NP             (SVCID_PTHREAD | 0x0000000f)
#define SVCID_PTHREAD_CANCEL                (SVCID_PTHREAD | 0x00000010)
#define SVCID_PT_ONCE_LOCKED                (SVCID_PTHREAD | 0x00000011)
#define SVCID_PT_ONCE_FINISH                (SVCID_PTHREAD | 0x00000012)
#define SVCID_PTHREAD_MUTEX_INIT            (SVCID_PTHREAD | 0x00000013)
#define SVCID_PTHREAD_MUTEX_DESTROY         (SVCID_PTHREAD | 0x00000014)
#define SVCID_PTHREAD_MUTEX_LOCK            (SVCID_PTHREAD | 0x00000015)
#define SVCID_PTHREAD_MUTEX_TIMEDLOCK       (SVCID_PTHREAD | 0x00000016)
#define SVCID_PTHREAD_MUTEX_TRYLOCK         (SVCID_PTHREAD | 0x00000017)
#define SVCID_PTHREAD_MUTEX_UNLOCK          (SVCID_PTHREAD | 0x00000018)
#define SVCID_PTHREAD_MUTEX_GETPRIOCEILING  (SVCID_PTHREAD | 0x00000019)
#define SVCID_PTHREAD_MUTEX_SETPRIOCEILING  (SVCID_PTHREAD | 0x0000001a)
#define SVCID_PTHREAD_MUTEX_CONSISTENT      (SVCID_PTHREAD | 0x0000001b)
#define SVCID_PTHREAD_RWLOCK_INIT           (SVCID_PTHREAD | 0x0000001c)
#define SVCID_PTHREAD_RWLOCK_DESTROY        (SVCID_PTHREAD | 0x0000001d)
#define SVCID_PTHREAD_RWLOCK_RDLOCK         (SVCID_PTHREAD | 0x0000001e)
#define SVCID_PTHREAD_RWLOCK_TIMEDRDLOCK    (SVCID_PTHREAD | 0x0000001f)
#define SVCID_PTHREAD_RWLOCK_TRYRDLOCK      (SVCID_PTHREAD | 0x00000020)
#define SVCID_PTHREAD_RWLOCK_WRLOCK         (SVCID_PTHREAD | 0x00000021)
#define SVCID_PTHREAD_RWLOCK_TIMEDWRLOCK    (SVCID_PTHREAD | 0x00000022)
#define SVCID_PTHREAD_RWLOCK_TRYWRLOCK      (SVCID_PTHREAD | 0x00000023)
#define SVCID_PTHREAD_RWLOCK_UNLOCK         (SVCID_PTHREAD | 0x00000024)
#define SVCID_PTHREAD_COND_INIT             (SVCID_PTHREAD | 0x00000025)
#define SVCID_PTHREAD_COND_DESTROY          (SVCID_PTHREAD | 0x00000026)
#define SVCID_PTHREAD_COND_WAIT             (SVCID_PTHREAD | 0x00000027)
#define SVCID_PTHREAD_COND_TIMEDWAIT        (SVCID_PTHREAD | 0x00000028)
#define SVCID_PTHREAD_COND_SIGNAL           (SVCID_PTHREAD | 0x00000029)
#define SVCID_PTHREAD_COND_BROADCAST        (SVCID_PTHREAD | 0x0000002a)
#define SVCID_PTHREAD_BARRIER_INIT          (SVCID_PTHREAD | 0x0000002b)
#define SVCID_PTHREAD_BARRIER_DESTROY       (SVCID_PTHREAD | 0x0000002c)
#define SVCID_PTHREAD_BARRIER_WAIT          (SVCID_PTHREAD | 0x0000002d)

#ifndef _in_asm_source_

/*
 * SVC Parameter Packet
 */
#include <pthread.h>
#include <sched.h>

/* pthread_create() */
typedef struct {
    int         id;
    pthread_t *restrict thread;
    const pthread_attr_t *restrict attr;
    void *(*start_routine)(void*);
    void *restrict arg;
} svc_packet_pthread_create_t;

/* pthread_exit() */
typedef struct {
    int         id;
    void *value_ptr;
} svc_packet_pthread_exit_t;

/* pthread_join() */
typedef struct {
    int         id;
    pthread_t thread;
    void **value_ptr;
} svc_packet_pthread_join_t;

/* pthread_self() */
typedef struct {
    int         id;
} svc_packet_pthread_self_t;

/* pthread_once() helper : pt_once_locked() */
typedef struct {
    int         id;
    uint32_t    once;
} svc_packet_pt_once_locked_t;

/* pthread_once() helper : pt_once_finish() */
typedef struct {
    int         id;
    uint32_t    once;
} svc_packet_pt_once_finish_t;

/* pthread_detach() */
typedef struct {
    int             id;
    pthread_t   thread;
} svc_packet_pthread_detach_t;

/* sched_yield() */
typedef struct {
    int             id;
} svc_packet_sched_yield_t;

/* pthread_key_create() */
typedef struct {
    int             id;
    pthread_key_t   *key;
    void            (*destructor)(void*);
} svc_packet_pthread_key_create_t;

/* pthread_key_delete() */
typedef struct {
    int             id;
    pthread_key_t   key;
} svc_packet_pthread_key_delete_t;

/* pthread_getspecific() */
typedef struct {
    int             id;
    pthread_key_t   key;
    void            **value;
} svc_packet_pthread_getspecific_t;

/* pthread_setspecific() */
typedef struct {
    int             id;
    pthread_key_t   key;
    const void      *value;
} svc_packet_pthread_setspecific_t;

/* pthread_getschedparam() */
typedef struct {
    int                 id;
    pthread_t           thread;
    int                 *restrict policy;
    struct sched_param  *restrict param;
} svc_packet_pthread_getschedparam_t;

/* pthread_setschedparam() */
typedef struct {
    int                         id;
    pthread_t                   thread;
    int                         policy;
    const struct sched_param    *param;
} svc_packet_pthread_setschedparam_t;

/* pthread_setschedprio() */
typedef struct {
    int             id;
    pthread_t       thread;
    int             prio;
} svc_packet_pthread_setschedprio_t;

/* pthread_sleep_np() */
typedef struct {
    int                     id;
} svc_packet_pthread_sleep_np_t;

/* pthread_timedsleep_np() */
typedef struct {
    int                     id;
    const struct timespec   *tspec;
} svc_packet_pthread_timedsleep_np_t;

/* pthread_wakeup_np() */
typedef struct {
    int                     id;
    pthread_t               tid;
} svc_packet_pthread_wakeup_np_t;

/* pthread_cancel() */
typedef struct {
    int             id;
    pthread_t       thread;
} svc_packet_pthread_cancel_t;

/* pthread_mutex_init() */
typedef struct {
    int         id;
    pthread_mutex_t* mutex;
    const pthread_mutexattr_t* restrict attr;
} svc_packet_pthread_mutex_init_t;

/* pthread_mutex_destroy() */
typedef struct {
    int         id;
    pthread_mutex_t* mutex;
} svc_packet_pthread_mutex_destroy_t;

/* pthread_mutex_lock() */
typedef struct {
    int         id;
    pthread_mutex_t* mutex;
} svc_packet_pthread_mutex_lock_t;

/* pthread_mutex_timedlock() */
typedef struct {
    int         id;
    pthread_mutex_t* restrict mutex;
    const struct timespec* restrict abstmo;
} svc_packet_pthread_mutex_timedlock_t;

/* pthread_mutex_trylock() */
typedef struct {
    int         id;
    pthread_mutex_t* mutex;
} svc_packet_pthread_mutex_trylock_t;

/* pthread_mutex_unlock() */
typedef struct {
    int         id;
    pthread_mutex_t* mutex;
} svc_packet_pthread_mutex_unlock_t;

/* pthread_mutex_getprioceiling() */
typedef struct {
    int         id;
    const pthread_mutex_t *restrict mutex;
    int *restrict ceil;
} svc_packet_pthread_mutex_getprioceiling_t;

/* pthread_mutex_setprioceiling() */
typedef struct {
    int         id;
    pthread_mutex_t *restrict mutex;
    int prio;
    int *restrict ceil;
} svc_packet_pthread_mutex_setprioceiling_t;

/* pthread_mutex_consistent() */
typedef struct {
    int         id;
    pthread_mutex_t *mutex;
} svc_packet_pthread_mutex_consistent_t;

/* pthread_rwlock_init() */
typedef struct {
    int                         id;
    pthread_rwlock_t            *restrict rwlock;
    const pthread_rwlockattr_t  *restrict attr;
} svc_packet_pthread_rwlock_init_t;

/* pthread_rwlock_destroy() */
typedef struct {
    int                     id;
    pthread_rwlock_t        *rwlock;
} svc_packet_pthread_rwlock_destroy_t;

/* pthread_rwlock_rdlock() */
typedef struct {
    int                     id;
    pthread_rwlock_t        *rwlock;
} svc_packet_pthread_rwlock_rdlock_t;

/* pthread_rwlock_timedrdlock() */
typedef struct {
    int                     id;
    pthread_rwlock_t        *restrict rwlock;
    const struct timespec   *restrict abstime;
} svc_packet_pthread_rwlock_timedrdlock_t;

/* pthread_rwlock_tryrdlock() */
typedef struct {
    int                     id;
    pthread_rwlock_t        *rwlock;
} svc_packet_pthread_rwlock_tryrdlock_t;

/* pthread_rwlock_wrlock() */
typedef struct {
    int                     id;
    pthread_rwlock_t        *rwlock;
} svc_packet_pthread_rwlock_wrlock_t;

/* pthread_rwlock_timedwrlock() */
typedef struct {
    int                     id;
    pthread_rwlock_t        *restrict rwlock;
    const struct timespec   *restrict abstime;
} svc_packet_pthread_rwlock_timedwrlock_t;

/* pthread_rwlock_trywrlock() */
typedef struct {
    int                     id;
    pthread_rwlock_t        *rwlock;
} svc_packet_pthread_rwlock_trywrlock_t;

/* pthread_rwlock_unlock() */
typedef struct {
    int                     id;
    pthread_rwlock_t        *rwlock;
} svc_packet_pthread_rwlock_unlock_t;

/* pthread_cond_init() */
typedef struct {
    int                         id;
    pthread_cond_t              *restrict cond;
    const pthread_condattr_t    *restrict attr;
} svc_packet_pthread_cond_init_t;

/* pthread_cond_destroy() */
typedef struct {
    int                     id;
    pthread_cond_t          *cond;
} svc_packet_pthread_cond_destroy_t;

/* pthread_cond_wait() */
typedef struct {
    int                     id;
    pthread_cond_t          *restrict cond;
    pthread_mutex_t         *restrict mutex;
} svc_packet_pthread_cond_wait_t;

/* pthread_cond_timedwait() */
typedef struct {
    int                     id;
    pthread_cond_t          *restrict cond;
    pthread_mutex_t         *restrict mutex;
    const struct timespec   *restrict abstime;
} svc_packet_pthread_cond_timedwait_t;

/* pthread_cond_signal() */
typedef struct {
    int                     id;
    pthread_cond_t          *cond;
} svc_packet_pthread_cond_signal_t;

/* pthread_cond_broadcast() */
typedef struct {
    int                     id;
    pthread_cond_t          *cond;
} svc_packet_pthread_cond_broadcast_t;

/* pthread_barrier_init() */
typedef struct {
    int                         id;
    pthread_barrier_t           *restrict barrier;
    const pthread_barrierattr_t *restrict attr;
    unsigned int                count;
} svc_packet_pthread_barrier_init_t;

/* pthread_barrier_destroy() */
typedef struct {
    int                         id;
    pthread_barrier_t           *barrier;
} svc_packet_pthread_barrier_destroy_t;

/* pthread_barrier_wait() */
typedef struct {
    int                         id;
    pthread_barrier_t           *barrier;
} svc_packet_pthread_barrier_wait_t;

/* List of POSIX LFS APIs */
typedef union {
    int                     id;

    svc_packet_pthread_create_t                     param_pthread_create_;
    svc_packet_pthread_exit_t                       param_pthread_exit_;
    svc_packet_pthread_join_t                       param_pthread_join_;
    svc_packet_pthread_self_t                       param_pthread_self_;
    svc_packet_pt_once_locked_t                     param_pt_once_locked_;
    svc_packet_pt_once_finish_t                     param_pt_once_finish_;
    svc_packet_pthread_detach_t                     param_pthread_detach_;
    svc_packet_sched_yield_t                        param_sched_yield_;
    svc_packet_pthread_key_create_t                 param_pthread_key_create_;
    svc_packet_pthread_key_delete_t                 param_pthread_key_delete_;
    svc_packet_pthread_getspecific_t                param_pthread_getspecific_;
    svc_packet_pthread_setspecific_t                param_pthread_setspecific_;
    svc_packet_pthread_getschedparam_t              param_pthread_getschedparam_;
    svc_packet_pthread_setschedparam_t              param_pthread_setschedparam_;
    svc_packet_pthread_setschedprio_t               param_pthread_setschedprio_;
    svc_packet_pthread_sleep_np_t                   param_pthread_sleep_np_;
    svc_packet_pthread_timedsleep_np_t              param_pthread_timedsleep_np_;
    svc_packet_pthread_wakeup_np_t                  param_pthread_wakeup_np_;
    svc_packet_pthread_mutex_init_t                 param_pthread_mutex_init_;
    svc_packet_pthread_mutex_destroy_t              param_pthread_mutex_destroy_;
    svc_packet_pthread_mutex_lock_t                 param_pthread_mutex_lock_;
    svc_packet_pthread_mutex_timedlock_t            param_pthread_mutex_timedlock_;
    svc_packet_pthread_mutex_trylock_t              param_pthread_mutex_trylock_;
    svc_packet_pthread_mutex_unlock_t               param_pthread_mutex_unlock_;
    svc_packet_pthread_mutex_getprioceiling_t       param_pthread_mutex_getprioceiling_;
    svc_packet_pthread_mutex_setprioceiling_t       param_pthread_mutex_setprioceiling_;
    svc_packet_pthread_mutex_consistent_t           param_pthread_mutex_consistent_;
    svc_packet_pthread_rwlock_init_t                param_pthread_rwlock_init_;
    svc_packet_pthread_rwlock_destroy_t             param_pthread_rwlock_destroy_;
    svc_packet_pthread_rwlock_rdlock_t              param_pthread_rwlock_rdlock_;
    svc_packet_pthread_rwlock_timedrdlock_t         param_pthread_rwlock_timedrdlock_;
    svc_packet_pthread_rwlock_tryrdlock_t           param_pthread_rwlock_tryrdlock_;
    svc_packet_pthread_rwlock_wrlock_t              param_pthread_rwlock_wrlock_;
    svc_packet_pthread_rwlock_timedwrlock_t         param_pthread_rwlock_timedwrlock_;
    svc_packet_pthread_rwlock_trywrlock_t           param_pthread_rwlock_trywrlock_;
    svc_packet_pthread_rwlock_unlock_t              param_pthread_rwlock_unlock_;
    svc_packet_pthread_cond_init_t                  param_pthread_cond_init_;
    svc_packet_pthread_cond_destroy_t               param_pthread_cond_destroy_;
    svc_packet_pthread_cond_wait_t                  param_pthread_cond_wait_;
    svc_packet_pthread_cond_timedwait_t             param_pthread_cond_timedwait_;
    svc_packet_pthread_cond_signal_t                param_pthread_cond_signal_;
    svc_packet_pthread_cond_broadcast_t             param_pthread_cond_broadcast_;
    svc_packet_pthread_barrier_init_t               param_pthread_barrier_init_;
    svc_packet_pthread_barrier_destroy_t            param_pthread_barrier_destroy_;
    svc_packet_pthread_barrier_wait_t               param_pthread_barrier_wait_;
} svc_packet_pthread_t;

#endif /* _in_asm_source_ */

#endif  /* #ifndef SVC_IF_PTHREAD_H */
