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
[pthread_mutex_attr.c] - MCOS Pthread mutex attributes API
****************************************************************************/
#include <pt_api_impl.h>
#include <pt_mutex_if.h>
#include <errno.h>

static int pthread_mutexattr_valid(const pthread_mutexattr_t* attr)
{
    return (1
#ifdef MCOS_CFG_PT_CHECK_ARGUMENTS
            && (attr != 0)
            && (CHECK_ALIGN(attr, sizeof(*attr)) == 0)
#endif
    );
}

/* pthread_mutexattr_init() API */
int pthread_mutexattr_init(pthread_mutexattr_t* attr)
{
    if (pthread_mutexattr_valid((const pthread_mutexattr_t*)attr))
    {
        *attr = MUTEX_ATTR_DEFAULT;
        return 0;
    }
    return EINVAL;
}

/* pthread_mutexattr_destroy() API */
int pthread_mutexattr_destroy(pthread_mutexattr_t* attr)
{
    if (pthread_mutexattr_valid((const pthread_mutexattr_t*)attr))
    {
        *attr = MUTEX_ATTR_INVALID;
        return 0;
    }
    return EINVAL;
}

/* pthread_mutexattr_getpshared() API */
int pthread_mutexattr_getpshared(const pthread_mutexattr_t* restrict attr, int* restrict pshared)
{
    if (pthread_mutexattr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (pshared != 0)
        && (CHECK_ALIGN(pshared, sizeof(*pshared)) == 0)
#endif
    )
    {
        *pshared  = (((*attr & (MUTEX_ATTR_SHARED_MASK
                                << MUTEX_ATTR_SHARED_SHIFT)) != 0)
                     ? PTHREAD_PROCESS_SHARED
                     : PTHREAD_PROCESS_PRIVATE);
        return 0;
    }
    return EINVAL;
}

/* pthread_mutexattr_setpshared() API */
int pthread_mutexattr_setpshared(pthread_mutexattr_t* attr, int pshared)
{
    if (((pshared == PTHREAD_PROCESS_SHARED)
         || (pshared == PTHREAD_PROCESS_PRIVATE))
        && pthread_mutexattr_valid((const pthread_mutexattr_t*)attr) )
    {
        *attr = ((*attr & ~(MUTEX_ATTR_SHARED_MASK
                            << MUTEX_ATTR_SHARED_SHIFT))
                 | (pshared == PTHREAD_PROCESS_SHARED
                    ? MUTEX_ATTR_SHARED_MASK << MUTEX_ATTR_SHARED_SHIFT
                    : 0));
        return 0;
    }
    return EINVAL;
}

/* pthread_mutexattr_getrobust() API */
int pthread_mutexattr_getrobust(const pthread_mutexattr_t* restrict attr, int* restrict robust)
{
    if (pthread_mutexattr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
         && (robust != 0)
         && (CHECK_ALIGN(robust, sizeof(*robust)) == 0)
#endif
    )
    {
        *robust  = (((*attr & (MUTEX_ATTR_ROBUST_MASK
                               << MUTEX_ATTR_ROBUST_SHIFT)) != 0)
                    ? PTHREAD_MUTEX_ROBUST
                    : PTHREAD_MUTEX_STALLED);
        return 0;
    }
    return EINVAL;
}

/* pthread_mutexattr_setrobust() API */
int pthread_mutexattr_setrobust(pthread_mutexattr_t* attr, int robust)
{
    if ((robust == PTHREAD_MUTEX_STALLED
         || robust == PTHREAD_MUTEX_ROBUST)
        && pthread_mutexattr_valid((const pthread_mutexattr_t*)attr) )
    {
        *attr = ((*attr & ~(MUTEX_ATTR_ROBUST_MASK
                            << MUTEX_ATTR_ROBUST_SHIFT))
                 | (robust == PTHREAD_MUTEX_ROBUST
                    ? MUTEX_ATTR_ROBUST_MASK << MUTEX_ATTR_ROBUST_SHIFT
                    : 0));
        return 0;
    }
    return EINVAL;
}

