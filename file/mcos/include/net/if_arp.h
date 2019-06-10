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
 net/if_arp.h - Address Resolution Protocol interface header
****************************************************************************/

#ifndef _NET_IF_ARP_H
#define _NET_IF_ARP_H

#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/socket.h>

__BEGIN_DECLS

#define MAX_ADDR_LEN    7

#define ARPOP_REQUEST   1
#define ARPOP_REPLY     2
#define ARPOP_RREQUEST  3
#define ARPOP_RREPLY    4
#define ARPOP_InREQUEST 8
#define ARPOP_InREPLY   9
#define ARPOP_NAK       10

struct arphdr {
    unsigned short ar_hrd;
    unsigned short ar_pro;
    unsigned char  ar_hln;
    unsigned char  ar_pln;
    unsigned short ar_op;
};

#define ARPHRD_NETROM      0
#define ARPHRD_ETHER       1
#define ARPHRD_EETHER      2
#define ARPHRD_AX25        3
#define ARPHRD_PRONET      4
#define ARPHRD_CHAOS       5
#define ARPHRD_IEEE802     6
#define ARPHRD_ARCNET      7
#define ARPHRD_APPLETLK    8
#define ARPHRD_DLCI       15
#define ARPHRD_ATM        19
#define ARPHRD_METRICOM   23
#define ARPHRD_IEEE1394   24
#define ARPHRD_EUI64      27
#define ARPHRD_INFINIBAND 32

#define ARPHRD_VOID       0xFFFF
#define ARPHRD_NONE       0xFFFE

struct arpreq {
    struct sockaddr arp_pa;
    struct sockaddr arp_ha;
    int arp_flags;
    struct sockaddr arp_netmask;
    char arp_dev[16];
};

__END_DECLS

#endif /* _NET_IF_ARP_H */
