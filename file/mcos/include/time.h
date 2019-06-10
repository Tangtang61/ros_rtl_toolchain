/*  $NetBSD: time.h,v 1.27 2001/03/31 18:29:20 kleink Exp $ */

/*
 * Copyright (c) 1989, 1993
 *  The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
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
 *  @(#)time.h  8.3 (Berkeley) 1/21/94
 */

/*
   Copyright (C) 2019 By eSOL Co.,Ltd. Tokyo, Japan
   Modified to work with eMCOS.
*/

#ifndef __time_h
#define __time_h

#if !defined COMPILER_RESTRICT
#if defined __cplusplus
#define COMPILER_RESTRICT
#else /* __cplusplus */
#define COMPILER_RESTRICT restrict
#endif /* __cplusplus */
#endif /* COMPILER_RESTRICT */

#include <sys/cdefs.h>
#include <sys/features.h>
#include <machine/ansi.h>
#include <sys/types.h>
#include <sys/_timespec.h>
#include <sys/null.h>

#ifndef __TIME_DECLS
#define __TIME_DECLS

__BEGIN_DECLS

struct tm {
    int tm_sec;     /* seconds after the minute [0-61] */
    int tm_min;     /* minutes after the hour [0-59] */
    int tm_hour;    /* hours since midnight [0-23] */
    int tm_mday;    /* day of the month [1-31] */
    int tm_mon;     /* months since January [0-11] */
    int tm_year;    /* years since 1900 */
    int tm_wday;    /* days since Sunday [0-6] */
    int tm_yday;    /* days since January 1 [0-365] */
    int tm_isdst;   /* Daylight Savings Time flag */
    long    tm_gmtoff;  /* offset from UTC in seconds */
    __aconst char *tm_zone; /* timezone abbreviation */
};

typedef struct __tzrule_struct
{
  char ch;
  int m;
  int n;
  int d;
  int s; 
  time_t change;
  long offset; /* Match type of _timezone. */
} __tzrule_type;

typedef struct __tzinfo_struct
{
  int __tznorth;
  int __tzyear;
  __tzrule_type __tzrule[2];
} __tzinfo_type;

__BEGIN_NAMESPACE_STD

typedef _CLOCK_T_ clock_t;


char *asctime (const struct tm *);
clock_t clock (void);
char *ctime (const time_t *);
double difftime (time_t, time_t);
struct tm *gmtime (const time_t *);
struct tm *localtime (const time_t *);
time_t mktime (struct tm *);
size_t strftime (char * COMPILER_RESTRICT, size_t, const char * COMPILER_RESTRICT,
    const struct tm * COMPILER_RESTRICT);
time_t time (time_t *);
__END_NAMESPACE_STD

typedef _CLOCKID_T_ clockid_t;

typedef _TIMER_T_   timer_t;

#if !defined(_ANSI_SOURCE)
#define CLK_TCK     1000
extern __aconst char *tzname[2];
void tzset (void);

/*
 * X/Open Portability Guide >= Issue 4
 */
#if (!defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)) || \
    (_XOPEN_SOURCE - 0) >= 4
extern int daylight;
#ifndef __LIBC12_SOURCE__
extern long int timezone __RENAME(__timezone13);
#endif
char *strptime (const char * COMPILER_RESTRICT, const char * COMPILER_RESTRICT,
    struct tm * COMPILER_RESTRICT);
#endif

#if (!defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)) || \
    (_POSIX_C_SOURCE - 0) >= 199309L || (_XOPEN_SOURCE - 0) >= 500
#include <sys/time.h>       /* XXX for struct timespec */
struct sigevent;
struct itimerspec;
int clock_getres (clockid_t, struct timespec *);
int clock_gettime (clockid_t, struct timespec *);
int clock_settime (clockid_t, const struct timespec *);
int nanosleep (const struct timespec *, struct timespec *);
int timer_create (clockid_t, struct sigevent *, timer_t *);
int timer_delete (timer_t);
int timer_getoverrun (timer_t);
int timer_gettime (timer_t, struct itimerspec *);
int timer_settime (timer_t, int, const struct itimerspec *,
    struct itimerspec *);
#endif /* (!_POSIX_C_SOURCE && !_XOPEN_SOURCE) || ... */

#if (!defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)) || \
    (_POSIX_C_SOURCE - 0) >= 199506L || (_XOPEN_SOURCE - 0) >= 500 || \
    defined(_REENTRANT)
char *asctime_r (const struct tm * COMPILER_RESTRICT, char * COMPILER_RESTRICT);
char *ctime_r (const time_t *, char *);
struct tm *gmtime_r (const time_t * COMPILER_RESTRICT, struct tm * COMPILER_RESTRICT);
struct tm *localtime_r (const time_t * COMPILER_RESTRICT, struct tm * COMPILER_RESTRICT);
#endif

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)
time_t time2posix (time_t);
time_t posix2time (time_t);
time_t timegm (struct tm *const);
time_t timeoff (struct tm *const, const long);
time_t timelocal (struct tm *const);
#ifdef __LIBC12_SOURCE__
char *timezone (int, int);
#endif
void tzsetwall (void);
struct tm *offtime (const time_t *const, const long);
#endif /* !_POSIX_C_SOURCE && !_XOPEN_SOURCE */

#endif /* !_ANSI_SOURCE */

#undef  CLOCKS_PER_SEC
#undef  CLOCK_REALTIME
#undef  CLOCK_MONOTONIC
#undef  TIMER_ABSTIME

#define CLOCKS_PER_SEC              1000000     /* To convert clock() into seconds */
#define CLOCK_PROCESS_CPUTIME_ID    0xfffffffeU /* Process cpu-time clock id */
#define CLOCK_THREAD_CPUTIME_ID     0xfffffffdU /* Thread cpu-time clock id */

#define CLOCK_MONOTONIC             0           /* Monotonic clock */
#define CLOCK_REALTIME              0xffffffffU /* Realtime clock (can have jumps) */
#define TIMER_ABSTIME               1           /* Flag indicating time is absolute */

int clock_getcpuclockid(pid_t, clockid_t *);
int clock_getres(clockid_t, struct timespec *);
int clock_gettime(clockid_t, struct timespec *);
int clock_settime(clockid_t, const struct timespec *);

int clock_nanosleep(clockid_t, int, const struct timespec *, struct timespec *);
int nanosleep(const struct timespec *, struct timespec *);

__tzinfo_type *_EXFUN (__gettzinfo, (_VOID));

__END_DECLS
#endif /* __TIME_DECLS */

#ifndef __TIME_NO_EXPORTS  /* defined in ARM RVCT <ctime> */
__USING_NAMESPACE_STD(clock_t)
__USING_NAMESPACE_STD(asctime)
__USING_NAMESPACE_STD(clock)
__USING_NAMESPACE_STD(ctime)
__USING_NAMESPACE_STD(difftime)
__USING_NAMESPACE_STD(gmtime)
__USING_NAMESPACE_STD(localtime)
__USING_NAMESPACE_STD(mktime)
__USING_NAMESPACE_STD(strftime)
__USING_NAMESPACE_STD(time)
#endif  /* #ifndef __TIME_NO_EXPORTS */

#endif /* !__time_h */
