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
[pthread_mutex_svc.c] - SVC interface library (POSIX Mutex)
****************************************************************************/

#include <svc/svc_if.h>
#include <svc/svc_if_pthread.h>

/* pthread_mutex_init() API */
int pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* restrict attr)
{
	svc_packet_pthread_mutex_init_t	p;

	p.id		= SVCID_PTHREAD_MUTEX_INIT;
	p.mutex		= mutex;
	p.attr		= attr;

	return (int)call_svc((void*)&p);
}

/* pthread_mutex_destroy() API */
int pthread_mutex_destroy(pthread_mutex_t* mutex)
{
	svc_packet_pthread_mutex_destroy_t	p;

	p.id		= SVCID_PTHREAD_MUTEX_DESTROY;
	p.mutex		= mutex;

	return (int)call_svc((void*)&p);
}

/* pthread_mutex_lock() API */
int pthread_mutex_lock(pthread_mutex_t* mutex)
{
	svc_packet_pthread_mutex_lock_t	p;

	p.id		= SVCID_PTHREAD_MUTEX_LOCK;
	p.mutex		= mutex;

	return (int)call_svc((void*)&p);
}

/* pthread_mutex_timedlock() API */
int pthread_mutex_timedlock(pthread_mutex_t* restrict mutex,
                            const struct timespec* restrict abstmo)
{
	svc_packet_pthread_mutex_timedlock_t	p;

	p.id		= SVCID_PTHREAD_MUTEX_TIMEDLOCK;
	p.mutex		= mutex;
	p.abstmo	= abstmo;

	return (int)call_svc((void*)&p);
}

/* pthread_mutex_trylock() API */
int pthread_mutex_trylock(pthread_mutex_t* mutex)
{
	svc_packet_pthread_mutex_trylock_t	p;

	p.id		= SVCID_PTHREAD_MUTEX_TRYLOCK;
	p.mutex		= mutex;

	return (int)call_svc((void*)&p);
}

/* pthread_mutex_unlock() API */
int pthread_mutex_unlock(pthread_mutex_t* mutex)
{
	svc_packet_pthread_mutex_unlock_t	p;

	p.id		= SVCID_PTHREAD_MUTEX_UNLOCK;
	p.mutex		= mutex;

	return (int)call_svc((void*)&p);
}

/* pthread_mutex_getprioceiling() API */
int pthread_mutex_getprioceiling(const pthread_mutex_t *restrict mutex,
                                   int *restrict ceil)
{
	svc_packet_pthread_mutex_getprioceiling_t	p;

	p.id		= SVCID_PTHREAD_MUTEX_GETPRIOCEILING;
	p.mutex		= mutex;
	p.ceil		= ceil;

	return (int)call_svc((void*)&p);
}

/* pthread_mutex_setprioceiling() API */
int pthread_mutex_setprioceiling(pthread_mutex_t *restrict mutex,
                                 int prio, int *restrict ceil)
{
	svc_packet_pthread_mutex_setprioceiling_t	p;

	p.id		= SVCID_PTHREAD_MUTEX_SETPRIOCEILING;
	p.mutex		= mutex;
	p.prio		= prio;
	p.ceil		= ceil;

	return (int)call_svc((void*)&p);
}

/* pthread_mutex_consistent() API */
int pthread_mutex_consistent(pthread_mutex_t *mutex)
{
	svc_packet_pthread_mutex_consistent_t	p;

	p.id		= SVCID_PTHREAD_MUTEX_CONSISTENT;
	p.mutex		= mutex;

	return (int)call_svc((void*)&p);
}
