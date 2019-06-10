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
[pthread_cond_svc.c] - SVC interface library (POSIX Condition Variable)
****************************************************************************/

#include <svc/svc_if.h>
#include <svc/svc_if_pthread.h>

/* pthread_cond_init() API */
int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr)
{
    svc_packet_pthread_cond_init_t  p;

    p.id        = SVCID_PTHREAD_COND_INIT;
    p.cond      = cond;
    p.attr      = attr;

    return (int)call_svc((void*)&p);
}

/* pthread_cond_destroy() API */
int pthread_cond_destroy(pthread_cond_t *cond)
{
    svc_packet_pthread_cond_destroy_t   p;

    p.id        = SVCID_PTHREAD_COND_DESTROY;
    p.cond      = cond;

    return (int)call_svc((void*)&p);
}

/* pthread_cond_wait() API */
int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex)
{
    svc_packet_pthread_cond_wait_t  p;

    p.id        = SVCID_PTHREAD_COND_WAIT;
    p.cond      = cond;
    p.mutex     = mutex;

    return (int)call_svc((void*)&p);
}

/* pthread_cond_timedwait() API */
int pthread_cond_timedwait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime)
{
    svc_packet_pthread_cond_timedwait_t p;

    p.id        = SVCID_PTHREAD_COND_TIMEDWAIT;
    p.cond      = cond;
    p.mutex     = mutex;
    p.abstime   = abstime;

    return (int)call_svc((void*)&p);
}

/* pthread_cond_signal() API */
int pthread_cond_signal(pthread_cond_t *cond)
{
    svc_packet_pthread_cond_signal_t    p;

    p.id        = SVCID_PTHREAD_COND_SIGNAL;
    p.cond      = cond;

    return (int)call_svc((void*)&p);
}

/* pthread_cond_broadcast() API */
int pthread_cond_broadcast(pthread_cond_t *cond)
{
    svc_packet_pthread_cond_broadcast_t p;

    p.id        = SVCID_PTHREAD_COND_BROADCAST;
    p.cond      = cond;

    return (int)call_svc((void*)&p);
}
