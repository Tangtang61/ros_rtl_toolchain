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
[ ifaddrs.c ]
****************************************************************************/
#include <ifaddrs.h>
#include <netinet/in.h>
#include <netinet/in6.h>
#include <errno.h>
#include <stdlib.h>

extern const unsigned char ___mcos_cfg_addr[4];
extern const unsigned char ___mcos_cfg_netmask[4];
extern const unsigned char ___mcos_cfg_broadaddr[4];
extern const char ___mcos_cfg_ifname[16];
extern const unsigned int  ___mcos_cfg_ifflags;

#define GETADDR(a,b,c,d) \
    ((uint32_t)(a) | \
    (uint32_t)((b) << 8) | \
    (uint32_t)((c) << 16) | \
    (uint32_t)((d) << 24))

int getifaddrs(struct ifaddrs **pifa)
{
    struct ifaddrs *pst_ifaddrs = NULL;
    char* pc_ifaname = NULL;
    struct sockaddr_in *pst_addr = NULL;
    struct sockaddr_in *pst_netmask = NULL;
    struct sockaddr_in *pst_dstaddr = NULL;

    /* init ifaddrs */
    pst_ifaddrs = (struct ifaddrs *)malloc(sizeof(struct ifaddrs));
    if(pst_ifaddrs == NULL) {
        errno = ENOMEM;
        freeifaddrs(pst_ifaddrs);
        return -1;
    }
    memset(pst_ifaddrs, 0, sizeof(struct ifaddrs));
    pst_ifaddrs->ifa_next = NULL;
    pst_ifaddrs->ifa_flags = ___mcos_cfg_ifflags;

    /* set ifa_name */
    pc_ifaname = (char *)malloc(sizeof(___mcos_cfg_ifname));
    if(pc_ifaname == NULL) {
        errno = ENOMEM;
        freeifaddrs(pst_ifaddrs);
        return -1;
    }
    strcpy(pc_ifaname, ___mcos_cfg_ifname);
    pst_ifaddrs->ifa_name = pc_ifaname;

    /* set ifa_addr */
    pst_addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr));
    if(pst_addr == NULL) {
        errno = ENOMEM;
        freeifaddrs(pst_ifaddrs);
        return -1;
    }
    memset(pst_addr, 0, sizeof(struct sockaddr));
    pst_addr->sin_family = AF_INET;
    pst_addr->sin_port = 0;
    pst_addr->sin_addr.s_addr = GETADDR(___mcos_cfg_addr[0],
                                        ___mcos_cfg_addr[1],
                                        ___mcos_cfg_addr[2],
                                        ___mcos_cfg_addr[3]);
    pst_ifaddrs->ifa_addr = (struct sockaddr *)pst_addr;

    /* set ifa_netmask */
    pst_netmask = (struct sockaddr_in *)malloc(sizeof(struct sockaddr));
    if(pst_netmask == NULL) {
        errno = ENOMEM;
        freeifaddrs(pst_ifaddrs);
        return -1;
    }
    memset(pst_netmask, 0, sizeof(struct sockaddr));
    pst_netmask->sin_family = AF_INET;
    pst_netmask->sin_port = 0;
    pst_netmask->sin_addr.s_addr = GETADDR( ___mcos_cfg_netmask[0],
                                            ___mcos_cfg_netmask[1],
                                            ___mcos_cfg_netmask[2],
                                            ___mcos_cfg_netmask[3]);
     pst_ifaddrs->ifa_netmask = (struct sockaddr *)pst_netmask;

    /* set ifa_dstaddr */
    pst_dstaddr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr));
    if(pst_dstaddr == NULL) {
        errno = ENOMEM;
        freeifaddrs(pst_ifaddrs);
        return -1;
    }
    memset(pst_dstaddr, 0, sizeof(struct sockaddr));
    pst_dstaddr->sin_family = AF_INET;
    pst_dstaddr->sin_port = 0;
    pst_dstaddr->sin_addr.s_addr = GETADDR( ___mcos_cfg_broadaddr[0],
                                            ___mcos_cfg_broadaddr[1],
                                            ___mcos_cfg_broadaddr[2],
                                            ___mcos_cfg_broadaddr[3]);
    pst_ifaddrs->ifa_dstaddr = (struct sockaddr *)pst_dstaddr;

    pst_ifaddrs->ifa_data = 0;
    *pifa = pst_ifaddrs;
    return 0;
}

void freeifaddrs(struct ifaddrs *ifa)
{
    struct ifaddrs *p_nxt, *p_cur;

    for(p_nxt = ifa; p_nxt; ) {
        free(p_nxt->ifa_name);

        if(p_nxt->ifa_addr) {
            free(p_nxt->ifa_addr);
        }

        if(p_nxt->ifa_netmask) {
            free(p_nxt->ifa_netmask);
        }

        if(p_nxt->ifa_dstaddr) { 
            free(p_nxt->ifa_dstaddr);
        }

        if(p_nxt->ifa_data){
            free(p_nxt->ifa_data);
        }
        p_cur = p_nxt;
        p_nxt = p_nxt->ifa_next;
        free(p_cur);
    }
}

const struct in6_addr in6addr_any = IN6ADDR_ANY_INIT;
const struct in6_addr in6addr_loopback = IN6ADDR_LOOPBACK_INIT;
