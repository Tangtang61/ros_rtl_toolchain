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
[clib_mutex.c] - Compiler support library (mutex based exclusive control)
****************************************************************************/

#include <pt_api_impl.h>

int _libc_lock_error = 0;   /* imported from crtarmclang/mutex_stub.c */

#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <limits.h>
#include <errno.h>

#define POSIX_CLIB_MUTEX_MAX    (OPEN_MAX + 8)
static pthread_mutex_t*         _clib_mutexes[POSIX_CLIB_MUTEX_MAX] = {0};
static pthread_mutex_t          _clib_mutex = PTHREAD_MUTEX_INITIALIZER;
static unsigned int             _mutex_shared;

extern char __process__ __attribute__ ((weak));

static int _clib_mutex_is_usable(void)
{
    /* _mutex_initialize() maybe called before system initialization */
    extern int _clib_malloc_initialized __attribute__ ((weak));
    int is_usable;
    if (&_clib_malloc_initialized == 0)
    {
        is_usable = 1;
    }
    else
    {
        is_usable = (_clib_malloc_initialized != 0 ? 1 : 0);
    }
    return is_usable;
}

static int _clib_mutex_init(void)
{
    pthread_mutexattr_t attr;

    if(&__process__ == 0)
    {
        _mutex_shared = PTHREAD_PROCESS_SHARED;
    }
    else
    {
        _mutex_shared = PTHREAD_PROCESS_PRIVATE;
    }

    (void)pthread_mutexattr_init(&attr);
    (void)pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_NORMAL);
    (void)pthread_mutexattr_setpshared(&attr, _mutex_shared);
    (void)pthread_mutex_init(&_clib_mutex, &attr);
    return 0;
}

static int _clib_mutex_fini(void)
{
    (void)pthread_mutex_destroy(&_clib_mutex);
    return 0;
}

static int _clib_mutex_lock(void)
{
    return pthread_mutex_lock(&_clib_mutex);
}

static int _clib_mutex_unlock(void)
{
    return pthread_mutex_unlock(&_clib_mutex);
}

static pthread_mutex_t* _clib_mutex_get(int* mut)
{
    unsigned int        index;
    pthread_mutex_t*    mutex;

    mutex = 0;
    if (_clib_mutex_is_usable() != 0)
    {
        if (*mut == 0)
        {
            _clib_mutex_lock();
            for (index = 0; index < POSIX_CLIB_MUTEX_MAX; index++)
            {
                if (_clib_mutexes[index] == 0)
                {
                    mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
                    if (mutex != 0)
                    {
                        _clib_mutexes[index] = mutex;
                        *mut = (int)(index + 1);
                    }
                    break;
                }
            }
            _clib_mutex_unlock();
        }
        else
        {
            index = (unsigned int)(*mut - 1);
            if (index < POSIX_CLIB_MUTEX_MAX)
            {
                mutex = _clib_mutexes[index];
            }
        }
    }

    return mutex;
}

static int _clib_mutex_rel(int* mut)
{
    int                 sta;
    unsigned int        index;
    pthread_mutex_t*    mutex;

    sta = EINVAL;
    _clib_mutex_lock();
    if (*mut != 0)
    {
        index = (unsigned int)(*mut - 1);
        if (index < POSIX_CLIB_MUTEX_MAX)
        {
            mutex = _clib_mutexes[index];
            (void)pthread_mutex_destroy(mutex);
            _clib_mutexes[index] = 0;
            free((void*)mutex);
            sta = 0;
        }
    }
    _clib_mutex_unlock();

    return sta;
}

void posix_clib_mutex_initialize(void)
{
    unsigned int    index;

    /* Initialize mutex array for C library */
    for (index = 0; index < POSIX_CLIB_MUTEX_MAX; index++)
    {
        _clib_mutexes[index] = 0;
    }

    /* Initialize global lock */
    _clib_mutex_init();
}

void posix_clib_mutex_finalize(void)
{
    unsigned int    index;
    unsigned int    temp;

    for (index = 0; index < POSIX_CLIB_MUTEX_MAX; index++)
    {
        temp = index + 1;
        (void)_clib_mutex_rel((int*)&temp);
    }

    /* Finalize global lock */
    _clib_mutex_fini();
}

void posix_clib_mutex_reset(void)
{
    unsigned int        index;
    pthread_mutexattr_t attr;
    pthread_mutex_t*    mutex;

    /* Reset global lock object forcedly */
    memset(&_clib_mutex, 0x00, sizeof(pthread_mutex_t));

    /* Reset all mutex objects */
    (void)pthread_mutexattr_init(&attr);
    (void)pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    for (index = 0; index < POSIX_CLIB_MUTEX_MAX; index++)
    {
        mutex = _clib_mutexes[index];
        if (mutex != 0)
        {
            (void)pthread_mutex_init(mutex, &attr);
        }
    }
}

int posix_clib_mutex_init(int* mut)
{
    int                 sta;
    pthread_mutexattr_t attr;
    pthread_mutex_t*    mutex;

    mutex = _clib_mutex_get(mut);
    if (mutex != 0)
    {
        (void)pthread_mutexattr_init(&attr);
        (void)pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
        (void)pthread_mutexattr_setpshared(&attr, _mutex_shared);
        sta = pthread_mutex_init(mutex, &attr);
    }
    else
    {
        sta = EAGAIN;
    }

    return sta;
}

int posix_clib_mutex_destroy(int* mut)
{
    int     sta;

    sta = _clib_mutex_rel(mut);
    *mut = 0;

    return sta;
}

int posix_clib_mutex_lock(int* mut)
{
    int                 sta;
    pthread_mutex_t*    mutex;

    if (*mut == 0)
    {
        (void)posix_clib_mutex_init(mut);
    }
    mutex = _clib_mutex_get(mut);
    sta = pthread_mutex_lock(mutex);

    return sta;
}

int posix_clib_mutex_trylock(int* mut)
{
    int                 sta;
    pthread_mutex_t*    mutex;

    if (*mut == 0)
    {
        (void)posix_clib_mutex_init(mut);
    }
    mutex = _clib_mutex_get(mut);
    sta = pthread_mutex_trylock(mutex);

    return sta;
}

int posix_clib_mutex_unlock(int* mut)
{
    int                 sta;
    pthread_mutex_t*    mutex;

    mutex = _clib_mutex_get(mut);
    sta = pthread_mutex_unlock(mutex);

    return sta;
}

int mutex_init(int* mut)
{
    return posix_clib_mutex_init(mut);
}

int mutex_destroy(int* mut)
{
    return posix_clib_mutex_destroy(mut);
}

int mutex_lock(int* mut)
{
    return posix_clib_mutex_lock(mut);
}

int mutex_trylock(int* mut)
{
    return posix_clib_mutex_trylock(mut);
}

int mutex_unlock(int* mut)
{
    return posix_clib_mutex_unlock(mut);
}
