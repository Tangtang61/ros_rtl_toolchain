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
[sigsetops.c] - MCOS POSIX signal set API
****************************************************************************/
#include <pt_api_impl.h>
#include <signal.h>
#include <errno.h>

/* sigemptyset() API */
int sigemptyset(sigset_t* set)
{
#if MCOS_CFG_PT_CHECK_ARGUMENTS
    if ((set == 0)
        || (CHECK_ALIGN(set, sizeof(*set)) != 0))
    {
        errno = EINVAL;
        return -1;
    }
#endif
    *set = 0;
    return 0;
}

/* sigfillset() API */
int sigfillset(sigset_t* set)
{
#if MCOS_CFG_PT_CHECK_ARGUMENTS
    if ((set == 0)
        || (CHECK_ALIGN(set, sizeof(*set)) != 0))
    {
        errno = EINVAL;
        return -1;
    }
#endif
    *set = (sigset_t)-1;
    return 0;
}

/* sigaddset() API */
int sigaddset(sigset_t* set, int sig)
{
    if (1
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (set != 0)
        && (CHECK_ALIGN(set, sizeof(*set)) == 0)
#endif
        && (sig > 0)
        && (sig <= PT_NUM_SIG)
    )
    {
        *set |= 1 << (sig - 1);
        return 0;
    }
    errno = EINVAL;
    return -1;
}

/* sigdelset() API */
int sigdelset(sigset_t* set, int sig)
{
    if (1
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (set != 0)
        && (CHECK_ALIGN(set, sizeof(*set)) == 0)
#endif
        && (sig > 0)
        && (sig <= PT_NUM_SIG)
    )
    {
        *set &= ~((sigset_t)1 << (sig - 1));
        return 0;
    }
    errno = EINVAL;
    return -1;
}

/* sigismember() API */
int sigismember(const sigset_t* set, int sig)
{
    if (1
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (set != 0)
        && (CHECK_ALIGN(set, sizeof(*set)) == 0)
#endif
        && (sig > 0)
        && (sig <= PT_NUM_SIG)
    )
    {
        return ((*set & (1 << (sig - 1))) != 0
                ? 1
                : 0);
    }
    errno = EINVAL;
    return -1;
}
