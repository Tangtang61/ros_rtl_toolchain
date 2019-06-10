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
 ftime.c    POSIX Layer ftime() library function
============================================================================*/
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/null.h>

/* Get date and time (LEGACY) */
int ftime(struct timeb *tp)
{
    int             sta;
    struct timeval  tim;
    struct timezone timz;

    if (tp != NULL)
    {
        timz.tz_minuteswest = 0;
        timz.tz_dsttime     = 0;
        sta = gettimeofday(&tim, (void*)&timz);
        if (sta == 0)
        {
            tp->time     = tim.tv_sec;
            tp->millitm  = (tim.tv_usec / 1000);
            tp->timezone = (short)timz.tz_minuteswest;
            tp->dstflag  = (short)timz.tz_dsttime;
        }
        else
        {
         /* gettimeofday() may always return 0, but just in case */
            sta = -1;
        }
    }
    else
    {
        sta = -1;
    }

    return sta;
}
