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
 sys/pthread_mutex.h
============================================================================*/

#ifndef _SYS_PTHREAD_MUTEX_H_
#define _SYS_PTHREAD_MUTEX_H_
#if defined(_POSIX_THREADS) || __POSIX_VISIBLE >= 199506

/* Mutex user space structure */
typedef union _pthread_mutex_info
{
    unsigned int data;
    struct {
        unsigned short  ownerid;    /* Onwner thread id */
        unsigned char   savepri;    /* Saved owner priority */
        unsigned char   counter;    /* Recursive counter */
    } member;
} pthread_mutex_info_t;

typedef struct _pthread_mutex
{
    unsigned int        value;      /* Mutex value */
    pthread_mutex_info_t    info;   /* Mutex object information */
    void*               robust;     /* Owned robust mutexes list */
} pthread_mutex_t;

typedef unsigned int    pthread_mutexattr_t;    /* Used to identify a mutex attribute object */

#define PTHREAD_MUTEX_INITIALIZER {0}
#endif /* defined(_POSIX_THREADS) || __POSIX_VISIBLE >= 199506 */
#endif /* _SYS_PTHREAD_MUTEX_H_*/
