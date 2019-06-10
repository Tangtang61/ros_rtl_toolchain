/*      $NetBSD: in.h,v 1.78 2007/02/17 22:34:11 dyoung Exp $   */

/*
 * Copyright (c) 1982, 1986, 1990, 1993
 *      The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
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
 *
 *      @(#)in.h        8.3 (Berkeley) 1/3/94
 */

/*
 * Constants and structures defined by the internet system,
 * Per RFC 790, September 1981, and numerous additions.
 */

/*
   Copyright (C) 2019 By eSOL Co.,Ltd. Tokyo, Japan
   Modified to work with eMCOS.
*/

/*============================================================================
 netinet/in.h       POSIX Layer  INET sockets definitions
============================================================================*/

#ifndef __NETINET_IN_H__
#define __NETINET_IN_H__

#include <inttypes.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/cdefs.h>

/*
 * Protocols
 */
#define IPPROTO_IP              0               /* dummy for IP */
#define IPPROTO_ICMP            1               /* control message protocol */
#define IPPROTO_TCP             6               /* tcp */
#define IPPROTO_UDP             17              /* user datagram protocol */
#define IPPROTO_IDP             22              /* xns idp */
#define IPPROTO_IPV6            41              /* IP6 header */
#define IPPROTO_RAW             255             /* raw IP packet */

/*
 * Internet address (a structure for historical reasons)
 */
typedef	__uint32_t	in_addr_t;
struct in_addr {
    in_addr_t s_addr;
} __attribute__((__packed__));

/*

 * Socket address, internet style.
 */
typedef	__uint16_t	in_port_t;
struct sockaddr_in {
        sa_family_t     sin_family;
        in_port_t       sin_port;
        struct in_addr  sin_addr;
};

/* */
#define __IPADDR(x)         ((uint32_t)(x))

#define INADDR_ANY          __IPADDR(0x00000000)
#define INADDR_BROADCAST    __IPADDR(0xffffffff)    /* must be masked */

#define INET_ADDRSTRLEN     16

#define IN_CLASSA(i)        (((uint32_t)(i) & __IPADDR(0x80000000)) == \
                             __IPADDR(0x00000000))
#define IN_CLASSA_NET       __IPADDR(0xff000000)
#define IN_CLASSA_NSHIFT    24
#define IN_CLASSA_HOST      __IPADDR(0x00ffffff)
#define IN_CLASSA_MAX       128

#define IN_CLASSB(i)        (((uint32_t)(i) & __IPADDR(0xc0000000)) == \
                             __IPADDR(0x80000000))
#define IN_CLASSB_NET       __IPADDR(0xffff0000)
#define IN_CLASSB_NSHIFT    16
#define IN_CLASSB_HOST      __IPADDR(0x0000ffff)
#define IN_CLASSB_MAX       65536

#define IN_CLASSC(i)        (((uint32_t)(i) & __IPADDR(0xe0000000)) == \
                             __IPADDR(0xc0000000))
#define IN_CLASSC_NET       __IPADDR(0xffffff00)
#define IN_CLASSC_NSHIFT    8
#define IN_CLASSC_HOST      __IPADDR(0x000000ff)

#define IN_LOOPBACKNET      127         /* official! */

#include <netinet/in6.h>

#define	INADDR_NONE		    ((in_addr_t) 0xffffffff)
#define INADDR_LOOPBACK	    ((in_addr_t) 0x7f000001)

#ifndef __USE_KERNEL_IPV6_DEFS
enum
  {
    IPPROTO_HOPOPTS = 0,
#define IPPROTO_HOPOPTS		IPPROTO_HOPOPTS
    IPPROTO_ROUTING = 43,
#define IPPROTO_ROUTING		IPPROTO_ROUTING
    IPPROTO_FRAGMENT = 44,
#define IPPROTO_FRAGMENT	IPPROTO_FRAGMENT
    IPPROTO_ICMPV6 = 58,
#define IPPROTO_ICMPV6		IPPROTO_ICMPV6
    IPPROTO_NONE = 59,
#define IPPROTO_NONE		IPPROTO_NONE
    IPPROTO_DSTOPTS = 60,
#define IPPROTO_DSTOPTS		IPPROTO_DSTOPTS
    IPPROTO_MH = 135
#define IPPROTO_MH		IPPROTO_MH
  };
#endif

struct ip_mreq  {
	struct in_addr imr_multiaddr;
	struct in_addr imr_interface;
};

#define  IP_OPTIONS_OFS    (0x3000)
#define  IP_OPTIONS        (IP_OPTIONS_OFS + 1)
#define  IP_HDRINCL        (IP_OPTIONS_OFS + 2)
#define  IP_TOS            (IP_OPTIONS_OFS + 3) 
#define  IP_TTL_OPT        (IP_OPTIONS_OFS + 4)
#define  IP_RECVOPTS       (IP_OPTIONS_OFS + 5)
#define  IP_RECVRETOPTS    (IP_OPTIONS_OFS + 6)
#define  IP_RECVDSTADDR    (IP_OPTIONS_OFS + 7)
#define  IP_RETOPTS        (IP_OPTIONS_OFS + 8)
#define  IP_MULTICAST_IF   (IP_OPTIONS_OFS + 9)
#define  IP_MULTICAST_TTL  (IP_OPTIONS_OFS + 10)
#define  IP_MULTICAST_LOOP (IP_OPTIONS_OFS + 11)
#define  IP_ADD_MEMBERSHIP (IP_OPTIONS_OFS + 12)
#define  IP_DROP_MEMBERSHIP (IP_OPTIONS_OFS + 13)
#define  IP_SCOPEID        (IP_OPTIONS_OFS + 14)

#ifndef  IP_TTL
#define  IP_TTL   64
#endif

__BEGIN_DECLS
uint32_t    htonl (uint32_t) __attribute__((__const__));
uint16_t    htons (uint16_t) __attribute__((__const__));
uint32_t    ntohl (uint32_t) __attribute__((__const__));
uint16_t    ntohs (uint16_t) __attribute__((__const__));
__END_DECLS

#if _BYTE_ORDER == _BIG_ENDIAN && !defined(lint)
#define ntohl(x)    (x)
#define ntohs(x)    (x)
#define htonl(x)    (x)
#define htons(x)    (x)

#define NTOHL(x)    (void) (x)
#define NTOHS(x)    (void) (x)
#define HTONL(x)    (void) (x)
#define HTONS(x)    (void) (x)

#else
#define NTOHL(x)    (x) = ntohl((uint32_t)(x))
#define NTOHS(x)    (x) = ntohs((uint16_t)(x))
#define HTONL(x)    (x) = htonl((uint32_t)(x))
#define HTONS(x)    (x) = htons((uint16_t)(x))
#endif

#endif /* !__NETINET_IN_H__ */
