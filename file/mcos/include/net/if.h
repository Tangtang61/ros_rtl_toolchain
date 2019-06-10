/* 
 * Copyright (C) 2019 eSOL Co.,Ltd. Tokyo, Japan
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE FREEBSD PROJECT ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL THE FREEBSD PROJECT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/****************************************************************************
 net/if.h - network interface header
****************************************************************************/

#ifndef _NET_IF_H
#define _NET_IF_H

#include <sys/socket.h>

#define IF_NAMESIZE     16

#define IFF_UP          0x1
#define IFF_BROADCAST   0x2
#define IFF_DEBUG       0x4
#define IFF_LOOPBACK    0x8
#define IFF_POINTOPOINT 0x10
#define IFF_SMART       0x20
#define IFF_RUNNING     0x40
#define IFF_NOARP       0x80
#define IFF_PROMISC     0x100
#define IFF_ALLMULTI    0x200
#define IFF_OACTIVE     0x400
#define IFF_SIMPLEX     0x800
#define IFF_LINK0       0x1000
#define IFF_LINK1       0x2000
#define IFF_LINK2       0x4000
#define IFF_ALTPHYS     IFF_LINK2
#define IFF_MULTICAST   0x8000
#define IFF_POLLING     0x10000
#define IFF_PPROMISC    0x20000
#define IFF_MONITOR     0x40000
#define IFF_STATICARP   0x80000
#define IFF_NEEDSGIANT  0x100000

struct ifmap
{
    unsigned long int mem_start;
    unsigned long int mem_end;
    unsigned short int base_addr;
    unsigned char irq;
    unsigned char dma;
    unsigned char port;
};

struct ifreq
{
# define IFHWADDRLEN 6
# define IFNAMSIZ IF_NAMESIZE
    union
    {
        char ifrn_name[IFNAMSIZ];
    } ifr_ifrn;

    union
    {
        struct sockaddr ifru_addr;
        struct sockaddr ifru_dstaddr;
        struct sockaddr ifru_broadaddr;
        struct sockaddr ifru_netmask;
        struct sockaddr ifru_hwaddr;
        short int ifru_flags;
        int ifru_ivalue;
        int ifru_mtu;
        struct ifmap ifru_map;
        char ifru_slave[IFNAMSIZ];
        char ifru_newname[IFNAMSIZ];
        char *ifru_data;
    } ifr_ifru;
};

#define ifr_name        ifr_ifrn.ifrn_name
#define ifr_hwaddr      ifr_ifru.ifru_hwaddr
#define ifr_addr        ifr_ifru.ifru_addr
#define ifr_dstaddr     ifr_ifru.ifru_dstaddr
#define ifr_broadaddr   ifr_ifru.ifru_broadaddr
#define ifr_netmask     ifr_ifru.ifru_netmask
#define ifr_flags       ifr_ifru.ifru_flags
#define ifr_metric      ifr_ifru.ifru_ivalue
#define ifr_mtu         ifr_ifru.ifru_mtu
#define ifr_map         ifr_ifru.ifru_map
#define ifr_slave       ifr_ifru.ifru_slave
#define ifr_data        ifr_ifru.ifru_data
#define ifr_ifindex     ifr_ifru.ifru_ivalue
#define ifr_bandwidth   ifr_ifru.ifru_ivalue
#define ifr_qlen        ifr_ifru.ifru_ivalue
#define ifr_newname     ifr_ifru.ifru_newname

struct ifconf
{
    int ifc_len;
    union
    {
        char *ifcu_buf;
        struct ifreq *ifcu_req;
    } ifc_ifcu;
};

#define ifc_buf         ifc_ifcu.ifcu_buf

__BEGIN_DECLS

extern unsigned int if_nametoindex (const char *__ifname);
extern char *if_indextoname (unsigned int __ifindex, char *__ifname);

__END_DECLS

#endif /* _NET_IF_H */
