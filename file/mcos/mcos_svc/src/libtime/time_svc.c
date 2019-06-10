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
[time_svc.c] - SVC interface library (POSIX Clock/Time)
****************************************************************************/

#include <svc/svc_if.h>
#include <svc/svc_if_time.h>
#include <stdio.h>

clock_t clock(void)
{
	return (clock_t)-1;
}

/* nanosleep() API */
int nanosleep(const struct timespec *rqtp, struct timespec *rmtp)
{
	svc_packet_time_nanosleep_t	p;

	p.id		= SVCID_TIME_NANOSLEEP;
	p.rqtp		= rqtp;
	p.rmtp		= rmtp;
	return (int)call_svc((void*)&p);
}

/* sleep() API */
unsigned int sleep(unsigned int seconds)
{
	svc_packet_time_sleep_t	p;

	p.id		= SVCID_TIME_SLEEP;
	p.seconds	= seconds;
	return (unsigned int)call_svc((void*)&p);
}

/* clock_nanosleep() API */
int clock_nanosleep(clockid_t clock_id, int flags, const struct timespec *rqtp, struct timespec *rmtp)
{
	svc_packet_time_clock_nanosleep_t	p;

	p.id		= SVCID_TIME_CLOCK_NANOSLEEP;
	p.clock_id	= clock_id;
	p.flags		= flags;
	p.rqtp		= rqtp;
	p.rmtp		= rmtp;
	return (int)call_svc((void*)&p);
}

/* clock_getres() API */
int clock_getres(clockid_t clock_id, struct timespec *res)
{
	svc_packet_time_clock_getres_t	p;

	p.id		= SVCID_TIME_CLOCK_GETRES;
	p.clock_id	= clock_id;
	p.res		= res;
	return (int)call_svc((void*)&p);
}

/* clock_gettime() API */
int clock_gettime(clockid_t clock_id, struct timespec *tp)
{
	svc_packet_time_clock_gettime_t	p;

	p.id		= SVCID_TIME_CLOCK_GETTIME;
	p.clock_id	= clock_id;
	p.tp		= tp;
	return (int)call_svc((void*)&p);
}

/* clock_settime() API */
int clock_settime(clockid_t clock_id, const struct timespec *tp)
{
	svc_packet_time_clock_settime_t	p;

	p.id		= SVCID_TIME_CLOCK_SETTIME;
	p.clock_id	= clock_id;
	p.tp		= tp;
	return (int)call_svc((void*)&p);
}

/* clock_getcpuclockid() API */
int clock_getcpuclockid(pid_t pid, clockid_t *clock_id)
{
	svc_packet_time_clock_getcpuclockid_t	p;

	p.id		= SVCID_TIME_CLOCK_GETCPUCLOCKID;
	p.pid		= pid;
	p.clock_id	= clock_id;
	return (int)call_svc((void*)&p);
}

/* gettimeofday() API */
int gettimeofday(struct timeval * restrict tp, struct timezone * restrict zp)
{
	svc_packet_time_gettimeofday_t	p;

	p.id	= SVCID_TIME_GETTIMEOFDAY;
	p.tp	= tp;
	p.zp	= zp;
	return (int)call_svc((void*)&p);
}

#include <sys/times.h>
clock_t times(struct tms *buf)
{
    printf("times(): eMCOS does not support this POSIX API.\n");
    return -1;
}
