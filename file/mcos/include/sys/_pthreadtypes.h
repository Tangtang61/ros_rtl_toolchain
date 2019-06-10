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
 sys/_pthreadtypes.h
============================================================================*/

#ifndef _SYS__PTHREADTYPES_H_
#define _SYS__PTHREADTYPES_H_

#include <sys/lock.h>
#include <sys/sched.h>

#define PTHREAD_NAME_MAX  (16)

/* Used to identify a thread */
typedef signed short    pthread_t;

/* Thread attributes */
typedef struct _pthread_attr
{
    unsigned int        attr[2]; /* Attr, lcid, stack size */
    void*               addr;    /* Stack address */
    char                name[PTHREAD_NAME_MAX]; /* optional thread name */
} pthread_attr_t;

/* Condvar userspace structure */
typedef struct _pthread_cond 
{
    unsigned int        value; /* Condvar value */
    pthread_mutex_t*    mutex; /* Condvar-related mutex */
} pthread_cond_t;

/* Used to identify a condition attribute object */
typedef unsigned int    pthread_condattr_t;

/* Used for thread-specific data keys */
typedef unsigned int    pthread_key_t;

/* User space once structure */
typedef struct _pthread_once 
{
    unsigned int value;
} pthread_once_t;

/* Barrier user space structure */
typedef struct _pthread_barrier 
{
    unsigned int value; /* Barrier value */
} pthread_barrier_t;

/* Used to define a barrier attributes object */
typedef unsigned int    pthread_barrierattr_t;

/* Used to identify a spin lock */
typedef unsigned int    pthread_spinlock_t;     

/* User space rwlock structure */
typedef struct _pthread_rwlock 
{
    unsigned int value;
} pthread_rwlock_t;

/* Used for read-write lock attributes */
typedef unsigned int pthread_rwlockattr_t;

#endif /* _SYS__PTHREADTYPES_H_ */
