/*  $NetBSD: netdb.h,v 1.1.1.3.4.1 2007/05/17 00:39:23 jdc Exp $    */

/*
 * ++Copyright++ 1980, 1983, 1988, 1993
 * -
 * Copyright (c) 1980, 1983, 1988, 1993
 *  The Regents of the University of California.  All rights reserved.
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
 * -
 * Portions Copyright (c) 1993 by Digital Equipment Corporation.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies, and that
 * the name of Digital Equipment Corporation not be used in advertising or
 * publicity pertaining to distribution of the document or software without
 * specific, written prior permission.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND DIGITAL EQUIPMENT CORP. DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS.   IN NO EVENT SHALL DIGITAL EQUIPMENT
 * CORPORATION BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 * -
 * Portions Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
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
 *    This product includes software developed by WIDE Project and
 *    its contributors.
 * 4. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * -
 * --Copyright--
 */

/*
 *      @(#)netdb.h 8.1 (Berkeley) 6/2/93
 *  Id: netdb.h,v 1.15.18.6 2006/10/02 01:23:09 marka Exp
 */

#ifndef _NETDB_H_
#define _NETDB_H_

#if !defined COMPILER_RESTRICT
#if defined __cplusplus
#define COMPILER_RESTRICT
#else /* __cplusplus */
#define COMPILER_RESTRICT restrict
#endif /* __cplusplus */
#endif /* COMPILER_RESTRICT */

#include <sys/param.h>
#include <sys/types.h>
#include <sys/cdefs.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#define __h_errno __h_errno_location

__BEGIN_DECLS
extern int * __h_errno (void);
__END_DECLS

#define h_errno (*__h_errno())


/*
 * Structures returned by network data base library.  All addresses are
 * supplied in host order, and returned in network order (suitable for
 * use in system calls).
 */
struct  hostent {
    char    *h_name;            /* official name of host */
    char    **h_aliases;        /* alias list */
    int     h_addrtype;         /* host address type */
    int     h_length;           /* length of address */
    char    **h_addr_list;      /* list of addresses from name server */
#define h_addr  h_addr_list[0]  /* address, for backward compatiblity */
};

/*
 * Assumption here is that a network number
 * fits in an unsigned long -- probably a poor one.
 */
struct  netent {
    char        *n_name;        /* official name of net */
    char        **n_aliases;    /* alias list */
    int         n_addrtype;     /* net address type */
    uint32_t    n_net;          /* network # */
};

struct  servent {
    char    *s_name;            /* official service name */
    char    **s_aliases;        /* alias list */
    int     s_port;             /* port # */
    char    *s_proto;           /* protocol to use */
};

struct  protoent {
    char    *p_name;            /* official protocol name */
    char    **p_aliases;        /* alias list */
    int     p_proto;            /* protocol # */
};

struct  addrinfo {
    int     ai_flags;           /* AI_PASSIVE, AI_CANONNAME */
    int     ai_family;          /* PF_xxx */
    int     ai_socktype;        /* SOCK_xxx */
    int     ai_protocol;        /* 0 or IPPROTO_xxx for IPv4 and IPv6 */
    socklen_t   ai_addrlen;
    struct sockaddr *ai_addr;   /* binary address */
    char    *ai_canonname;      /* canonical name for hostname */
    struct addrinfo *ai_next;   /* next structure in linked list */
};

/*
 * Error return codes from gethostbyname() and gethostbyaddr()
 * (left in extern int h_errno).
 */

#define NETDB_INTERNAL  -1      /* see errno */
#define NETDB_SUCCESS   0       /* no problem */
#define HOST_NOT_FOUND  1       /* Authoritative Answer Host not found */
#define TRY_AGAIN       2       /* Non-Authoritive Host not found, or SERVERFAIL */
#define NO_RECOVERY     3       /* Non recoverable errors, FORMERR, REFUSED, NOTIMP */
#define NO_DATA         4       /* Valid name, no data record of requested type */
#define NO_ADDRESS      NO_DATA /* no address, look for MX record */

/*
 * Error return codes from getaddrinfo()
 */
#define EAI_AGAIN       1       /* temporary failure in name resolution */
#define EAI_BADFLAGS    2       /* invalid value for ai_flags */
#define EAI_FAIL        3       /* non-recoverable failure in name resolution */
#define EAI_FAMILY      4       /* ai_family not supported */
#define EAI_MEMORY      5       /* memory allocation failure */
#define EAI_NONAME      6       /* hostname nor servname provided, or not known */
#define EAI_SERVICE     7       /* servname not supported for ai_socktype */
#define EAI_SOCKTYPE    8       /* ai_socktype not supported */
#define EAI_SYSTEM      9       /* system error returned in errno */
#define EAI_OVERFLOW    10      /* argument buffer overflowed */
#define EAI_BADHINTS    11      /* invalid value for hints */
#define EAI_MAX         12

/*
 * Flag values for getaddrinfo()
 */
#define AI_PASSIVE      0x00000001  /* get address to use bind() */
#define AI_CANONNAME    0x00000002  /* fill ai_canonname */
#define AI_NUMERICHOST  0x00000004  /* prevent host name resolution */
#define AI_NUMERICSERV  0x00000008  /* prevent service name resolution */
#define AI_ADDRCONFIG   0x00000040  /* Use configuration of this host to choose returned address type */
#define AI_MASK         (AI_PASSIVE | AI_CANONNAME | AI_NUMERICHOST | AI_NUMERICSERV | AI_ADDRCONFIG)

/*
 * Flag values for getipnodebyname()
 */
#define AI_V4MAPPED     0x00000010  /* IPv4 mapped addresses are acceptable */
#define AI_ALL          0x00000020  /* Return IPv4 mapped and IPv6 addresses */
#define AI_DEFAULT      (AI_V4MAPPED | AI_ADDRCONFIG)

/*
 * Constants for getnameinfo()
 */
#define NI_MAXHOST  1025
#define NI_MAXSERV  32

/*
 * Flag values for getnameinfo()
 */
#define NI_NOFQDN       0x00000001  /* Only return nodename portion */
#define NI_NUMERICHOST  0x00000002  /* Don't try to look up hostname */
#define NI_NAMEREQD     0x00000004  /* Don't return numeric addresses */
#define NI_NUMERICSERV  0x00000008  /* Don't convert port number to name */
#define NI_DGRAM        0x00000010  /* Look up UDP service rather than TCP */
#define NI_NUMERICSCOPE 0x00000020  /* Returns the numeric form of the scope identifier */


__BEGIN_DECLS
void            endhostent(void);
void            endservent(void);
struct hostent  *gethostbyaddr(const char *, socklen_t, int);
struct hostent  *gethostbyname(const char *);
struct hostent  *gethostent(void);
struct servent  *getservbyname(const char *, const char *);
struct servent  *getservbyport(int, const char *);
struct servent  *getservent(void);
void            sethostent(int);
void            setservent(int);
int             getaddrinfo(const char * COMPILER_RESTRICT, const char * COMPILER_RESTRICT,
                             const struct addrinfo * COMPILER_RESTRICT, struct addrinfo ** COMPILER_RESTRICT);
void            freeaddrinfo(struct addrinfo *);
const char      *gai_strerror(int);
int             getnameinfo(const struct sockaddr * COMPILER_RESTRICT sa, socklen_t salen,
                            char * COMPILER_RESTRICT node, socklen_t nodelen,
                            char * COMPILER_RESTRICT service, socklen_t servicelen, int flags);
__END_DECLS

#endif /* !_NETDB_H_ */
