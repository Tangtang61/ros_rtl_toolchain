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
[sem_svc.c] - SVC interface library (POSIX Semaphore)
****************************************************************************/

#include <svc/svc_if.h>

#define sem_open	__sem_open__	/* for variadic argument */
#include <svc/svc_if_sem.h>
#undef sem_open						/* for variadic argument */

/* sem_init() API */
int sem_init(sem_t *sem, int pshared, unsigned value)
{
	svc_packet_sem_init_t	p;

	p.id		= SVCID_SEM_INIT;
	p.sem		= sem;
	p.pshared	= pshared;
	p.value		= value;
	return (int)call_svc((void*)&p);
}

/* sem_destroy() API */
int sem_destroy(sem_t *sem)
{
	svc_packet_sem_destroy_t	p;

	p.id		= SVCID_SEM_DESTROY;
	p.sem		= sem;
	return (int)call_svc((void*)&p);
}

/* sem_wait() API */
int sem_wait(sem_t *sem)
{
	svc_packet_sem_wait_t	p;

	p.id		= SVCID_SEM_WAIT;
	p.sem		= sem;
	return (int)call_svc((void*)&p);
}

/* sem_timedwait() API */
int sem_timedwait(sem_t *restrict sem, const struct timespec *restrict abstime)
{
	svc_packet_sem_timedwait_t	p;

	p.id		= SVCID_SEM_TIMEDWAIT;
	p.sem		= sem;
	p.abstime	= abstime;
	return (int)call_svc((void*)&p);
}

/* sem_trywait() API */
int sem_trywait(sem_t *sem)
{
	svc_packet_sem_trywait_t	p;

	p.id		= SVCID_SEM_TRYWAIT;
	p.sem		= sem;
	return (int)call_svc((void*)&p);
}

/* sem_post() API */
int sem_post(sem_t *sem)
{
	svc_packet_sem_post_t	p;

	p.id		= SVCID_SEM_POST;
	p.sem		= sem;
	return (int)call_svc((void*)&p);
}

/* sem_getvalue() API */
int sem_getvalue(sem_t *restrict sem, int *restrict sval)
{
	svc_packet_sem_getvalue_t	p;

	p.id		= SVCID_SEM_GETVALUE;
	p.sem		= sem;
	p.sval		= sval;
	return (int)call_svc((void*)&p);
}

/* sem_open() API */
sem_t* sem_open(const char *name, int oflag, mode_t mode, unsigned int value)
{
	svc_packet_sem_open_t	p;
	sem_t	*sem;

	p.id		= SVCID_SEM_OPEN;
	p.name		= name;
	p.oflag		= oflag;
	p.mode		= mode;
	p.value		= value;
	p.sem		= &sem;
	(void)call_svc((void*)&p);
	return *p.sem;
}

/* sem_close() API */
int sem_close(sem_t *sem)
{
	svc_packet_sem_close_t	p;

	p.id		= SVCID_SEM_CLOSE;
	p.sem		= sem;
	return (int)call_svc((void*)&p);
}

/* sem_unlink() API */
int sem_unlink(const char *name)
{
	svc_packet_sem_unlink_t	p;

	p.id		= SVCID_SEM_UNLINK;
	p.name		= name;
	return (int)call_svc((void*)&p);
}
