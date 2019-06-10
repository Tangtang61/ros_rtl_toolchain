/*  $NetBSD: strptime.c,v 1.22 2000/12/20 20:56:34 christos Exp $   */

/*-
 * Copyright (c) 1997, 1998 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code was contributed to The NetBSD Foundation by Klaus Klein.
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
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
   Copyright(C) 2019 eSOL Co., Ltd.
   Modified to work with eMCOS.
*/

#include <time.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define _ctloc(x)    x

#define TM_YEAR_BASE 1900

int strcasecmp(const char *s1, const char *s2);
int strncasecmp(const char *s1, const char *s2, size_t n);
/*
 * We do not implement alternate representations. However, we always
 * check whether a given modifier is allowed for a certain conversion.
 */
#define ALT_E           0x01
#define ALT_O           0x02
#define LEGAL_ALT(x)        { if (alt_format & ~(x)) return (0); }


static  int conv_num (const unsigned char **, int *, int, int);

/* rt_locale.h: definitions to enable retargetting of locale mechanism
 *
 * Copyright 1999 ARM Limited. All rights reserved.
 *
 * RCS $Revision: 103989 $
 * Checkin $Date: 2006-10-25 15:18:33 +0100 (Wed, 25 Oct 2006) $
 * Revising $Author: statham $
 */
/*
 * This code has been copied from rt_locale.h in RVCT3.1.
 * __lc_time_blk is undefined under RVCT4.0 because tailoring locale
 * and CTYPE using C macros is obsolete.
 */
struct __lc_time_blk {
    unsigned offset_week_abbrs;        /* char week_abbrs[] */
    unsigned offset_week_full;         /* char week_full[] */
    unsigned offset_month_abbrs;       /* char month_abbrs[] */
    unsigned offset_month_full;        /* char month_full[] */
    unsigned offset_am;                /* char am[] */
    unsigned offset_pm;                /* char pm[] */
    unsigned offset_datetime_fmt;      /* char datetime_fmt[] */
    unsigned offset_date_fmt;          /* char date_fmt[] */
    unsigned offset_time_fmt;          /* char time_fmt[] */
    unsigned size_week_abbrs;          /* size of one entry */
    unsigned size_week_full;           /* size of one entry */
    unsigned size_month_abbrs;         /* size of one entry */
    unsigned size_month_full;          /* size of one entry */
    unsigned offset_12hrtime_fmt;      /* char 12hrtime_fmt[] */
};

char *
strptime(const char *buf, const char *fmt, struct tm *tm)
{
    printf("strptime(): ROS-RTL does not support this POSIX API.\n");
    return NULL;
}


static int
conv_num(const unsigned char **buf, int *dest, int llim, int ulim)
{
    int result = 0;

    /* The limit also determines the number of valid digits. */
    int rulim = ulim;

    if (**buf < '0' || **buf > '9')
        return (0);

    do {
        result *= 10;
        result += *(*buf)++ - '0';
        rulim /= 10;
    } while ((result * 10 <= ulim) && rulim && **buf >= '0' && **buf <= '9');

    if (result < llim || result > ulim)
        return (0);

    *dest = result;
    return (1);
}

