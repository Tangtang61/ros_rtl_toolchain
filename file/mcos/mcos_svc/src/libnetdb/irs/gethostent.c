/*  $NetBSD: gethostent.c,v 1.1.1.3.4.1 2007/05/17 00:39:49 jdc Exp $       */

/*
 * Copyright (c) 2004 by Internet Systems Consortium, Inc. ("ISC")
 * Copyright (c) 1996-1999 by Internet Software Consortium.
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
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <netdb.h>
#include "resolv.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "irs.h"
#include "isc/memcluster.h"

#include "port_after.h"

#include "irs_p.h"
#include "irs_data.h"

/* Definitions */

struct pvt {
    char *          aliases[1];
    char *          addrs[2];
    char            addr[NS_IN6ADDRSZ];
    char            name[NS_MAXDNAME + 1];
    struct hostent  host;
};

/* Forward */

static struct net_data *init(void);
static void             freepvt(struct net_data * net_data);
static struct hostent  *fakeaddr(const char * name, int af, struct net_data * net_data);


/* Public */

struct hostent *
gethostbyname(const char *name) {
    struct net_data *net_data = init();

    return (gethostbyname_p(name, net_data));
}

struct hostent *
gethostbyaddr(const char *addr, socklen_t len, int af) {
    struct net_data *net_data = init();

    return (gethostbyaddr_p(addr, len, af, net_data));
}

struct hostent *
gethostent() {
    struct net_data *net_data = init();

    return (gethostent_p(net_data));
}

void
sethostent(int stayopen) {
    struct net_data *net_data = init();
    sethostent_p(stayopen, net_data);
}


void
endhostent() {
    struct net_data *net_data = init();
    endhostent_p(net_data);
}

/* Shared private. */

struct hostent *
gethostbyname_p(const char *name, struct net_data *net_data) {
    struct hostent *hp;

    if (!net_data)
        return (NULL);

    if (net_data->res->options & RES_USE_INET6) {
        hp = gethostbyname2_p(name, AF_INET6, net_data);
        if (hp)
            return (hp);
    }
    return (gethostbyname2_p(name, AF_INET, net_data));
}

struct hostent *
gethostbyname2_p(const char *name, int af, struct net_data *net_data) {
    struct irs_ho *ho;
    char *tmp;
    struct hostent *hp;
    const char *cp;
    char **hap;

    if (net_data == NULL || (ho = net_data->ho) == NULL)
        return (NULL);
    if (net_data->ho_stayopen && net_data->ho_last &&
        net_data->ho_last->h_addrtype == af) {
        if (ns_samename(name, net_data->ho_last->h_name) == 1)
            return (net_data->ho_last);
        for (hap = net_data->ho_last->h_aliases; hap && *hap; hap++)
            if (ns_samename(name, *hap) == 1)
                return (net_data->ho_last);
    }
    
    tmp = (char *)malloc(NS_MAXDNAME);
    if (tmp == NULL) {
        RES_SET_H_ERRNO(net_data->res, NETDB_INTERNAL);
        errno = ENOMEM;
        return (NULL);
    }
    
    if (strchr(name, '.') == NULL && (cp = res_hostalias(net_data->res, name,
                                      tmp, NS_MAXDNAME)) != NULL)
        name = cp;
    if ((hp = fakeaddr(name, af, net_data)) != NULL) {
        if (tmp != NULL)
            free(tmp);
        return (hp);
    }
    net_data->ho_last = (*ho->byname2)(ho, name, af);
    if (!net_data->ho_stayopen)
        endhostent();
    if (tmp != NULL)
        free(tmp);
    return (net_data->ho_last);
}

struct hostent *
gethostbyaddr_p(const char *addr, socklen_t len, int af, struct net_data *net_data) {
    struct irs_ho *ho;
    char **hap;

    if (net_data == NULL || (ho = net_data->ho) == NULL)
        return (NULL);
    if (net_data->ho_stayopen && net_data->ho_last &&
        net_data->ho_last->h_length == len)
        for (hap = net_data->ho_last->h_addr_list;
             hap && *hap;
             hap++)
            if (!memcmp(addr, *hap, len))
                return (net_data->ho_last);
    net_data->ho_last = (*ho->byaddr)(ho, addr, len, af);
    if (!net_data->ho_stayopen)
        endhostent();
    return (net_data->ho_last);
}


