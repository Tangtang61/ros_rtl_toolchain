/*  $NetBSD: resolv.h,v 1.1.1.4.4.1 2007/05/17 00:39:25 jdc Exp $   */

/*
 * Copyright (c) 1983, 1987, 1989
 *    The Regents of the University of California.  All rights reserved.
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
 */

/*
 * Copyright (c) 2004 by Internet Systems Consortium, Inc. ("ISC")
 * Portions Copyright (c) 1996-1999 by Internet Software Consortium.
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

/*
 *  @(#)resolv.h    8.1 (Berkeley) 6/2/93
 *  Id: resolv.h,v 1.19.18.3 2005/08/25 04:43:51 marka Exp
 */

/*
   Copyright (C) 2019 By eSOL Co.,Ltd. Tokyo, Japan
   Modified to work with eMCOS.
*/

#ifndef _RESOLV_H_
#define _RESOLV_H_

#include <sys/param.h>
#include <sys/types.h>
#include <sys/cdefs.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/nameser.h>
#include "mcos_netdb.h"

/*
 * Revision information.  This is the release date in YYYYMMDD format.
 * It can change every day so the right thing to do with it is use it
 * in preprocessor commands such as "#if (__RES > 19931104)".  Do not
 * compare for equality; rather, use it to determine whether your resolver
 * is new enough to contain a certain feature.
 */

#define __RES   20030124

/*
 * This used to be defined in res_query.c, now it's in herror.c.
 * [XXX no it's not.  It's in irs/irs_data.c]
 * It was
 * never extern'd by any *.h file before it was placed here.  For thread
 * aware programs, the last h_errno value set is stored in res->h_errno.
 *
 * XXX: There doesn't seem to be a good reason for exposing RES_SET_H_ERRNO
 *      (and __h_errno_set) to the public via <resolv.h>.
 * XXX: __h_errno_set is really part of IRS, not part of the resolver.
 *  If somebody wants to build and use a resolver that doesn't use IRS,
 *  what do they do?  Perhaps something like
 *      #ifdef WANT_IRS
 *      # define RES_SET_H_ERRNO(r,x) __h_errno_set(r,x)
 *      #else
 *      # define RES_SET_H_ERRNO(r,x) (h_errno = (r)->res_h_errno = (x))
 *      #endif
 */

#define RES_SET_H_ERRNO(r,x) __h_errno_set(r,x)
struct __res_state; /* forward */
__BEGIN_DECLS
void __h_errno_set(struct __res_state *res, int err);
__END_DECLS

/*
 * Resolver configuration file.
 * Normally not present, but may contain the address of the
 * initial name server(s) to query and the domain search list.
 */

typedef enum { res_goahead, res_nextns, res_modified, res_done, res_error }
        res_sendhookact;

typedef res_sendhookact (*res_send_qhook)(struct sockaddr * const *,
                                           const u_char **, int *,
                                           u_char *, int, int *);
typedef res_sendhookact (*res_send_rhook)(const struct sockaddr *,
                                           const u_char *, int, u_char *,
                                           int, int *);
/*
 * Global defines and variables for resolver stub.
 */
#define MAXDFLSRCH              3       /* # default domain levels to try */
#define MAXDNSRCH               6       /* max # domains in search path */
#define LOCALDOMAINPARTS        2       /* min levels in name that is "local" */
#define RES_TIMEOUT             5       /* min. seconds between retries */
#define MAXRESOLVSORT           10      /* number of net to sort on */
#define RES_MAXNDOTS            15      /* should reflect bit field size */
#define RES_MAXRETRANS          30      /* only for resolv.conf/RES_OPTIONS */
#define RES_MAXRETRY            5       /* only for resolv.conf/RES_OPTIONS */
#define RES_DFLRETRY            2       /* Default #/tries. */
#define RES_MAXTIME             65535   /* Infinity, in milliseconds. */
struct __res_state_ext;

