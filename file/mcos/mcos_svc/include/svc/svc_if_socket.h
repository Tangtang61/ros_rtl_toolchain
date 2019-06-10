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
[svc_if_socket.h] - SVC interface library header (POSIX Socket)
****************************************************************************/

#ifndef SVC_IF_SOCKET_H
#define SVC_IF_SOCKET_H

#include <svc/svc_if.h>

/*
 * SVC Function ID
 */
#define SVCID_SOCKET_ACCEPT         (SVCID_SOCKET | 0x00000000) /* accept()      */
#define SVCID_SOCKET_ACCEPT4        (SVCID_SOCKET | 0x00000001) /* accept4()     */
#define SVCID_SOCKET_BIND           (SVCID_SOCKET | 0x00000002) /* bind()        */
#define SVCID_SOCKET_LISTEN         (SVCID_SOCKET | 0x00000003) /* listen()      */
#define SVCID_SOCKET_CONNECT        (SVCID_SOCKET | 0x00000004) /* connect()     */
#define SVCID_SOCKET_SHUTDOWN       (SVCID_SOCKET | 0x00000005) /* shutdown()    */
#define SVCID_SOCKET_SOCKET         (SVCID_SOCKET | 0x00000006) /* socket()      */
#define SVCID_SOCKET_SOCKETPAIR     (SVCID_SOCKET | 0x00000007) /* socketpair()  */
#define SVCID_SOCKET_RECV           (SVCID_SOCKET | 0x00000008) /* recv()        */
#define SVCID_SOCKET_RECVFROM       (SVCID_SOCKET | 0x00000009) /* recvfrom()    */
#define SVCID_SOCKET_RECVMSG        (SVCID_SOCKET | 0x0000000a) /* recvmsg()     */
#define SVCID_SOCKET_SEND           (SVCID_SOCKET | 0x0000000b) /* send()        */
#define SVCID_SOCKET_SENDMSG        (SVCID_SOCKET | 0x0000000c) /* sendmsg()     */
#define SVCID_SOCKET_SENDTO         (SVCID_SOCKET | 0x0000000d) /* sendto()      */
#define SVCID_SOCKET_GETSOCKNAME    (SVCID_SOCKET | 0x0000000e) /* getsockname() */
#define SVCID_SOCKET_GETPEERNAME    (SVCID_SOCKET | 0x0000000f) /* getpeername() */
#define SVCID_SOCKET_GETSOCKOPT     (SVCID_SOCKET | 0x00000010) /* getsockopt()  */
#define SVCID_SOCKET_SETSOCKOPT     (SVCID_SOCKET | 0x00000011) /* setsockopt()  */
#define SVCID_SOCKET_SOCKATMARK     (SVCID_SOCKET | 0x00000012) /* sockatmark()  */

#ifndef _in_asm_source_

/*
 * SVC Parameter Packet
 */
#include <sys/socket.h>

/* accept() */
typedef struct {
    int             id;
    int             socket;
    struct sockaddr * restrict address;
    socklen_t       * restrict address_len;
} svc_packet_socket_accept_t;

/* accept4() */
typedef struct {
    int             id;
    int             socket;
    struct sockaddr * restrict address;
    socklen_t       * restrict address_len;
    int             flags;
} svc_packet_socket_accept4_t;

/* bind() */
typedef struct {
    int                     id;
    int                     socket;
    const struct sockaddr   *address;
    socklen_t               address_len;
} svc_packet_socket_bind_t;

/* listen() */
typedef struct {
    int             id;
    int             socket;
    int             backlog;
} svc_packet_socket_listen_t;

/* connect() */
typedef struct {
    int                     id;
    int                     socket;
    const struct sockaddr   *address;
    socklen_t               address_len;
} svc_packet_socket_connect_t;

/* shutdown() */
typedef struct {
    int             id;
    int             socket;
    int             how;
} svc_packet_socket_shutdown_t;

/* socket() */
typedef struct {
    int             id;
    int             domain;
    int             type;
    int             protocol;
} svc_packet_socket_socket_t;

/* socketpair() */
typedef struct {
    int             id;
    int             domain;
    int             type;
    int             protocol;
    int             *socket_vector;
} svc_packet_socket_socketpair_t;

/* recv() */
typedef struct {
    int             id;
    int             socket;
    void            *buffer;
    size_t          length;
    int             flags;
    ssize_t         *received_len;
} svc_packet_socket_recv_t;

/* recvfrom() */
typedef struct {
    int             id;
    int             socket;
    void            * restrict buffer;
    size_t          length;
    int             flags;
    struct sockaddr * restrict address;
    socklen_t       * restrict address_len;
    ssize_t         *received_len;
} svc_packet_socket_recvfrom_t;

/* recvmsg() */
typedef struct {
    int             id;
    int             socket;
    struct msghdr   *message;
    int             flags;
    ssize_t         *received_len;
} svc_packet_socket_recvmsg_t;

/* send() */
typedef struct {
    int             id;
    int             socket;
    const void      *buffer;
    size_t          length;
    int             flags;
    ssize_t         *sent_len;
} svc_packet_socket_send_t;

/* sendmsg() */
typedef struct {
    int                 id;
    int                 socket;
    const struct msghdr *message;
    int                 flags;
    ssize_t             *sent_len;
} svc_packet_socket_sendmsg_t;

/* sendto() */
typedef struct {
    int                     id;
    int                     socket;
    const void              *message;
    size_t                  length;
    int                     flags;
    const struct sockaddr   *dest_addr;
    socklen_t               dest_len;
    ssize_t                 *sent_len;
} svc_packet_socket_sendto_t;

/* getsockname() */
typedef struct {
    int             id;
    int             socket;
    struct sockaddr * restrict address;
    socklen_t       * restrict address_len;
} svc_packet_socket_getsockname_t;

/* getpeername() */
typedef struct {
    int             id;
    int             socket;
    struct sockaddr * restrict address;
    socklen_t       * restrict address_len;
} svc_packet_socket_getpeername_t;

/* getsockopt() */
typedef struct {
    int             id;
    int             socket;
    int             level;
    int             option_name;
    void            * restrict option_value;
    socklen_t       * restrict option_len;
} svc_packet_socket_getsockopt_t;

/* setsockopt() */
typedef struct {
    int             id;
    int             socket;
    int             level;
    int             option_name;
    const void      *option_value;
    socklen_t       option_len;
} svc_packet_socket_setsockopt_t;

/* sockatmark() */
typedef struct {
    int             id;
    int             socket;
} svc_packet_socket_sockatmark_t;


/* List of POSIX Socket APIs */
typedef struct {
    int                 id;
} svc_packet_socket_t;

#endif /* _in_asm_source_ */

#endif  /* #ifndef SVC_IF_SOCKET_H */
