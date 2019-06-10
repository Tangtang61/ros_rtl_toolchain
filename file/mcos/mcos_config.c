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
[ mcos_config.c ]
****************************************************************************/

const int ___mcos_cfg_hclid = 1;
const int ___mcos_cfg_cp_hcl_max = 4;
const int ___mcos_cfg_cc_count = 4;

/* IP address */
const unsigned char ___mcos_cfg_addr[4]      = {192, 168,   1, 100}; /* ex. "192.168.1.1"    > {192, 168,  1,   1} */
/* Subnet mask */
const unsigned char ___mcos_cfg_netmask[4]   = {255, 255, 255,   0}; /* ex. "255.255.255.0"  > {255, 255, 255,  0} */
/* Broadcast address */
const unsigned char ___mcos_cfg_broadaddr[4] = {192, 168,   1, 255}; /* ex. "192.168.1.255"  > {192, 168,  1, 255} */
/* interface name */
const char ___mcos_cfg_ifname[16]            = "et0";
/* interface flags */
const unsigned int ___mcos_cfg_ifflags       = (0x01 | 0x02 | 0x40); /* IFF_UP | IFF_BROADCAST | IFF_RUNNING */

