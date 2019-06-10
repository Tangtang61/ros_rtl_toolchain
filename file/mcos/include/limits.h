/*  $NetBSD: limits.h,v 1.13 1999/09/27 16:24:39 kleink Exp $   */

/*
 * Copyright (c) 1988, 1993
 *  The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *  This product includes software developed by the University of
 *  California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *  @(#)limits.h    8.2 (Berkeley) 1/4/94
 */

/*
   Copyright (C) 2019 By eSOL Co.,Ltd. Tokyo, Japan
   Modified to work with eMCOS.
*/

#ifndef _LIMITS_H_
#define _LIMITS_H_

#define _POSIX_ARG_MAX      4096
#define _POSIX_CHILD_MAX    25
#define _POSIX_LINK_MAX     8
#define _POSIX_LOGIN_NAME_MAX   9
#define _POSIX_MAX_CANON    255
#define _POSIX_MAX_INPUT    255
#define _POSIX_NAME_MAX     14
#define _POSIX_NGROUPS_MAX  8
#define _POSIX_OPEN_MAX     20
#define _POSIX_PATH_MAX     256
#define _POSIX_PIPE_BUF     512
#define _POSIX_SSIZE_MAX    32767
#define _POSIX_STREAM_MAX   8
#define _POSIX_TZNAME_MAX   6

#define _POSIX2_BC_BASE_MAX 99
#define _POSIX2_BC_DIM_MAX  2048
#define _POSIX2_BC_SCALE_MAX    99
#define _POSIX2_BC_STRING_MAX   1000
#define _POSIX2_COLL_WEIGHTS_MAX    2
#define _POSIX2_EXPR_NEST_MAX   32
#define _POSIX2_LINE_MAX    2048
#define _POSIX2_RE_DUP_MAX  255

#define _XOPEN_IOV_MAX      16
#define PASS_MAX        128

#define NL_ARGMAX       9
#define NL_LANGMAX      14
#define NL_MSGMAX       32767
#define NL_NMAX         1
#define NL_SETMAX       255
#define NL_TEXTMAX      64

#include <machine/limits.h>
#include <sys/syslimits.h>

#ifndef PTHREAD_THREADS_MAX
#define PTHREAD_THREADS_MAX 64
#endif

#ifndef PTHREAD_KEYS_MAX
#define PTHREAD_KEYS_MAX    128
#endif

#ifndef PTHREAD_STACK_MIN
#define PTHREAD_STACK_MIN   4096
#endif

#ifndef MQ_OPEN_MAX
#define MQ_OPEN_MAX         32
#endif

#ifndef MQ_PRIO_MAX
#define MQ_PRIO_MAX         140
#endif

#ifndef SEM_NSEMS_MAX
#define SEM_NSEMS_MAX       256
#endif

#ifndef TIMER_MAX
#define TIMER_MAX           64
#endif

#ifdef  SEM_VALUE_MAX
#undef  SEM_VALUE_MAX
#endif
#define SEM_VALUE_MAX      0xfffff

#ifndef AIO_MAX
#define AIO_MAX             256         /* Max outstanding AIO reqs system-wide */
#endif

#ifndef AIO_LISTIO_MAX
#define AIO_LISTIO_MAX      16          /* Max list AIO requests number */
#endif

#ifndef AIO_PRIO_DELTA_MAX
#define AIO_PRIO_DELTA_MAX  16          /* Max priority decrease delta for AIO */
#endif

#ifndef IOV_MAX
#define IOV_MAX             16          /* Max IO vectors */
#endif

#define LONG_LONG_MIN   LLONG_MIN
#define LONG_LONG_MAX   LLONG_MAX
#define ULONG_LONG_MAX  ULLONG_MAX

#endif /* !_LIMITS_H_ */
