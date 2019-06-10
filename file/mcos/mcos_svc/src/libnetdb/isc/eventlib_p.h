/*  $NetBSD: eventlib_p.h,v 1.1.1.3.4.1 2007/05/17 00:40:05 jdc Exp $       */

/*
 * Copyright (c) 2005 by Internet Systems Consortium, Inc. ("ISC")
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

/*! \file 
 * \brief private interfaces for eventlib
 * \author vix 09sep95 [initial]
 *
 * Id: eventlib_p.h,v 1.5.18.4 2006/03/10 00:20:08 marka Exp
 */

#ifndef _EVENTLIB_P_H
#define _EVENTLIB_P_H

#include <sys/param.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "isc/memcluster.h"

#ifdef USE_POLL
#include <poll.h>
#endif /* USE_POLL */

/*Dummy */

#endif /*_EVENTLIB_P_H*/
