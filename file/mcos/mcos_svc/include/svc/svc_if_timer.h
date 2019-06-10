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
[svc_if_timer.h] - SVC interface library header (POSIX Timer)
****************************************************************************/

#ifndef SVC_IF_TIMER_H
#define SVC_IF_TIMER_H

#include <svc/svc_if.h>

/*
 * SVC Function ID
 */
#define SVCID_TIMER_CREATE			(SVCID_TIMER | 0x00000000)
#define SVCID_TIMER_DELETE			(SVCID_TIMER | 0x00000001)
#define SVCID_TIMER_GETTIME			(SVCID_TIMER | 0x00000002)
#define SVCID_TIMER_SETTIME			(SVCID_TIMER | 0x00000003)
#define SVCID_TIMER_GETOVERRUN		(SVCID_TIMER | 0x00000004)

#ifndef _in_asm_source_

/*
 * SVC Parameter Packet
 */
#include <time.h>
#include <signal.h>
#include <unistd.h>

/* timer_create() */
typedef struct {
	int				id;
	clockid_t		clockid;
	struct sigevent	*event;
	timer_t			*timerid;
} svc_packet_timer_create_t;

/* timer_delete() */
typedef struct {
	int				id;
	timer_t			timerid;
} svc_packet_timer_delete_t;

/* timer_gettime() */
typedef struct {
	int					id;
	timer_t				timerid;
	struct itimerspec 	*value;
} svc_packet_timer_gettime_t;

/* timer_settime() */
typedef struct {
	int							id;
	timer_t						timerid;
	int							flags;
	const struct itimerspec 	*value;
	struct itimerspec			*old;
} svc_packet_timer_settime_t;

/* timer_getoverrun() */
typedef struct {
	int					id;
	timer_t				timerid;
} svc_packet_timer_getoverrun_t;

/* List of POSIX Timer APIs */
typedef union {
	int									id;
	svc_packet_timer_create_t			param_timer_create_;
	svc_packet_timer_delete_t			param_timer_delete_;
	svc_packet_timer_gettime_t			param_timer_gettime_;
	svc_packet_timer_settime_t			param_timer_settime_;
	svc_packet_timer_getoverrun_t		param_timer_getoverrun_;
} svc_packet_timer_t;

#endif /* _in_asm_source_ */

#endif	/* #ifndef SVC_IF_TIMER_H */
