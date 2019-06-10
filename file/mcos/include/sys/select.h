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
 sys/select.h   POSIX Layer  Synchronous I/O multiplexing definitions
============================================================================*/
#ifndef __SYS_SELECT_H__
#define __SYS_SELECT_H__

#if !defined COMPILER_RESTRICT
#if defined __cplusplus
#define COMPILER_RESTRICT
#else /* __cplusplus */
#define COMPILER_RESTRICT restrict
#endif /* __cplusplus */
#endif /* COMPILER_RESTRICT */

#include <limits.h>
#include <sys/syslimits.h>
#include <sys/_sigset.h>
#include <sys/_timeval.h>
#include <sys/timespec.h>
#if !defined(_SIGSET_T_DECLARED)
#define _SIGSET_T_DECLARED
typedef __sigset_t  sigset_t;
#endif /* #if !defined(_SIGSET_T_DECLARED) */

#ifdef  __cplusplus
extern  "C" {
#endif

 /* File descriptors max number in set */
#undef  FD_SETSIZE  /* (conflict with LIBC sys/types.h) */
#define FD_SETSIZE  (OPEN_MAX)
#define FD_SETBITS  (sizeof(int) * CHAR_BIT)

 /* File descriptor set */
typedef struct _fd_set
{
    unsigned int bits[FD_SETSIZE / FD_SETBITS + ((FD_SETSIZE % FD_SETBITS) != 0 ? 1 : 0)];
} fd_set;

/* File descriptor set manipulations */
#define FD_CLR(_f_, _s_)   ((_s_)->bits[(_f_) / FD_SETBITS] &= ~(1 << ((_f_) % FD_SETBITS)))

#define FD_SET(_f_, _s_)   ((_s_)->bits[(_f_) / FD_SETBITS] |=  (1 << ((_f_) % FD_SETBITS)))

#define FD_ISSET(_f_, _s_) ((_s_)->bits[(_f_) / FD_SETBITS] &   (1 << ((_f_) % FD_SETBITS)))

#define FD_ZERO(_s_) \
do                   \
{                    \
    int _i_;         \
    for (_i_ = 0; _i_ < sizeof(*(_s_)) / sizeof((_s_)->bits[0]); _i_++) \
                     (_s_)->bits[_i_] = 0; \
} while (0)

/* Prototypes */
int  pselect(int, fd_set *COMPILER_RESTRICT, fd_set *COMPILER_RESTRICT, fd_set *COMPILER_RESTRICT,
             const struct timespec *COMPILER_RESTRICT, const sigset_t *COMPILER_RESTRICT);
int  select(int, fd_set *COMPILER_RESTRICT, fd_set *COMPILER_RESTRICT, fd_set *COMPILER_RESTRICT, struct timeval *COMPILER_RESTRICT);

#ifdef  __cplusplus
}
#endif

#endif /* __SYS_SELECT_H__ */
