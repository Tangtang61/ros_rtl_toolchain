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
[pthread_create_svc.c] - SVC interface library (POSIX Thread)
****************************************************************************/

#include <pt_api_impl.h>
#include <svc/svc_if.h>
#include <svc/svc_if_pthread.h>
#include <errno.h>

extern void* getextcbptr(void);
extern int pt_init_signal_entry(void);

/* Get own PT TCB from the process space */
pttcb_t* pt_get_pttcb(void)
{
    pttcb_t *pttcb;
    pttcb = getextcbptr();
    return pttcb;
}

/* Common PT thread entry for subthreads of a process */
void* pt_process_thread_entry(void *args)
{
    void    *(*start_routine)(void*);
    void    *arg;
    void    *ret;
    void    **param;

    /* Setup argument */
    param = (void**)args;
    start_routine = (void*(*)(void*))param[0];
    arg = (void*)param[1];

    /* Install signal handler entry */
    pt_init_signal_entry();

    /* Invoke user specified entry */
    ret = start_routine(arg);

    /* Exit thread */
    pthread_exit(ret);

    /* Never reach here */
    return ret;
}

/* pthread_create() API */
int pthread_create(pthread_t *restrict thread,
       const pthread_attr_t *restrict attr,
       void *(*start_routine)(void*), void *restrict arg)
{
    svc_packet_pthread_create_t p;

    p.id            = SVCID_PTHREAD_CREATE;
    p.thread        = thread;
    p.attr          = attr;
    p.start_routine = start_routine;
    p.arg           = arg;

    if (!p.attr) {
        pthread_attr_t default_attr;
        pthread_attr_init(&default_attr);
        p.attr = &default_attr;
        int r = (int)call_svc((void*)&p);
        pthread_attr_destroy(&default_attr);
        return r;
    } else {
        return (int)call_svc((void*)&p);
    }
}

/* pthread_exit() API */
void pthread_exit(void *value_ptr)
{
    svc_packet_pthread_exit_t   p;

    p.id            = SVCID_PTHREAD_EXIT;
    p.value_ptr     = value_ptr;

    (void)call_svc((void*)&p);
    return;
}

/* pthread_join() API */
int pthread_join(pthread_t thread, void **value_ptr)
{
    svc_packet_pthread_join_t   p;

    p.id            = SVCID_PTHREAD_JOIN;
    p.thread        = thread;
    p.value_ptr     = value_ptr;

    return (int)call_svc((void*)&p);
}

/* pthread_self() API */
static pthread_t _pthread_self(void)
{
    svc_packet_pthread_self_t   p;

    p.id            = SVCID_PTHREAD_SELF;

    return (pthread_t)call_svc((void*)&p);
}

pthread_t pthread_self(void)
{
    pthread_t   tid;
    pttcb_t     *pttcb;

    pttcb = pt_get_pttcb();
    if (pttcb != 0)
    {
        tid = pttcb->pthrid;
    }
    else
    {
        tid = _pthread_self();
    }
    return tid;
}

int pt_once_locked(uint32_t once)
{
    svc_packet_pt_once_locked_t p;

    p.id    = SVCID_PT_ONCE_LOCKED;
    p.once  = once;

    return (int)call_svc((void*)&p);
}

int pt_once_finish(uint32_t once)
{
    svc_packet_pt_once_finish_t p;

    p.id    = SVCID_PT_ONCE_FINISH;
    p.once  = once;

    return (int)call_svc((void*)&p);
}

int pthread_detach(pthread_t thread)
{
    svc_packet_pthread_detach_t p;

    p.id            = SVCID_PTHREAD_DETACH;
    p.thread        = thread;

    return (int)call_svc((void*)&p);
}

int sched_yield(void)
{
    svc_packet_sched_yield_t    p;

    p.id            = SVCID_SCHED_YIELD;

    return (int)call_svc((void*)&p);
}

int pthread_key_create(pthread_key_t *key, void (*destructor)(void*))
{
    svc_packet_pthread_key_create_t p;

    p.id            = SVCID_PTHREAD_KEY_CREATE;
    p.key           = key;
    p.destructor    = destructor;

    return (int)call_svc((void*)&p);
}

int pthread_key_delete(pthread_key_t key)
{
    svc_packet_pthread_key_delete_t p;

    p.id            = SVCID_PTHREAD_KEY_DELETE;
    p.key           = key;

    return (int)call_svc((void*)&p);
}

void* pthread_getspecific(pthread_key_t key)
{
    svc_packet_pthread_getspecific_t    p;
    void    *value;

    p.id            = SVCID_PTHREAD_GETSPECIFIC;
    p.key           = key;
    p.value         = &value;

    (void)call_svc((void*)&p);
    return *p.value;
}

int pthread_setspecific(pthread_key_t key, const void *value)
{
    svc_packet_pthread_setspecific_t    p;

    p.id            = SVCID_PTHREAD_SETSPECIFIC;
    p.key           = key;
    p.value         = value;

    return (int)call_svc((void*)&p);
}

int pthread_getschedparam(pthread_t thread, int *restrict policy, struct sched_param *restrict param)
{
    svc_packet_pthread_getschedparam_t    p;

    p.id        = SVCID_PTHREAD_GETSCHEDPARAM;
    p.thread    = thread;
    p.policy    = policy;
    p.param     = param;

    return (int)call_svc((void*)&p);
}

int pthread_setschedparam(pthread_t thread, int policy, const struct sched_param *param)
{
    svc_packet_pthread_setschedparam_t  p;

    p.id        = SVCID_PTHREAD_SETSCHEDPARAM;
    p.thread    = thread;
    p.policy    = policy;
    p.param     = param;

    return (int)call_svc((void*)&p);
}

int pthread_setschedprio(pthread_t thread, int prio)
{
    svc_packet_pthread_setschedprio_t   p;

    p.id        = SVCID_PTHREAD_SETSCHEDPRIO;
    p.thread    = thread;
    p.prio      = prio;

    return (int)call_svc((void*)&p);
}

int pthread_sleep_np(void)
{
    svc_packet_pthread_sleep_np_t   p;

    p.id    = SVCID_PTHREAD_SLEEP_NP;

    return (int)call_svc((void*)&p);
}

int pthread_timedsleep_np(const struct timespec* tspec)
{
    svc_packet_pthread_timedsleep_np_t  p;

    p.id    = SVCID_PTHREAD_TIMEDSLEEP_NP;
    p.tspec = tspec;

    return (int)call_svc((void*)&p);
}

int pthread_wakeup_np(pthread_t tid)
{
    svc_packet_pthread_wakeup_np_t  p;

    p.id    = SVCID_PTHREAD_WAKEUP_NP;
    p.tid   = tid;

    return (int)call_svc((void*)&p);
}

int pthread_cancel(pthread_t thread)
{
    svc_packet_pthread_cancel_t  p;

    p.id        = SVCID_PTHREAD_CANCEL;
    p.thread    = thread;

    return (int)call_svc((void*)&p);
}
