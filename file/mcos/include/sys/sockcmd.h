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
 sys/sockcmd.h - Domain switch Table
============================================================================*/

#ifndef _SYS_SOCKCMD_H_
#define _SYS_SOCKCMD_H_

#include <sys/socket.h>
#include <sys/lfs.h>
#include <sys/ioctl.h>

#ifdef  __cplusplus
extern  "C" {
#endif

/* shutdown state flag */

#define PAR_SHUT_RD     0x00000001
#define PAR_SHUT_WR     0x00000002

/*
 * netstat() command state
 * AF_UNIX
 */

#define OPENED          0x00000004
#define LISTENING       0x00000008
#define CONNECTING      0x00000010
#define CONNECTED       0x00000020

/* AF_INET status */
#define ESTABLISHED     0x00000040
#define SYN_SENT        0x00000080
#define SYN_RECV        0x00000100
#define FIN_WAIT1       0x00000200
#define FIN_WAIT2       0x00000400
#define TIME_WAIT       0x00000800
#define CLOSED          0x00001000
#define CLOSE_WAIT      0x00002000
#define LAST_ACK        0x00004000
#define LISTEN          0x00008000
#define CLOSING         0x00010000

/*
 * Socket command codes
 */
enum sock_cmd_code
{
    SOCK_CMD_SOCKET,
    SOCK_CMD_SOCKETPAIR,
    SOCK_CMD_SOCKATMARK,
    SOCK_CMD_GETSOCKNAME,
    SOCK_CMD_GETPEERNAME,
    SOCK_CMD_BIND,
    SOCK_CMD_LISTEN,
    SOCK_CMD_CONNECT,
    SOCK_CMD_ACCEPT,
    SOCK_CMD_SHUTDOWN,
    SOCK_CMD_RECV,
    SOCK_CMD_SEND,
    SOCK_CMD_RECVFROM,
    SOCK_CMD_SENDTO,
    SOCK_CMD_RECVMSG,
    SOCK_CMD_SENDMSG,
    SOCK_CMD_GETSOCKOPT,
    SOCK_CMD_SETSOCKOPT,
    SOCK_CMD_CLOSE,
    SOCK_CMD_SELECT,
    SOCK_CMD_IOCTL,
    SOCK_CMD_STATE,
};

/*
 * Type Definitions
 */
typedef union sock_cmd  sock_cmd_t;

struct  sock_cmd_socket
{
    int                     code;       /* Command code                 */
    int                     domain;     /* Socket domain                */
    int                     type;       /* Socket type                  */
    int                     proto;      /* Protocol                     */
    unsigned int*           sid;        /* Socket ID                    */
};

struct  sock_cmd_socketpair
{
    int                     code;       /* Command code                 */
    int                     domain;     /* Socket domain                */
    int                     type;       /* Socket type                  */
    int                     proto;      /* Protocol                     */
    unsigned int*           sid;        /* Socket ID                    */
};

struct  sock_cmd_sockatmark
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    ssize_t*                res;        /* Return an OOB data mark      */
};

struct  sock_cmd_getsockname
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    struct sockaddr*        addr;       /* Socket address strucrure     */
    socklen_t*              aptr;       /* Pointer to address_len       */
};

struct  sock_cmd_getpeername
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    struct sockaddr*        addr;       /* Socket address strucrure     */
    socklen_t*              aptr;       /* Pointer to address_len       */
};

struct  sock_cmd_bind
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    const struct sockaddr*  addr;       /* Socket address strucrure     */
    socklen_t               alen;       /* Length of address            */
};

struct  sock_cmd_listen
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    int                     blog;       /* Length of the listen queue   */
};

struct  sock_cmd_connect
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    const struct sockaddr*  addr;       /* Socket address strucrure     */
    socklen_t               alen;       /* Length of address            */
    int                     fflags;     /* File flags                   */
};

struct  sock_cmd_accept
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    struct sockaddr*        addr;       /* Socket address strucrure     */
    socklen_t*              aptr;       /* Pointer to address_len       */
    int                     fflags;     /* File flags                   */
    unsigned int*           nsid;       /* New socket ID                */
};

struct  sock_cmd_shutdown
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    int                     how;        /* Type of shutdown             */
};

struct  sock_cmd_recv
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    void*                   buf;        /* messsage buffer              */
    size_t                  len;        /* Length of message buffer     */
    int                     flags;      /* Type of message reception    */
    int                     fflags;     /* File flags                   */
    ssize_t*                res;        /* Length of received message   */
};

