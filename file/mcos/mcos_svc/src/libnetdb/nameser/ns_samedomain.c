/*  $NetBSD: ns_samedomain.c,v 1.1.1.3.4.1 2007/05/17 00:40:09 jdc Exp $    */

/*
 * Copyright (c) 2004 by Internet Systems Consortium, Inc. ("ISC")
 * Copyright (c) 1995,1999 by Internet Software Consortium.
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
#include "port_before.h"

#include <stdlib.h>
#include <sys/types.h>
#include <arpa/nameser.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include "port_after.h"

/*
 *  make a canonical copy of domain name "src"
 *
 * notes:
 * \code
 *  foo -> foo.
 *  foo. -> foo.
 *  foo.. -> foo.
 *  foo\. -> foo\..
 *  foo\\. -> foo\\.
 * \endcode
 */

int
ns_makecanon(const char *src, char *dst, size_t dstsize) {
    size_t n = strlen(src);

    if (n + sizeof "." > dstsize) {         /* Note: sizeof == 2 */
        errno = EMSGSIZE;
        return (-1);
    }
    strcpy(dst, src);
    while (n >= 1U && dst[n - 1] == '.')        /* Ends in "." */
        if (n >= 2U && dst[n - 2] == '\\' &&    /* Ends in "\." */
            (n < 3U || dst[n - 3] != '\\'))     /* But not "\\." */
            break;
        else
            dst[--n] = '\0';
    dst[n++] = '.';
    dst[n] = '\0';
    return (0);
}

/*
 *  determine whether domain name "a" is the same as domain name "b"
 *
 * return:
 *\li   -1 on error
 *\li   0 if names differ
 *\li   1 if names are the same
 */

int
ns_samename(const char *a, const char *b) {
    char *ta; 
    char *tb;
    int   ret;

    ta = (char *)malloc(NS_MAXDNAME*2);
    if (ta != NULL) {
        tb = (char *)(ta + NS_MAXDNAME);
        if (ns_makecanon(a, ta, NS_MAXDNAME) < 0 ||
            ns_makecanon(b, tb, NS_MAXDNAME) < 0)
            ret = -1;
        if (strcasecmp(ta, tb) == 0)
            ret = 1;
        else
            ret = 0;
        if (ta != NULL)
            free(ta);
    } else {
        errno = ENOMEM;
        ret = -1;
    }
    return (ret);
}
