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

/*============================================================================
 mqueue.h   POSIX Layer   Message queue support definitions
============================================================================*/
#ifndef __MQUEUE_H__
#define __MQUEUE_H__

#if !defined COMPILER_RESTRICT
#if defined __cplusplus
#define COMPILER_RESTRICT
#else /* __cplusplus */
#define COMPILER_RESTRICT restrict
#endif /* __cplusplus */
#endif /* COMPILER_RESTRICT */

#include <sys/types.h>
#include <time.h>
#include <signal.h>

#ifdef  __cplusplus
extern  "C" {
#endif

/* Message queue descriptor type */
typedef int mqd_t;

 /* Message queue attributes */
struct mq_attr
{
    long    mq_flags;    /* Message queue flags */
    long    mq_maxmsg;   /* Maximum number of messages */
    long    mq_msgsize;  /* Maximum message size */
    long    mq_curmsgs;  /* Number of messages currently queued */
};

/* Prototypes */
int      mq_close(mqd_t);
int      mq_getattr(mqd_t, struct mq_attr *);
int      mq_notify(mqd_t, const struct sigevent *);
mqd_t    mq_open(const char *, int, ...);
ssize_t  mq_receive(mqd_t, char *, size_t, unsigned *);
int      mq_send(mqd_t, const char *, size_t, unsigned );
int      mq_setattr(mqd_t, const struct mq_attr *COMPILER_RESTRICT,
             struct mq_attr *COMPILER_RESTRICT);
ssize_t  mq_timedreceive(mqd_t, char *COMPILER_RESTRICT, size_t,
             unsigned *COMPILER_RESTRICT, const struct timespec *COMPILER_RESTRICT);
int      mq_timedsend(mqd_t, const char *, size_t, unsigned ,
             const struct timespec *);

int      mq_unlink(const char *);

#ifdef  __cplusplus
}
#endif

#endif /* __MQUEUE_H__ */