/* pthread_mutexattr_getprotocol() API */
int pthread_mutexattr_getprotocol(const pthread_mutexattr_t* restrict attr, int* restrict protocol)
{
    if (pthread_mutexattr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
         && (protocol != 0)
         && (CHECK_ALIGN(protocol, sizeof(*protocol)) == 0)
#endif
    )
    {
        *protocol = ((*attr >> MUTEX_ATTR_PROTOCOL_SHIFT)
                     & MUTEX_ATTR_PROTOCOL_MASK);
        return 0;
    }
    return EINVAL;
}

/* pthread_mutexattr_setprotocol() API */
int pthread_mutexattr_setprotocol(pthread_mutexattr_t* attr, int protocol)
{
    if (((protocol == PTHREAD_PRIO_NONE)
         || (protocol == PTHREAD_PRIO_INHERIT)
         || (protocol == PTHREAD_PRIO_PROTECT))
        && pthread_mutexattr_valid((const pthread_mutexattr_t*)attr) )
    {
        *attr = ((*attr & ~(MUTEX_ATTR_PROTOCOL_MASK
                            << MUTEX_ATTR_PROTOCOL_SHIFT))
                 | (protocol << MUTEX_ATTR_PROTOCOL_SHIFT));
        return 0;
    }
    return EINVAL;
}

/* pthread_mutexattr_gettype() API */
int pthread_mutexattr_gettype(const pthread_mutexattr_t* restrict attr, int* restrict type)
{
    if (pthread_mutexattr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
         && (type != 0)
         && (CHECK_ALIGN(type, sizeof(*type)) == 0)
#endif
    )
    {
        *type = (*attr >> MUTEX_ATTR_TYPE_SHIFT) & MUTEX_ATTR_TYPE_MASK;
        return 0;
    }
    return EINVAL;
}

/* pthread_mutexattr_settype() API */
int pthread_mutexattr_settype(pthread_mutexattr_t* attr, int type)
{
    if (((type == PTHREAD_MUTEX_NORMAL)
         || (type == PTHREAD_MUTEX_ERRORCHECK)
         || (type == PTHREAD_MUTEX_RECURSIVE))
        && pthread_mutexattr_valid((const pthread_mutexattr_t*)attr) )
    {
        *attr = ((*attr & ~(MUTEX_ATTR_TYPE_MASK
                            << MUTEX_ATTR_TYPE_SHIFT))
                 | (type << MUTEX_ATTR_TYPE_SHIFT));
        return 0;
    }
    return EINVAL;
}

/* pthread_mutexattr_getprioceiling() API */
int pthread_mutexattr_getprioceiling(const pthread_mutexattr_t* restrict attr, int* restrict ceil)
{
    if (pthread_mutexattr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
         && (ceil != 0)
         && (CHECK_ALIGN(ceil, sizeof(*ceil)) == 0)
#endif
    )
    {
        *ceil = (*attr >> MUTEX_ATTR_PRIO_SHIFT) & MUTEX_ATTR_PRIO_MASK;
        return 0;
    }
    return EINVAL;
}

/* pthread_mutexattr_setprioceiling() API */
int pthread_mutexattr_setprioceiling(pthread_mutexattr_t* attr, int ceil)
{
    if ( (ceil >= MCOS_CFG_PT_MIN_PRI)
         && (ceil <= MCOS_CFG_PT_MAX_PRI)
         && pthread_mutexattr_valid((const pthread_mutexattr_t*)attr) )
    {
        *attr = ((*attr & ~(MUTEX_ATTR_PRIO_MASK << MUTEX_ATTR_PRIO_SHIFT))
                 | (ceil << MUTEX_ATTR_PRIO_SHIFT));
        return 0;
    }
    return EINVAL;
}
