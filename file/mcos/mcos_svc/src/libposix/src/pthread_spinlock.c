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
[ptread_spinlock.c] - MCOS Pthread spinlock API
****************************************************************************/

#include <pthread.h>
#include <errno.h>
#include <pt_api_impl.h>
#include <posix_atomic.h>

/* Alignment check */
#define CHECK_ALIGN(_x_, _a_)  ((unsigned)(uintptr_t)(_x_) & ((_a_) - 1))

int pthread_spin_init(pthread_spinlock_t* lock, int pshared)
{
    if (0
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        || (lock == 0)
        || (CHECK_ALIGN(lock, sizeof(*lock)) != 0)
#endif
        || ((pshared != PTHREAD_PROCESS_SHARED)
            && (pshared != PTHREAD_PROCESS_PRIVATE))
    )
    {
        return EINVAL;
    }

    posix_atomic_purge((void*)lock);
    posix_atomic_set((void*)lock, 0);
    return 0;
}

int pthread_spin_destroy(pthread_spinlock_t* lock)
{
    int lockval;

#if MCOS_CFG_PT_CHECK_ARGUMENTS
    if ( (lock == 0)
         || (CHECK_ALIGN(lock, sizeof(*lock)) != 0) )
    {
        return EINVAL;
    }
#endif

    posix_atomic_purge((void*)lock);
    lockval = posix_atomic_get((void*)lock);

    return ((lockval != 0)
            ? EBUSY
            : 0);
}

int pthread_spin_lock(pthread_spinlock_t* lock)
{
#if MCOS_CFG_PT_CHECK_ARGUMENTS
    if ( (lock == 0)
         || (CHECK_ALIGN(lock, sizeof(*lock)) != 0) )
    {
        return EINVAL;
    }
#endif

    posix_atomic_spinlock((int*)lock);
    return 0;
}

int pthread_spin_unlock(pthread_spinlock_t* lock)
{
#if MCOS_CFG_PT_CHECK_ARGUMENTS
    if ( (lock == 0)
         || (CHECK_ALIGN(lock, sizeof(*lock)) != 0) )
    {
        return EINVAL;
    }
#endif

    return ((posix_atomic_cmpset((int*)lock, 1, 0) == 0)
            ? EPERM
            : 0);
}

int pthread_spin_trylock(pthread_spinlock_t* lock)
{
#if MCOS_CFG_PT_CHECK_ARGUMENTS
    if ( (lock == 0)
         || (CHECK_ALIGN(lock, sizeof(*lock)) != 0) )
    {
        return EINVAL;
    }
#endif

    return ((posix_atomic_cmpset((int*)lock, 0, 1) != 0)
            ? EBUSY
            : 0);
}
