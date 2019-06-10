/*  $NetBSD: eventlib.h,v 1.1.1.3.4.1 2007/05/17 00:39:33 jdc Exp $ */

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

/* eventlib.h - exported interfaces for eventlib
 * vix 09sep95 [initial]
 *
 * Id: eventlib.h,v 1.3.18.2 2005/07/28 07:38:07 marka Exp
 */

#ifndef _EVENTLIB_H
#define _EVENTLIB_H

#include <sys/types.h>
#include <sys/uio.h>
#include <time.h>
#include <stdio.h>

/* ev_streams.c */
#define evConsIovec __evConsIovec

struct iovec evConsIovec(void *buf, size_t cnt);

/* ev_timers.c */
#define evConsTime  __evConsTime
#define evAddTime   __evAddTime
#define evSubTime   __evSubTime
#define evCmpTime   __evCmpTime
#define evTimeSpec  __evTimeSpec
#define evTimeVal   __evTimeVal
#define evNowTime   __evNowTime

struct timespec evConsTime(time_t sec, long nsec);
struct timespec evAddTime(struct timespec addend1, struct timespec addend2);
struct timespec evSubTime(struct timespec minuend, struct timespec subtrahend);
struct timespec evNowTime(void);
struct timespec evTimeSpec(struct timeval tv);
struct timeval evTimeVal(struct timespec ts);
int evCmpTime(struct timespec a, struct timespec b);

#endif /*_EVENTLIB_H*/
