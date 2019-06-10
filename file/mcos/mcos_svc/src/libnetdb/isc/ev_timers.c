/*  $NetBSD: ev_timers.c,v 1.1.1.3.4.1 2007/05/17 00:40:04 jdc Exp $        */

/*
 * Copyright (c) 2004 by Internet Systems Consortium, Inc. ("ISC")
 * Copyright (c) 1995-1999 by Internet Software Consortium
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/* ev_timers.c - implement timers for the eventlib
 * vix 09sep95 [initial]
 */
/* Import. */

#include "port_before.h"

#include <errno.h>

#include "isc/assertions.h"
#include "isc/eventlib.h"
#include "eventlib_p.h"

#include "port_after.h"

/* Constants. */

#define MILLION 1000000
#define BILLION 1000000000

/* Forward. */
/* Public. */

struct timespec
evConsTime(time_t sec, long nsec) {
    struct timespec x;

    x.tv_sec = sec;
    x.tv_nsec = nsec;
    return (x);
}

struct timespec
evAddTime(struct timespec addend1, struct timespec addend2) {
    struct timespec x;

    x.tv_sec = addend1.tv_sec + addend2.tv_sec;
    x.tv_nsec = addend1.tv_nsec + addend2.tv_nsec;
    if (x.tv_nsec >= BILLION) {
        x.tv_sec++;
        x.tv_nsec -= BILLION;
    }
    return (x);
}

struct timespec
evSubTime(struct timespec minuend, struct timespec subtrahend) {
    struct timespec x;

    x.tv_sec = minuend.tv_sec - subtrahend.tv_sec;
    if (minuend.tv_nsec >= subtrahend.tv_nsec)
        x.tv_nsec = minuend.tv_nsec - subtrahend.tv_nsec;
    else {
        x.tv_nsec = BILLION - subtrahend.tv_nsec + minuend.tv_nsec;
        x.tv_sec--;
    }
    return (x);
}

int
evCmpTime(struct timespec a, struct timespec b) {
    long x = a.tv_sec - b.tv_sec;

    if (x == 0L)
        x = a.tv_nsec - b.tv_nsec;
    return (x < 0L ? (-1) : x > 0L ? (1) : (0));
}

struct timespec
evNowTime(void) {
    struct timeval now;
#ifdef CLOCK_REALTIME
    struct timespec tsnow;
    clockid_t m = CLOCK_REALTIME;
    if (clock_gettime(m, &tsnow) == 0)
        return (tsnow);
#endif
    if (gettimeofday(&now, NULL) < 0)
        return (evConsTime(0, 0));
    return (evTimeSpec(now));
}

struct timespec
evTimeSpec(struct timeval tv) {
    struct timespec ts;

    ts.tv_sec = tv.tv_sec;
    ts.tv_nsec = tv.tv_usec * 1000;
    return (ts);
}

struct timeval
evTimeVal(struct timespec ts) {
    struct timeval tv;

    tv.tv_sec = ts.tv_sec;
    tv.tv_usec = ts.tv_nsec / 1000;
    return (tv);
}
