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
[pthread_barrier_svc.c] - SVC interface library (POSIX Barrier Synchronization)
****************************************************************************/

#include <svc/svc_if.h>
#include <svc/svc_if_pthread.h>

/* pthread_barrier_init() API */
int pthread_barrier_init(pthread_barrier_t *restrict barrier, const pthread_barrierattr_t *restrict attr, unsigned count)
{
    svc_packet_pthread_barrier_init_t   p;

    p.id        = SVCID_PTHREAD_BARRIER_INIT;
    p.barrier   = barrier;
    p.attr      = attr;
    p.count     = count;

    return (int)call_svc((void*)&p);
}

/* pthread_barrier_destroy() API */
int pthread_barrier_destroy(pthread_barrier_t *barrier)
{
    svc_packet_pthread_barrier_destroy_t    p;

    p.id        = SVCID_PTHREAD_BARRIER_DESTROY;
    p.barrier   = barrier;

    return (int)call_svc((void*)&p);
}

/* pthread_barrier_wait() API */
int pthread_barrier_wait(pthread_barrier_t *barrier)
{
    svc_packet_pthread_barrier_wait_t   p;

    p.id        = SVCID_PTHREAD_BARRIER_WAIT;
    p.barrier   = barrier;

    return (int)call_svc((void*)&p);
}
