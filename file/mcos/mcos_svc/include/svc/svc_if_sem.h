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
[svc_if_sem.h] - SVC interface library header (POSIX Semaphore)
****************************************************************************/

#ifndef SVC_IF_SEM_H
#define SVC_IF_SEM_H

#include <svc/svc_if.h>

/*
 * SVC Function ID
 */
#define SVCID_SEM_XXX			(SVCID_SEM | 0x00000000) /* Do not use bit31-16 */

#define SVCID_SEM_INIT			(SVCID_SEM | 0x00000001)
#define SVCID_SEM_DESTROY		(SVCID_SEM | 0x00000002)
#define SVCID_SEM_WAIT			(SVCID_SEM | 0x00000003)
#define SVCID_SEM_TIMEDWAIT		(SVCID_SEM | 0x00000004)
#define SVCID_SEM_TRYWAIT		(SVCID_SEM | 0x00000005)
#define SVCID_SEM_POST			(SVCID_SEM | 0x00000006)
#define SVCID_SEM_GETVALUE		(SVCID_SEM | 0x00000007)
#define SVCID_SEM_OPEN			(SVCID_SEM | 0x00000008)
#define SVCID_SEM_CLOSE			(SVCID_SEM | 0x00000009)
#define SVCID_SEM_UNLINK		(SVCID_SEM | 0x0000000a)

#ifndef _in_asm_source_

/*
 * SVC Parameter Packet
 */
#include <semaphore.h>
#include <time.h>

/* sem_init() */
typedef struct {
	int				id;
	sem_t			*sem;
	int				pshared;
	unsigned int	value;
} svc_packet_sem_init_t;

/* sem_destroy() */
typedef struct {
	int				id;
	sem_t			*sem;
} svc_packet_sem_destroy_t;

/* sem_wait() */
typedef struct {
	int				id;
	sem_t			*sem;
} svc_packet_sem_wait_t;

/* sem_timedwait() */
typedef struct {
	int						id;
	sem_t					*restrict sem;
	const struct timespec	*restrict abstime;
} svc_packet_sem_timedwait_t;

/* sem_trywait() */
typedef struct {
	int				id;
	sem_t			*sem;
} svc_packet_sem_trywait_t;

/* sem_post() */
typedef struct {
	int				id;
	sem_t			*sem;
} svc_packet_sem_post_t;

/* sem_getvalue() */
typedef struct {
	int				id;
	sem_t			*restrict sem;
	int				*restrict sval;
} svc_packet_sem_getvalue_t;

/* sem_open() */
typedef struct {
	int				id;
	const char		*name;
	int				oflag;
	mode_t			mode;
	unsigned int	value;
	sem_t			**sem;
} svc_packet_sem_open_t;

/* sem_close() */
typedef struct {
	int				id;
	sem_t			*sem;
} svc_packet_sem_close_t;

/* sem_unlink() */
typedef struct {
	int				id;
	const char		*name;
} svc_packet_sem_unlink_t;

/* List of POSIX Semaphore APIs */
typedef union {
	int							id;
	svc_packet_sem_init_t		param_sem_init_;
	svc_packet_sem_destroy_t	param_sem_destroy_;
	svc_packet_sem_wait_t		param_sem_wait_;
	svc_packet_sem_timedwait_t	param_sem_timedwait_;
	svc_packet_sem_trywait_t	param_sem_trywait_;
	svc_packet_sem_post_t		param_sem_post_;
	svc_packet_sem_getvalue_t	param_sem_getvalue_;
	svc_packet_sem_open_t		param_sem_open_;
	svc_packet_sem_close_t		param_sem_close_;
	svc_packet_sem_unlink_t		param_sem_unlink_;
} svc_packet_sem_t;

#endif /* _in_asm_source_ */

#endif	/* #ifndef SVC_IF_SEM_H */
