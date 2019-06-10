/*  $NetBSD: ev_streams.c,v 1.1.1.3.4.1 2007/05/17 00:40:04 jdc Exp $       */

/*
 * Copyright (c) 2004 by Internet Systems Consortium, Inc. ("ISC")
 * Copyright (c) 1996-1999 by Internet Software Consortium
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

/* ev_streams.c - implement asynch stream file IO for the eventlib
 * vix 04mar96 [initial]
 */
#include "port_before.h"

#include <sys/types.h>
#include <sys/uio.h>
#include <errno.h>

#include "isc/eventlib.h"
#include "isc/assertions.h"
#include "eventlib_p.h"

#include "port_after.h"

struct iovec
evConsIovec(void *buf, size_t cnt) {
    struct iovec ret;

    memset(&ret, 0xf5, sizeof ret);
    ret.iov_base = buf;
    ret.iov_len = cnt;
    return (ret);
}