struct __res_state {
        int     retrans;                /* retransmission time interval */
        int     retry;                  /* number of times to retransmit */
        u_long  options;                /* option flags - see below. */
        int     nscount;                /* number of name servers */
        struct sockaddr_in
                nsaddr_list[MAXNS];     /* address of name server */
#define nsaddr  nsaddr_list[0]          /* for backward compatibility */
        u_short id;                     /* current message id */
        char    *dnsrch[MAXDNSRCH+1];   /* components of domain to search */
        char    defdname[256];          /* default domain (deprecated) */
        u_long  pfcode;                 /* RES_PRF_ flags - see below. */
        unsigned ndots:4;               /* threshold for initial abs. query */
        unsigned nsort:4;               /* number of elements in sort_list[] */
        char    unused[3];
        struct {
            struct in_addr  addr;
            u_int32_t       mask;
        } sort_list[MAXRESOLVSORT];
        res_send_qhook qhook;           /* query hook */
        res_send_rhook rhook;           /* response hook */
        int     res_h_errno;            /* last one set for this context */
        int     _vcsock;                /* PRIVATE: for res_send VC i/o */
        u_int   _flags;                 /* PRIVATE: see below */
        u_int   _pad;                   /* make _u 64 bit aligned */
        union {
            /* On an 32-bit arch this means 512b total. */
            char    pad[72 - 4*sizeof (int) - 2*sizeof (void *)];
            struct {
                u_int16_t   nscount;
                u_int16_t   nstimes[MAXNS];     /* ms. */
                int         nssocks[MAXNS];
                struct __res_state_ext *ext;    /* extention for IPv6 */
            } _ext;
        } _u;
};

typedef struct __res_state *res_state;

union res_sockaddr_union {
        struct sockaddr_in  sin;
        struct sockaddr_in6 sin6;
#ifdef ISC_ALIGN64
        int64_t             __align64;      /* 64bit alignment */
#else
        int32_t             __align32;      /* 32bit alignment */
#endif
        char                __space[128];   /* max size */
};

/*
 * Resolver flags (used to be discrete per-module statics ints).
 */
#define RES_F_VC        0x00000001      /* socket is TCP */
#define RES_F_CONN      0x00000002      /* socket is connected */
#define RES_F_EDNS0ERR  0x00000004      /* EDNS0 caused errors */
#define RES_F__UNUSED   0x00000008      /* (unused) */
#define RES_F_LASTMASK  0x000000F0      /* ordinal server of last res_nsend */
#define RES_F_LASTSHIFT 4               /* bit position of LASTMASK "flag" */
#define RES_GETLAST(res) (((res)._flags & RES_F_LASTMASK) >> RES_F_LASTSHIFT)

/* res_findzonecut2() options */
#define RES_EXHAUSTIVE  0x00000001      /* always do all queries */
#define RES_IPV4ONLY    0x00000002      /* IPv4 only */
#define RES_IPV6ONLY    0x00000004      /* IPv6 only */

/*
 * Resolver options (keep these in synch with res_debug.c, please)
 */
#define RES_INIT        0x00000001      /* address initialized */
#define RES_DEBUG       0x00000002      /* print debug messages */
#define RES_AAONLY      0x00000004      /* authoritative answers only (!IMPL)*/
#define RES_USEVC       0x00000008      /* use virtual circuit */
#define RES_PRIMARY     0x00000010      /* query primary server only (!IMPL) */
#define RES_IGNTC       0x00000020      /* ignore trucation errors */
#define RES_RECURSE     0x00000040      /* recursion desired */
#define RES_DEFNAMES    0x00000080      /* use default domain name */
#define RES_STAYOPEN    0x00000100      /* Keep TCP socket open */
#define RES_DNSRCH      0x00000200      /* search up local domain tree */
#define RES_INSECURE1   0x00000400      /* type 1 security disabled */
#define RES_INSECURE2   0x00000800      /* type 2 security disabled */
#define RES_NOALIASES   0x00001000      /* shuts off HOSTALIASES feature */
#define RES_USE_INET6   0x00002000      /* use/map IPv6 in gethostbyname() */
#define RES_ROTATE      0x00004000      /* rotate ns list after each query */
#define RES_NOCHECKNAME 0x00008000      /* do not check names for sanity. */
#define RES_KEEPTSIG    0x00010000      /* do not strip TSIG records */
#define RES_BLAST       0x00020000      /* blast all recursive servers */
#define RES_NOTLDQUERY  0x00100000      /* don't unqualified name as a tld */
#define RES_USE_DNSSEC  0x00200000      /* use DNSSEC using OK bit in OPT */
/* #define RES_DEBUG2   0x00400000 */   /* nslookup internal */
/* KAME extensions: use higher bit to avoid conflict with ISC use */
#define RES_USE_DNAME   0x10000000      /* use DNAME */
#define RES_USE_EDNS0   0x40000000      /* use EDNS0 if configured */
#define RES_NO_NIBBLE2  0x80000000      /* disable alternate nibble lookup */

