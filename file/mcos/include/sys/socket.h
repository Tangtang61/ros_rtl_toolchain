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
 sys/socket.h   POSIX Layer  UNIX domain sockets definitions
============================================================================*/
#ifndef __SYS_SOCKET_H__
#define __SYS_SOCKET_H__

#if !defined COMPILER_RESTRICT
#if defined __cplusplus
#define COMPILER_RESTRICT
#else /* __cplusplus */
#define COMPILER_RESTRICT restrict
#endif /* __cplusplus */
#endif /* COMPILER_RESTRICT */

#include <sys/uio.h>

#ifdef  __cplusplus
extern  "C" {
#endif

 /* Address domains */
#define AF_UNSPEC  0
#define AF_UNIX    1
#define AF_INET    2
#define AF_INET6   3

#define PF_UNSPEC  AF_UNSPEC
#define PF_UNIX    AF_UNIX
#define PF_INET    AF_INET
#define PF_INET6   AF_INET6

typedef int   socklen_t;             /* Buffer size specification */
typedef unsigned short sa_family_t;  /* Address family enumerator */

 /* Address description */
struct sockaddr
{
    sa_family_t  sa_family;          /* Address family */
    char         sa_data[26];        /* socket address */
};

 /* Address storage */
struct sockaddr_storage
{
    sa_family_t    ss_family;
    unsigned short ss_align;
    unsigned int   ss_data[6];
};

/* Message support */
struct msghdr
{
    void          *msg_name;        /* Optional address */
    socklen_t      msg_namelen;     /* Size of address */
    struct iovec  *msg_iov;         /* Scatter/gather array */
    int            msg_iovlen;      /* Members in msg_iov */
    void          *msg_control;     /* Ancillary data buffer */
    socklen_t      msg_controllen;  /* Ancillary data buffer len */
    int            msg_flags;       /* Flags on received message */
};

/* Message flags */
#define MSG_OOB         0x0001          /* Out-of-band data */
#define MSG_EOR         0x0002          /* Terminates a record (if supported by protocol) */
#define MSG_TRUNC       0x0004          /* Normal data truncated */
#define MSG_CTRUNC      0x0008          /* Control data truncated */
#define MSG_PEEK        0x0010          /* Leave received data in queue */
#define MSG_DONTROUTE   0x0020          /* Send without using routing tables */
#define MSG_WAITALL     0x0040          /* Attempt to fill the read buffer */
#define MSG_NONBLOCK    0x0100          /* Non-blocking I/O */
#define MSG_DONTWAIT    MSG_NONBLOCK    /* Non-blocking I/O */
#define MSG_NOSIGNAL    0x0200          /* Do not generate SIGPIPE */

/* Message control */
struct cmsghdr
{
    socklen_t  cmsg_len;    /* Data byte count, including cmsghdr */
    int        cmsg_level;  /* Originating protocol */
    int        cmsg_type;   /* Protocol-specific type */
 /* data follows */
};

/* cmsg_type */
#define SCM_RIGHTS      1   /* Control msg contains file descriptors */

/* Data access */
#define CMSG_DATA(_cmsg_)   ((unsigned char*)((_cmsg_) + 1))
#define CMSG_FIRST(_mhdr_)  ((struct cmsghdr*)((_mhdr_)->msg_control))
#define CMSG_NXTHDR(_mhdr_, _cmsg_)                                                                                            \
                            ((((unsigned long)((unsigned char*)(_cmsg_) + (_cmsg_)->cmsg_len + sizeof(int) - 1) & -sizeof(int)) \
                              < (unsigned long)((unsigned char*)(_mhdr_)->msg_control + (_mhdr_)->msg_controllen))              \
                             ? (struct cmsghdr*)((unsigned long)((unsigned char*)(_cmsg_)                                       \
                                                                + (_cmsg_)->cmsg_len + sizeof(int) - 1) & -sizeof(int))        \
                             : 0)

/* Linger control */
struct linger
{
    int  l_onoff;   /* Indicates whether linger option is enabled */
    int  l_linger;  /* Linger time, in seconds */
};

/* Socket types */
#define SOCK_RAW        1   /* Raw protocol interface socket */
#define SOCK_DGRAM      2   /* Datagram socket */
#define SOCK_STREAM     3   /* Byte-stream socket */
#define SOCK_SEQPACKET  4   /* Sequenced packet socket */
#define SOCK_TYPE_MASK  0xff

/* Flags for socket(), socketpair(), accept4() */
#define SOCK_NONBLOCK   0x0100  /* Non-blocking mode */
#define SOCK_CLOEXEC    0x0200  /* Close-on-exec flag */

/* Shutdown options */
#define SHUT_RD        0   /* Disables further receive operations */
#define SHUT_WR        1   /* Disables further send operations */
#define SHUT_RDWR      2   /* Disables further send and receive operations */

/* Max connection backlog */
#define SOMAXCONN     16

/* Socket level options flag (as opposed to protocol level) */
#define SOL_SOCKET     -1

/* Socket options */
#define SO_ACCEPTCONN  0       /* Socket is accepting connections */
#define SO_BROADCAST   1       /* Transmission of broadcast messages is supported */
#define SO_DEBUG       2       /* Debugging information is being recorded */
#define SO_DONTROUTE   3       /* Bypass normal routing */
#define SO_ERROR       4       /* Socket error status */
#define SO_KEEPALIVE   5       /* Connections are kept alive with periodic messages */
#define SO_LINGER      6       /* Socket lingers on close */
#define SO_OOBINLINE   7       /* Out-of-band data is transmitted in line */
#define SO_RCVBUF      8       /* Receive buffer size */
#define SO_RCVLOWAT    9       /* Receive low water mark */
#define SO_RCVTIMEO   10       /* Receive timeout */
#define SO_REUSEADDR  11       /* Reuse of local addresses is supported */
#define SO_SNDBUF     12       /* Send buffer size */
#define SO_SNDLOWAT   13       /* Send low water mark */
#define SO_SNDTIMEO   14       /* Send timeout */
#define SO_TYPE       15       /* Socket type */
#define SO_PEERCRED   16       /* Socket peer credentials */

/* Credentials (for SO_PEERCRED) */
struct ucred
{
    pid_t   pid;
    uid_t   uid;
    gid_t   gid;
};

 /* Prototypes */
int     accept(int, struct sockaddr *COMPILER_RESTRICT, socklen_t *COMPILER_RESTRICT);
int     accept4(int, struct sockaddr *COMPILER_RESTRICT, socklen_t *COMPILER_RESTRICT, int);
int     bind(int, const struct sockaddr *, socklen_t);
int     connect(int, const struct sockaddr *, socklen_t);
int     getpeername(int, struct sockaddr *COMPILER_RESTRICT, socklen_t *COMPILER_RESTRICT);
int     getsockname(int, struct sockaddr *COMPILER_RESTRICT, socklen_t *COMPILER_RESTRICT);
int     getsockopt(int, int, int, void *COMPILER_RESTRICT, socklen_t *COMPILER_RESTRICT);
int     listen(int, int);
ssize_t recv(int, void *, size_t, int);
ssize_t recvfrom(int, void *COMPILER_RESTRICT, size_t, int, struct sockaddr *COMPILER_RESTRICT, socklen_t *COMPILER_RESTRICT);
ssize_t recvmsg(int, struct msghdr *, int);
ssize_t send(int, const void *, size_t, int);
ssize_t sendmsg(int, const struct msghdr *, int);
ssize_t sendto(int, const void *, size_t, int, const struct sockaddr *, socklen_t);
int     setsockopt(int, int, int, const void *, socklen_t);
int     shutdown(int, int);
int     socket(int, int, int);
int     sockatmark(int);
int     socketpair(int, int, int, int[2]);

#ifdef  __cplusplus
}
#endif

#endif
