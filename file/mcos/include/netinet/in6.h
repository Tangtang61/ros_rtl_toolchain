/*      $NetBSD: in6.h,v 1.59 2007/02/17 22:34:13 dyoung Exp $  */
/*      $KAME: in6.h,v 1.83 2001/03/29 02:55:07 jinmei Exp $    */

/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
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
 * 3. Neither the name of the project nor the names of its contributors
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
 *
 *      @(#)in6.h        8.3 (Berkeley) 1/3/94
 */

#ifndef __NETINET_IN6_H__
#define __NETINET_IN6_H__

#include <string.h> /* for memcmp() */

/*
 * IPv6 address
 */
struct in6_addr {
    uint8_t s6_addr[16];
};

struct sockaddr_in6 {
        sa_family_t     sin6_family;    /* AF_INET6 (sa_family_t) */
        in_port_t       sin6_port;      /* Transport layer port */
        uint32_t        sin6_flowinfo;  /* IP6 flow information */
        struct in6_addr sin6_addr;      /* IP6 address */
        uint32_t        sin6_scope_id;  /* scope zone index */
};

#define IN6_ARE_ADDR_EQUAL(a,b) \
           (memcmp(&(a)->s6_addr[0], &(b)->s6_addr[0], sizeof(struct in6_addr)) == 0)

#define __IPV6_ADDR_MC_SCOPE(a)         ((a)->s6_addr[1] & 0x0f)

#define  __IPV6_ADDR_SCOPE_NODELOCAL    0x01
#define  __IPV6_ADDR_SCOPE_LINKLOCAL    0x02
#define  __IPV6_ADDR_SCOPE_SITELOCAL    0x05
#define  __IPV6_ADDR_SCOPE_ORGLOCAL     0x08
#define  __IPV6_ADDR_SCOPE_GLOBAL       0x0e

/*
 * Definition of some useful macros to handle IP6 addresses
 */
#define IN6ADDR_ANY_INIT \
        {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}

#define IN6ADDR_LOOPBACK_INIT \
        {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 }}

/* IPv6 Wildcard Address (::) and Loopback Address (::1) defined in RFC2553
 * NOTE: Be aware the IN6ADDR_* constants and in6addr_* externals are defined
 * in network byte order, not in host byte order as are the IPv4 equivalents
 */

extern const struct in6_addr in6addr_any;
extern const struct in6_addr in6addr_loopback;

/*
 * Argument structure for IPV6_JOIN_GROUP and IPV6_LEAVE_GROUP.
 */
struct ipv6_mreq {
        struct in6_addr ipv6mr_multiaddr;
        unsigned int    ipv6mr_interface;
};

#define IPV6_UNICAST_HOPS       4  /* int; IP6 hops */
#define IPV6_MULTICAST_IF       9  /* u_int; set/get IP6 multicast i/f  */
#define IPV6_MULTICAST_HOPS     10 /* int; set/get IP6 multicast hops */
#define IPV6_MULTICAST_LOOP     11 /* u_int; set/get IP6 multicast loopback */
#define IPV6_JOIN_GROUP         12 /* ip6_mreq; join a group membership */
#define IPV6_LEAVE_GROUP        13 /* ip6_mreq; leave a group membership */
#define IPV6_V6ONLY             27 /* bool; make AF_INET6 sockets v6 only */

#define INET6_ADDRSTRLEN        46

/*
 * Unspecified
 */
#define IN6_IS_ADDR_UNSPECIFIED(a)      \
        ((*(const uint32_t *)(const void *)(&(a)->s6_addr[0]) == 0) &&  \
         (*(const uint32_t *)(const void *)(&(a)->s6_addr[4]) == 0) &&  \
         (*(const uint32_t *)(const void *)(&(a)->s6_addr[8]) == 0) &&  \
         (*(const uint32_t *)(const void *)(&(a)->s6_addr[12]) == 0))

/*
 * Loopback
 */
#define IN6_IS_ADDR_LOOPBACK(a)         \
        ((*(const uint32_t *)(const void *)(&(a)->s6_addr[0]) == 0) &&  \
         (*(const uint32_t *)(const void *)(&(a)->s6_addr[4]) == 0) &&  \
         (*(const uint32_t *)(const void *)(&(a)->s6_addr[8]) == 0) &&  \
         (*(const uint32_t *)(const void *)(&(a)->s6_addr[12]) == ntohl(1)))

/*
 * Multicast
 */
#define IN6_IS_ADDR_MULTICAST(a)        ((a)->s6_addr[0] == 0xff)

#define IN6_IS_ADDR_LINKLOCAL(a)        \
        (((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0x80))
#define IN6_IS_ADDR_SITELOCAL(a)        \
        (((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0xc0))

#define IN6_IS_ADDR_MC_NODELOCAL(a)     \
        (IN6_IS_ADDR_MULTICAST(a) &&    \
         (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_NODELOCAL))
#define IN6_IS_ADDR_MC_LINKLOCAL(a)     \
        (IN6_IS_ADDR_MULTICAST(a) &&    \
         (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_LINKLOCAL))
#define IN6_IS_ADDR_MC_SITELOCAL(a)     \
        (IN6_IS_ADDR_MULTICAST(a) &&    \
         (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_SITELOCAL))
#define IN6_IS_ADDR_MC_ORGLOCAL(a)      \
        (IN6_IS_ADDR_MULTICAST(a) &&    \
         (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_ORGLOCAL))
#define IN6_IS_ADDR_MC_GLOBAL(a)        \
        (IN6_IS_ADDR_MULTICAST(a) &&    \
         (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_GLOBAL))
/*
 * Mapped
 */
#define IN6_IS_ADDR_V4MAPPED(a)               \
        ((*(const uint32_t *)(const void *)(&(a)->s6_addr[0]) == 0) &&  \
         (*(const uint32_t *)(const void *)(&(a)->s6_addr[4]) == 0) &&  \
         (*(const uint32_t *)(const void *)(&(a)->s6_addr[8]) == ntohl(0x0000ffff)))

/*
 * IPv4 compatible
 */
#define IN6_IS_ADDR_V4COMPAT(a)         \
        ((*(const uint32_t *)(const void *)(&(a)->s6_addr[0]) == 0) &&  \
         (*(const uint32_t *)(const void *)(&(a)->s6_addr[4]) == 0) &&  \
         (*(const uint32_t *)(const void *)(&(a)->s6_addr[8]) == 0) &&  \
         (*(const uint32_t *)(const void *)(&(a)->s6_addr[12]) != 0) && \
         (*(const uint32_t *)(const void *)(&(a)->s6_addr[12]) != ntohl(1)))

#endif /* !__NETINET_IN6_H__ */