#define RES_DEFAULT     (RES_RECURSE | RES_DEFNAMES | \
                         RES_DNSRCH | RES_NO_NIBBLE2)

/*
 * Resolver "pfcode" values.  Used by dig.
 */
#define RES_PRF_STATS   0x00000001
#define RES_PRF_UPDATE  0x00000002
#define RES_PRF_CLASS   0x00000004
#define RES_PRF_CMD     0x00000008
#define RES_PRF_QUES    0x00000010
#define RES_PRF_ANS     0x00000020
#define RES_PRF_AUTH    0x00000040
#define RES_PRF_ADD     0x00000080
#define RES_PRF_HEAD1   0x00000100
#define RES_PRF_HEAD2   0x00000200
#define RES_PRF_TTLID   0x00000400
#define RES_PRF_HEADX   0x00000800
#define RES_PRF_QUERY   0x00001000
#define RES_PRF_REPLY   0x00002000
#define RES_PRF_INIT    0x00004000
#define RES_PRF_TRUNC   0x00008000
/*                      0x00010000      */

/* Things involving an internal (static) resolver context. */
#ifdef _REENTRANT
__BEGIN_DECLS
extern struct __res_state *__res_state(void);
__END_DECLS
#define _res (*__res_state())
#endif

#define dn_comp                 __dn_comp
#define dn_expand               __dn_expand
#define dn_skipname             __dn_skipname
#define res_dnok                __res_dnok
#define res_hnok                __res_hnok
#define res_hostalias           __res_hostalias
#define res_nameinquery         __res_nameinquery
#define res_nclose              __res_nclose
#define res_ninit               __res_ninit
#define res_nmkquery            __res_nmkquery
#define res_nquery              __res_nquery
#define res_nquerydomain        __res_nquerydomain
#define res_nsearch             __res_nsearch
#define res_nsend               __res_nsend
#define res_queriesmatch        __res_queriesmatch
#define res_randomid            __res_randomid
#define res_nopt                __res_nopt
#define res_ndestroy            __res_ndestroy
#define res_setservers          __res_setservers
#define res_getservers          __res_getservers
#define res_get_nibblesuffix    __res_get_nibblesuffix
#define res_get_nibblesuffix2   __res_get_nibblesuffix2
#define res_ourserver_p         __res_ourserver_p

__BEGIN_DECLS

int             res_hnok(const char * dn);
int             res_dnok(const char * dn);
int             dn_skipname (const u_char * ptr, const u_char * oem);
int             dn_comp(const char * src, u_char * dst, int dstsiz,
                         u_char ** dnptrs, u_char ** lastdnptr);
int             dn_expand(const u_char * msg, const u_char * oem, const u_char * src,
                           char * dst, int dstsiz);
u_int           res_randomid (void);
int             res_nameinquery(const char * name, int type, int class, const u_char * buf,
                                 const u_char * oem);
int             res_queriesmatch(const u_char * buf1, const u_char * oem1,
                                  const u_char * buf2, const u_char * oem2);
/* Things involving a resolver context. */
int             res_ninit(res_state statp);
const char *    res_hostalias(const res_state statp, const char * name,
                               char * dst, size_t siz);
int             res_nquery(res_state statp, const char * name, int class, int type,
                            u_char * answer, int anslen);
int             res_nsearch(res_state statp, const char * name, int class, int type, u_char * answer,
                             int anslen);
int             res_nquerydomain(res_state statp, const char * name, const char * domain,
                                  int class, int type, u_char * answer, int anslen);
int             res_nmkquery(res_state statp, int op, const char * dname, int class, int type,
                              const u_char * data, int datalen, const u_char * newrr_in,
                              u_char * buf, int buflen);
int             res_nsend(res_state statp, const u_char * buf, int buflen, u_char * ans, int anssiz);
void            res_nclose(res_state statp);
int             res_nopt(res_state statp, int n0, u_char * buf, int buflen, int anslen);
int             __res_vinit(res_state statp, int preinit);
const char *    res_get_nibblesuffix(res_state statp);
const char *    res_get_nibblesuffix2(res_state statp);
void            res_ndestroy(res_state statp);
void            res_setservers(res_state statp,
                                const union res_sockaddr_union * set, int cnt);
int             res_getservers(res_state statp,
                                union res_sockaddr_union * set, int cnt);

__END_DECLS

#endif /* !_RESOLV_H_ */
