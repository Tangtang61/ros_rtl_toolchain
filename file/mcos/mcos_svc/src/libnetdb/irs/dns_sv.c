/*  $NetBSD: dns_sv.c,v 1.1.1.3.4.1 2007/05/17 00:39:46 jdc Exp $   */

/*
 * Copyright (c) 2004 by Internet Systems Consortium, Inc. ("ISC")
 * Copyright (c) 1996,1999 by Internet Software Consortium.
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
/* Imports */

#include "port_before.h"

#include <sys/types.h>
#include <netinet/in.h>

#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include "resolv.h"

#include "isc/memcluster.h"
#include "irs.h"

#include "port_after.h"

#include "irs_p.h"
#include "hesiod.h"
#include "dns_p.h"

/* Definitions */

struct pvt {
    struct dns_p *          dns;
    struct servent          serv;
    char *                  svbuf;
    struct __res_state *    res;
    void                    (*free_res)(void *);
};

/* Forward. */

static void                 sv_close(struct irs_sv *);
static struct servent *     sv_byname(struct irs_sv *,
                                      const char *, const char *);
static struct servent *     sv_byport(struct irs_sv *, int, const char *);
static struct servent *     sv_next(struct irs_sv *);
static void                 sv_rewind(struct irs_sv *);
static void                 sv_minimize(struct irs_sv *);
#ifdef SV_RES_SETGET
static struct __res_state * sv_res_get(struct irs_sv *);
static void                 sv_res_set(struct irs_sv *,
                                       struct __res_state *,
                                       void (*)(void *));
#endif

/* Public */

struct irs_sv *
irs_dns_sv(struct irs_acc *this) {
    struct dns_p *dns = (struct dns_p *)this->private;
    struct irs_sv *sv;
    struct pvt *pvt;

    if ((pvt = memget(sizeof *pvt)) == NULL) {
        errno = ENOMEM;
        return (NULL);
    }
    memset(pvt, 0, sizeof *pvt);
    pvt->dns = dns;
    if ((sv = memget(sizeof *sv)) == NULL) {
        memput(pvt, sizeof *pvt);
        errno = ENOMEM;
        return (NULL);
    }
    memset(sv, 0x5e, sizeof *sv);
    sv->private = pvt;
    sv->byname = sv_byname;
    sv->byport = sv_byport;
    sv->next = sv_next;
    sv->rewind = sv_rewind;
    sv->close = sv_close;
    sv->minimize = sv_minimize;
#ifdef SV_RES_SETGET
    sv->res_get = sv_res_get;
    sv->res_set = sv_res_set;
#else
    sv->res_get = NULL; /* sv_res_get; */
    sv->res_set = NULL; /* sv_res_set; */
#endif
    return (sv);
}

/* Methods */

static void
sv_close(struct irs_sv *this) {
    struct pvt *pvt = (struct pvt *)this->private;

#if 0   /* Unneeded */
    if (pvt->serv.s_aliases)
        free(pvt->serv.s_aliases);
    if (pvt->svbuf)
        free(pvt->svbuf);
#endif

    if (pvt->res && pvt->free_res)
        (*pvt->free_res)(pvt->res);
    memput(pvt, sizeof *pvt);
    memput(this, sizeof *this);
}

static struct servent *
sv_byname(struct irs_sv *this, const char *name, const char *proto) {
    /* Dummy */
    UNUSED(this);
    UNUSED(name);
    UNUSED(proto);
    return (NULL);
}

static struct servent *
sv_byport(struct irs_sv *this, int port, const char *proto) {
    /* Dummy */
    UNUSED(this);
    UNUSED(port);
    UNUSED(proto);
    return (NULL);
}

static struct servent *
sv_next(struct irs_sv *this) {
    UNUSED(this);
    errno = ENODEV;
    return (NULL);
}

static void
sv_rewind(struct irs_sv *this) {
    UNUSED(this);
    /* NOOP */
}


static void
sv_minimize(struct irs_sv *this) {
    UNUSED(this);
    /* NOOP */
}

#ifdef SV_RES_SETGET
static struct __res_state *
sv_res_get(struct irs_sv *this) {
    /* Dummy */
    UNUSED(this);
    return (NULL);
}

static void
sv_res_set(struct irs_sv *this, struct __res_state * res,
           void (*free_res)(void *)) {
    /* Dummy */
    UNUSED(this);
    UNUSED(res);
    UNUSED(free_res);
    return (NULL);
}
#endif
