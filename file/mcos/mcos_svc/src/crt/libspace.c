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
[libspace.c] -
****************************************************************************/

#include <stdint.h>
#include <errno.h>

#define LIBSPACE_NUM    24U

struct libspace
{
    unsigned long buff[LIBSPACE_NUM];
}; /* struct libspace */

struct libspace_thread
{
    struct libspace base;
}; /* struct libspace_thread */

struct libspace_proc
{
    struct libspace base;
}; /* struct libspace_proc */

/* libspace for thread */
static struct libspace_thread libspace_thread;

/* libspace for non-thread */
static struct libspace_thread libspace_nothread;

/* process local libspace */
static struct libspace_proc libspace_global;

#define ERRNO_SIZE      (1)
static unsigned int mcos_hwl_get_tsd_size(void)
{
    return ERRNO_SIZE;
}

/* Get size of TSD (in word size) */
unsigned int gettsdsize(void)
{
    return mcos_hwl_get_tsd_size();
}

/* Get pointer to extcb */
void * getextcbptr(void)
{
    void * p;
#if 1   /* defined THREAD_ID_REG_SUPPORT */
    extern void * __get_threadid2(void);
    p = __get_threadid2();
#endif  /* defined THREAD_ID_REG_SUPPORT */
    return p;
}

/* Get pointer to TSD */
void * gettsdptr(void)
{
    void * p;
    p = getextcbptr();
    if (p != 0)
    {
        p = (void*)((uintptr_t*)p - gettsdsize());
    }
    else
    {
        extern int *get_errno_addr(void);
        p = (void*)get_errno_addr();
    }
    return p;
}

void * __user_perthread_libspace(void)
{
    struct libspace_thread * libspace;
    void * p;

    p = gettsdptr();
    if (p == 0) {
        libspace = &libspace_nothread;
    } else {
        unsigned int size;

        size = sizeof(libspace_thread);
        size >>= 3; /* byte to long long */
        size -= LIBSPACE_NUM;
        libspace = (struct libspace_thread *)&((void * *)p)[size];
    }
    return libspace;
}

void * __user_perproc_libspace(void)
{
    return &libspace_global;
}

__attribute__((__const__))  __attribute__((__nothrow__)) volatile int *__aeabi_errno_addr(void)
{
    return &((int *)__user_perthread_libspace())[0];
}
