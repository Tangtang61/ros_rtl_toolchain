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
[pthread_barrier_attr.c] - MCOS Pthread barrier attributes API
****************************************************************************/
#include <pt_api_impl.h>
#include <pt_barrier_if.h>
#include <errno.h>

static int pthread_barrierattr_valid(const pthread_barrierattr_t* attr)
{
    return (1
#ifdef MCOS_CFG_PT_CHECK_ARGUMENTS
            && (attr != 0)
            && (CHECK_ALIGN(attr, sizeof(*attr)) == 0)
#endif
    );
}

/* pthread_barrierattr_init() API */
int pthread_barrierattr_init(pthread_barrierattr_t* attr)
{
    if (pthread_barrierattr_valid((const pthread_barrierattr_t*)attr))
    {
        *attr = 0;
        return 0;
    }
    return EINVAL;
}

/* pthread_barrierattr_destroy() API */
int pthread_barrierattr_destroy(pthread_barrierattr_t* attr)
{
    if (pthread_barrierattr_valid((const pthread_barrierattr_t*)attr))
    {
        *attr = -1U;
        return 0;
    }
    return EINVAL;
}

/* pthread_barrierattr_getpshared() API */
int pthread_barrierattr_getpshared(const pthread_barrierattr_t* restrict attr, int* restrict pshared)
{
    if (pthread_barrierattr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
         && (pshared != 0)
         && (CHECK_ALIGN(pshared, sizeof(*pshared)) == 0)
#endif
    )
    {
        *pshared  = ((*attr & BARRIER_ATTR_SHARED) != 0
                     ? PTHREAD_PROCESS_SHARED
                     : PTHREAD_PROCESS_PRIVATE);
        return 0;
    }
    return EINVAL;
}

/* pthread_barrierattr_setpshared() API */
int pthread_barrierattr_setpshared(pthread_barrierattr_t* attr, int pshared)
{
    if (((pshared == PTHREAD_PROCESS_SHARED)
         || (pshared == PTHREAD_PROCESS_PRIVATE))
        && pthread_barrierattr_valid((const pthread_barrierattr_t*)attr) )
    {
        *attr = ((*attr & ~BARRIER_ATTR_SHARED)
                 | (pshared == PTHREAD_PROCESS_SHARED
                    ? BARRIER_ATTR_SHARED
                    : 0));
        return 0;
    }
    return EINVAL;
}