struct  sock_cmd_send
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    const void*             buf;        /* messsage buffer              */
    size_t                  len;        /* Length of message buffer     */
    int                     flags;      /* Type of message transmission */
    int                     fflags;     /* File flags                   */
    ssize_t*                res;        /* Length of send message       */
};

struct  sock_cmd_recvfrom
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    void*                   buf;        /* messsage buffer              */
    size_t                  len;        /* Length of message buffer     */
    int                     flags;      /* Type of message reception    */
    struct sockaddr*        addr;       /* Socket address strucrure     */
    socklen_t*              aptr;       /* Pointer to address_len       */
    int                     fflags;     /* File flags                   */
    ssize_t*                res;        /* Length of received message   */
};

struct  sock_cmd_sendto
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    const void*             buf;        /* messsage buffer              */
    size_t                  len;        /* Length of message buffer     */
    int                     flags;      /* Type of message transmission */
    const struct sockaddr*  addr;       /* Socket address strucrure     */
    socklen_t               alen;       /* Length of address            */
    int                     fflags;     /* File flags                   */
    ssize_t*                res;        /* Length of send message       */
};

struct  sock_cmd_recvmsg
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    struct msghdr*          hdr;        /* Pointet to mssage handler    */
    int                     flags;      /* Type of message reception    */
    int                     fflags;     /* File flags                   */
    ssize_t*                res;        /* Length of received message   */
};

struct  sock_cmd_sendmsg
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    const struct msghdr*    hdr;        /* Pointet to mssage handler    */
    int                     flags;      /* Type of message reception    */
    int                     fflags;     /* File flags                   */
    ssize_t*                res;        /* Length of send message       */
};

struct  sock_cmd_getsockopt
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    int                     level;      /* Socket level                 */
    int                     optname;    /* Socket option                */
    void*                   optval;     /* Value for the socket option  */
    socklen_t*              optlen;     /* Size of option value         */
};

struct  sock_cmd_setsockopt
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    int                     level;      /* Socket level                 */
    int                     optname;    /* Socket option                */
    const void*             optval;     /* Value for the socket option  */
    socklen_t               optlen;     /* Size of option value         */
};

struct  sock_cmd_close
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    int                     fflags;     /* File flags                   */
};

struct  sock_cmd_select
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    struct selreq*          selreq;     /* Select request block         */
    int                     fflags;     /* File flags                   */
};

struct  sock_cmd_ioctl
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    int                     dcmd;       /* Command to device            */
    void*                   data;       /* Pointer to input/output data */
    size_t                  size;       /* Data size                    */
    int*                    info;       /* Pointer to return device info*/
    int                     fflags;     /* File flags                   */
};

struct  sock_cmd_state
{
    int                     code;       /* Command code                 */
    unsigned int            sid;        /* Socket ID                    */
    int*                    state;      /* Socket State                 */
};

/*
 * Request union
 */
union   sock_cmd
{
    int     code;
    struct  sock_cmd_socket          r_socket;
    struct  sock_cmd_socketpair      r_socketpair;
    struct  sock_cmd_sockatmark      r_sockatmark;
    struct  sock_cmd_getsockname     r_getsockname;
    struct  sock_cmd_getpeername     r_getpeername;
    struct  sock_cmd_bind            r_bind;
    struct  sock_cmd_listen          r_listen;
    struct  sock_cmd_connect         r_connect;
    struct  sock_cmd_accept          r_accept;
    struct  sock_cmd_shutdown        r_shutdown;
    struct  sock_cmd_recv            r_recv;
    struct  sock_cmd_send            r_send;
    struct  sock_cmd_recvfrom        r_recvfrom;
    struct  sock_cmd_sendto          r_sendto;
    struct  sock_cmd_recvmsg         r_recvmsg;
    struct  sock_cmd_sendmsg         r_sendmsg;
    struct  sock_cmd_getsockopt      r_getsockopt;
    struct  sock_cmd_setsockopt      r_setsockopt;
    struct  sock_cmd_close           r_close;
    struct  sock_cmd_select          r_select;
    struct  sock_cmd_ioctl           r_ioctl;
    struct  sock_cmd_state           r_state;
};

/* domain attach or detach prototypes */
int     socket_domain_attach(int, int (*sock_service)(sock_cmd_t*));
int     socket_domain_detach(int);

#ifdef  __cplusplus
}
#endif

#endif  /* _SYS_SOCKCMD_H_ */
