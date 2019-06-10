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
[ mcos_netdb.h ] - Configurations for Network Database Operation
****************************************************************************/
#ifndef _MCOS_NETDB_H
#define _MCOS_NETDB_H

#define _PATH_SERVICES  "/ramfs/etc/services"    /* Path of the services file */
#define _PATH_IRS_CONF  "/ramfs/etc/irs.conf"    /* Path of the irs.conf file */
#define _PATH_HOSTS     "/ramfs/etc/hosts"       /* Path of the hosts file */
#define _PATH_RESCONF   "/ramfs/etc/resolv.conf" /* Path of the resolv.conf file */
#if 0
#define _PATH_SERVICES  "/prfile2sd/etc/services"
#define _PATH_IRS_CONF  "/prfile2sd/etc/irs.conf"
#define _PATH_HOSTS     "/prfile2sd/etc/hosts"
#define _PATH_RESCONF   "/prfile2sd/etc/resolv.conf"
#endif

/* Default lockup order for hosts */
#define _DEFAULT_RULE_HOSTS     0x00000221

/* Default lockup order for services */
#define _DEFAULT_RULE_SERVICES  0x00000001

/* Maximum number of the available
 * name servers may be listed in resolv.conf */
#define MAXNS   3

#endif /* _MCOS_NETDB_H */