struct hostent *
gethostent_p(struct net_data *net_data) {
    struct irs_ho *ho;
    struct hostent *hp;

    if (net_data == NULL || (ho = net_data->ho) == NULL)
        return (NULL);
    while ((hp = (*ho->next)(ho)) != NULL &&
           hp->h_addrtype == AF_INET6 &&
           (net_data->res->options & RES_USE_INET6) == 0U)
        continue;
    net_data->ho_last = hp;
    return (net_data->ho_last);
}


void
sethostent_p(int stayopen, struct net_data *net_data) {
    struct irs_ho *ho;

    if (net_data == NULL || (ho = net_data->ho) == NULL)
        return;
    freepvt(net_data);
    (*ho->rewind)(ho);
    net_data->ho_stayopen = (stayopen != 0);
    if (stayopen == 0)
        net_data_minimize(net_data);
}

void
endhostent_p(struct net_data *net_data) {
    struct irs_ho *ho;

    if ((net_data != NULL) && ((ho = net_data->ho) != NULL))
        (*ho->minimize)(ho);
}

static struct net_data *
init() {
    struct net_data *net_data;

    if ((net_data = net_data_init(NULL)) == NULL)
        goto label_error;
    if (!net_data->ho) {
        net_data->ho = (*net_data->irs->ho_map)(net_data->irs);
        if (!net_data->ho || !net_data->res) {
  label_error:
            errno = EIO;
            if (net_data && net_data->res)
                    RES_SET_H_ERRNO(net_data->res, NETDB_INTERNAL);
            return (NULL);
        }

        (*net_data->ho->res_set)(net_data->ho, net_data->res, NULL);
    }

    return (net_data);
}

static void
freepvt(struct net_data *net_data) {
    if (net_data->ho_data) {
        free(net_data->ho_data);
        net_data->ho_data = NULL;
    }
}

static struct hostent *
fakeaddr(const char *name, int af, struct net_data *net_data) {
    struct pvt *pvt;

    freepvt(net_data);
    net_data->ho_data = malloc(sizeof (struct pvt));
    if (!net_data->ho_data) {
        errno = ENOMEM;
        RES_SET_H_ERRNO(net_data->res, NETDB_INTERNAL);
        return (NULL);
    }
    pvt = net_data->ho_data;
#ifndef __bsdi__
    /*
     * Unlike its forebear(inet_aton), our friendly inet_pton() is strict
     * in its interpretation of its input, and it will only return "1" if
     * the input string is a formally valid(and thus unambiguous with
     * respect to host names) internet address specification for this AF.
     *
     * This means "telnet 0xdeadbeef" and "telnet 127.1" are dead now.
     */
    if (inet_pton(af, name, pvt->addr) != 1) {
#else
    /* BSDI XXX
     * We put this back to inet_aton -- we really want the old behavior
     * Long live 127.1...
     */
    if ((af != AF_INET ||
        inet_aton(name, (struct in_addr *)pvt->addr) != 1) &&
        inet_pton(af, name, pvt->addr) != 1) {
#endif
        RES_SET_H_ERRNO(net_data->res, HOST_NOT_FOUND);
        return (NULL);
    }
    strncpy(pvt->name, name, NS_MAXDNAME);
    pvt->name[NS_MAXDNAME] = '\0';
    if (af == AF_INET && (net_data->res->options & RES_USE_INET6) != 0U) {
        map_v4v6_address(pvt->addr, pvt->addr);
        af = AF_INET6;
    }
    pvt->host.h_addrtype = af;
    switch(af) {
    case AF_INET:
        pvt->host.h_length = NS_INADDRSZ;
        break;
    case AF_INET6:
        pvt->host.h_length = NS_IN6ADDRSZ;
        break;
    default:
        errno = EAFNOSUPPORT;
        RES_SET_H_ERRNO(net_data->res, NETDB_INTERNAL);
        return (NULL);
    }
    pvt->host.h_name = pvt->name;
    pvt->host.h_aliases = pvt->aliases;
    pvt->aliases[0] = NULL;
    pvt->addrs[0] = (char *)pvt->addr;
    pvt->addrs[1] = NULL;
    pvt->host.h_addr_list = pvt->addrs;
    RES_SET_H_ERRNO(net_data->res, NETDB_SUCCESS);
    return (&pvt->host);
}
