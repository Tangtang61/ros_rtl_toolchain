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
[pthread_rwlock_attr.c] - MCOS Pthread rwlock attributes API
****************************************************************************/
#include <pt_api_impl.h>
#include <pt_rwlock_if.h>
#include <errno.h>

static int pthread_rwlockattr_valid(const pthread_rwlockattr_t* attr)
{
    return (1
#ifdef MCOS_CFG_PT_CHECK_ARGUMENTS
            && (attr != 0)
            && (CHECK_ALIGN(attr, sizeof(*attr)) == 0)
#endif
    );
}

/* pthread_rwlockattr_init() API */
int pthread_rwlockattr_init(pthread_rwlockattr_t* attr)
{
    if (pthread_rwlockattr_valid((const pthread_rwlockattr_t*)attr))
    {
        *attr = 0;
        return 0;
    }
    return EINVAL;
}

/* pthread_rwlockattr_destroy() API */
int pthread_rwlockattr_destroy(pthread_rwlockattr_t* attr)
{
    if (pthread_rwlockattr_valid((const pthread_rwlockattr_t*)attr))
    {
        *attr = -1U;
        return 0;
    }
    return EINVAL;
}

/* pthread_rwlockattr_getpshared() API */
int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t* restrict attr, int* restrict pshared)
{
    if (pthread_rwlockattr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
         && (pshared != 0)
         && (CHECK_ALIGN(pshared, sizeof(*pshared)) == 0)
#endif
    )
    {
        *pshared  = ((*attr & RWLOCK_ATTR_SHARED) != 0
                     ? PTHREAD_PROCESS_SHARED
                     : PTHREAD_PROCESS_PRIVATE);
        return 0;
    }
    return EINVAL;
}

/* pthread_rwlockattr_setpshared() API */
int pthread_rwlockattr_setpshared(pthread_rwlockattr_t* attr, int pshared)
{
    if (((pshared == PTHREAD_PROCESS_SHARED)
         || (pshared == PTHREAD_PROCESS_PRIVATE))
        && pthread_rwlockattr_valid((const pthread_rwlockattr_t*)attr) )
    {
        *attr = ((*attr & ~RWLOCK_ATTR_SHARED)
                 | (pshared == PTHREAD_PROCESS_SHARED
                    ? RWLOCK_ATTR_SHARED
                    : 0));
        return 0;
    }
    return EINVAL;
}
