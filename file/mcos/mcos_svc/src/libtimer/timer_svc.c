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
[timer_svc.c] - SVC interface library (POSIX Timer)
****************************************************************************/

#include <svc/svc_if.h>
#include <svc/svc_if_timer.h>

/* timer_create() API */
int timer_create(clockid_t clockid, struct sigevent *restrict event, timer_t *restrict timerid)
{
	svc_packet_timer_create_t	p;

	p.id		= SVCID_TIMER_CREATE;
	p.clockid	= clockid;
	p.event		= event;
	p.timerid	= timerid;
	return (int)call_svc((void*)&p);
}

/* timer_delete() API */
int timer_delete(timer_t timerid)
{
	svc_packet_timer_delete_t	p;

	p.id		= SVCID_TIMER_DELETE;
	p.timerid	= timerid;
	return (int)call_svc((void*)&p);
}

/* timer_gettime() API */
int timer_gettime(timer_t timerid, struct itimerspec* value)
{
	svc_packet_timer_gettime_t	p;

	p.id		= SVCID_TIMER_GETTIME;
	p.timerid	= timerid;
	p.value		= value;
	return (int)call_svc((void*)&p);
}

/* timer_settime() API */
int timer_settime(timer_t timerid, int flags, const struct itimerspec* value, struct itimerspec* old)
{
	svc_packet_timer_settime_t	p;

	p.id		= SVCID_TIMER_SETTIME;
	p.timerid	= timerid;
	p.flags     = flags;
	p.value     = value;
	p.old       = old;
	return (int)call_svc((void*)&p);
}

/* timer_getoverrun() API */
int timer_getoverrun(timer_t timerid)
{
	svc_packet_timer_getoverrun_t	p;

	p.id		= SVCID_TIMER_GETOVERRUN;
	p.timerid	= timerid;
	return (int)call_svc((void*)&p);
}
