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
[pthread_rwlock_svc.c] - SVC interface library (POSIX RWLock)
****************************************************************************/

#include <svc/svc_if.h>
#include <svc/svc_if_pthread.h>

/* pthread_rwlock_init() API */
int pthread_rwlock_init(pthread_rwlock_t* restrict rwlock, const pthread_rwlockattr_t* restrict attr)
{
    svc_packet_pthread_rwlock_init_t    p;

    p.id        = SVCID_PTHREAD_RWLOCK_INIT;
    p.rwlock    = rwlock;
    p.attr      = attr;

    return (int)call_svc((void*)&p);
}

/* pthread_rwlock_destroy() API */
int pthread_rwlock_destroy(pthread_rwlock_t* rwlock)
{
    svc_packet_pthread_rwlock_destroy_t p;

    p.id        = SVCID_PTHREAD_RWLOCK_DESTROY;
    p.rwlock    = rwlock;

    return (int)call_svc((void*)&p);
}

/* pthread_rwlock_rdlock() API */
int pthread_rwlock_rdlock(pthread_rwlock_t* rwlock)
{
    svc_packet_pthread_rwlock_rdlock_t  p;

    p.id        = SVCID_PTHREAD_RWLOCK_RDLOCK;
    p.rwlock    = rwlock;

    return (int)call_svc((void*)&p);
}

/* pthread_rwlock_timedrdlock() API */
int pthread_rwlock_timedrdlock(pthread_rwlock_t* restrict rwlock, const struct timespec* restrict abstime)
{
    svc_packet_pthread_rwlock_timedrdlock_t p;

    p.id        = SVCID_PTHREAD_RWLOCK_TIMEDRDLOCK;
    p.rwlock    = rwlock;
    p.abstime   = abstime;

    return (int)call_svc((void*)&p);
}

/* pthread_rwlock_tryrdlock() API */
int pthread_rwlock_tryrdlock(pthread_rwlock_t* rwlock)
{
    svc_packet_pthread_rwlock_tryrdlock_t   p;

    p.id        = SVCID_PTHREAD_RWLOCK_TRYRDLOCK;
    p.rwlock    = rwlock;

    return (int)call_svc((void*)&p);
}

/* pthread_rwlock_wrlock() API */
int pthread_rwlock_wrlock(pthread_rwlock_t* rwlock)
{
    svc_packet_pthread_rwlock_wrlock_t  p;

    p.id        = SVCID_PTHREAD_RWLOCK_WRLOCK;
    p.rwlock    = rwlock;

    return (int)call_svc((void*)&p);
}

/* pthread_rwlock_timedwrlock() API */
int pthread_rwlock_timedwrlock(pthread_rwlock_t* restrict rwlock, const struct timespec* restrict abstime)
{
    svc_packet_pthread_rwlock_timedwrlock_t p;

    p.id        = SVCID_PTHREAD_RWLOCK_TIMEDWRLOCK;
    p.rwlock    = rwlock;
    p.abstime   = abstime;

    return (int)call_svc((void*)&p);
}

/* pthread_rwlock_trywrlock() API */
int pthread_rwlock_trywrlock(pthread_rwlock_t* rwlock)
{
    svc_packet_pthread_rwlock_trywrlock_t   p;

    p.id        = SVCID_PTHREAD_RWLOCK_TRYWRLOCK;
    p.rwlock    = rwlock;

    return (int)call_svc((void*)&p);
}

/* pthread_rwlock_unlock() API */
int pthread_rwlock_unlock(pthread_rwlock_t* rwlock)
{
    svc_packet_pthread_rwlock_unlock_t  p;

    p.id        = SVCID_PTHREAD_RWLOCK_UNLOCK;
    p.rwlock    = rwlock;

    return (int)call_svc((void*)&p);
}
