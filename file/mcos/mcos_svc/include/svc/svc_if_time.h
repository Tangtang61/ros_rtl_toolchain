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
[svc_if_time.h] - SVC interface library header (POSIX Clock/Time)
****************************************************************************/

#ifndef SVC_IF_TIME_H
#define SVC_IF_TIME_H

#include <svc/svc_if.h>

/*
 * SVC Function ID
 */
#define SVCID_TIME_XXX					(SVCID_TIME | 0x00000000) /* Do not use bit31-16 */

#define SVCID_TIME_NANOSLEEP			(SVCID_TIME | 0x00000001)
#define SVCID_TIME_SLEEP				(SVCID_TIME | 0x00000002)
#define SVCID_TIME_CLOCK_NANOSLEEP		(SVCID_TIME | 0x00000003)
#define SVCID_TIME_CLOCK_GETRES			(SVCID_TIME | 0x00000004)
#define SVCID_TIME_CLOCK_GETTIME		(SVCID_TIME | 0x00000005)
#define SVCID_TIME_CLOCK_SETTIME		(SVCID_TIME | 0x00000006)
#define SVCID_TIME_CLOCK_GETCPUCLOCKID	(SVCID_TIME | 0x00000007)
#define SVCID_TIME_GETTIMEOFDAY			(SVCID_TIME | 0x00000008)

#ifndef _in_asm_source_

/*
 * SVC Parameter Packet
 */
#include <time.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/timeb.h>

/* nanosleep() */
typedef struct {
	int						id;
	const struct timespec	*rqtp;
	struct timespec			*rmtp;
} svc_packet_time_nanosleep_t;

/* sleep() */
typedef struct {
	int				id;
	unsigned int	seconds;
} svc_packet_time_sleep_t;

/* clock_nanosleep() */
typedef struct {
	int						id;
	clockid_t				clock_id;
	int						flags;
	const struct timespec	*rqtp;
	struct timespec			*rmtp;
} svc_packet_time_clock_nanosleep_t;

/* clock_getres() */
typedef struct {
	int						id;
	clockid_t				clock_id;
	struct timespec			*res;
} svc_packet_time_clock_getres_t;

/* clock_gettime() */
typedef struct {
	int						id;
	clockid_t				clock_id;
	struct timespec			*tp;
} svc_packet_time_clock_gettime_t;

/* clock_settime() */
typedef struct {
	int						id;
	clockid_t				clock_id;
	const struct timespec	*tp;
} svc_packet_time_clock_settime_t;

/* clock_getcpuclockid() */
typedef struct {
	int			id;
	pid_t		pid;
	clockid_t	*clock_id;
} svc_packet_time_clock_getcpuclockid_t;

/* gettimeofday() */
typedef struct {
	int				id;
	struct timeval	* restrict tp;
	struct timezone	* restrict zp;
} svc_packet_time_gettimeofday_t;

/* List of POSIX LFS APIs */
typedef union {
	int										id;
	svc_packet_time_nanosleep_t				param_time_nanosleep_;
	svc_packet_time_sleep_t					param_time_sleep_;
	svc_packet_time_clock_nanosleep_t		param_time_clock_nanosleep_;
	svc_packet_time_clock_getres_t			param_time_clock_getres_;
	svc_packet_time_clock_gettime_t			param_time_clock_gettime_;
	svc_packet_time_clock_settime_t			param_time_clock_settime_;
	svc_packet_time_clock_getcpuclockid_t	param_time_clock_getcpuclockid_;
	svc_packet_time_gettimeofday_t			param_time_gettimeofday_;
} svc_packet_time_t;

#endif /* _in_asm_source_ */

#endif	/* #ifndef SVC_IF_TIME_H */
