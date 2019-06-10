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

/*============================================================================
 port_before.h  Configration for netdb API
============================================================================*/
#ifndef _PORT_BEFORE_H_
#define _PORT_BEFORE_H_

/* WANT_IRS_GR
 *  - #define   Group database functions are supported
 *  - #undef    Group database functions are not supported 
 */
#undef WANT_IRS_GR

/* WANT_IRS_PW
 *  - #define   User database functions are supported
 *  - #undef    User database funcionts are not supported
 */
#undef WANT_IRS_PW

/* WANT_IRS_PR
 *  - #define   Network protocol database functions are supported
 *  - #undef    Network protocol database functions are not supported
 */
#undef WANT_IRS_PR

/* WANT_IRS_NW
 *  - #define   Network database functions are supported
 *  - #undef    Network database functions are not supported
 */
#undef WANT_IRS_NW

/* WANT_IRS_NG
 *  - #define   Network group functions are supported
 *  - #undef    Network group functions are not supported
 */
#undef WANT_IRS_NG

/* WANT_IRS_NIS
 *  - #define   Network Infomation Server function is supported
 *  - #undef    Network Infomation Server function is not supported
 */
#undef WANT_IRS_NIS

/* WANT_IRS_IRP
 *  - #define   IRP function is supported
 *  - #undef    IRP function is not supported
 */
#undef WANT_IRS_IRP

/* USE_SYSLOG
 *  - #definie  syslog function is supported
 *  - #undef    syslog function is not supported
 */
#undef USE_SYSLOG

/* IRS_LCL_SV_DB
 *  - #define   Local services database function is supported
 *  - #undef    Local services database function is not supported
 */
#undef IRS_LCL_SV_DB

/* DEBUG
 *  - #define   Debuging function is supported. Debuging information is output.
 *  - #undef    Debuging function is not supported.
 */
#undef DEBUG

/* SCOPE_DELIMITER
 *  - #define   Delimiter for IPv6 scope ID
 *  - #undef    Delimiter for IPv6 scope ID is not supported
 */
#undef SCOPE_DELIMITER

/* HAVE_SIN6_SCOPE_ID
 *  - #define   struct sockaddr_in6 has element sin6_scope_id
 *  - #undef    sin6_scope_id is not available
 */
#define HAVE_SIN6_SCOPE_ID

/* HAVE_SA_LEN
 *  - #define   struct sockaddr has element sa_len
 *  - #undef    sa_len is not available
 */
#undef HAVE_SA_LEN

/* USE_IFNAMELINKID
 *  - #define   Interface name function if_nametoindex is used.
 *  - #undef    Interface name function if_nametoindex is not used.
 */
#undef USE_IFNAMELINKID

/* __bsdi__
*/
#undef __bsdi__

/* GETHOSTNAME_SUPPORT
 *  - #define   gethostname function is availabe
 *  - #undef    gethostname function is unavailabe 
 */
#undef GETHOSTNAME_SUPPORT

/* DO_PTHREADS 
 *  Network data is allocated for every task
 */
#define DO_PTHREADS

/* USE_POLL 
 *  How to synchronize socket multiplexing
 *  - #definie  poll function is used
 *  - #undef    pselect function is used
 */
#define USE_POLL

/* HAS_INET6_STRUCTS
 *  - #define   IPv6 struct sockaddr_in6 is available
 *  - #undef    IPv6 struct sockaddr_in6 is not available
 */
#define HAS_INET6_STRUCTS

/* USELOOPBACK
 *  - #define   INADDR_LOOPBACK_INIT is used instead of INADDR_ANY
 *  - #undef    INADDR_ANY is used instead of INADDR_LOOPBACK_INIT
 */
#define USELOOPBACK

/* CANNOT_CONNECT_DGRAM
 *  - #define   sendto is used when connects to the DNS
 *  - #undef    send is used when connects to the DNS
 */
#define CANNOT_CONNECT_DGRAM

/* _REENTRANT
 *  - #define   functions are reentrant 
 *  - #undef    functions are not sure to be reentrant
 */
#define _REENTRANT              1

/* assertions.h file */
#define CHECK_ALL               1
#define __COVERITY__            1

/* ISC_ALIGN64
 *  - #define   64 bits align
 *  - #undef    32 bit align
 */
#define ISC_ALIGN32
#undef  ISC_ALIGN64

#define DE_CONST(konst, var) \
        do { \
                union { const void *k; void *v; } _u; \
                _u.k = konst; \
                var = _u.v; \
        } while (0)
        
#define UNUSED(x) (x) = (x)

#define ISC_FORMAT_PRINTF(fmt, args) \
        __attribute__((__format__(__printf__, fmt, args)))

#endif  /* _PORT_BEFORE_H_  */
