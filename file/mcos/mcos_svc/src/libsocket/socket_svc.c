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
[socket_svc.c] - SVC interface library (POSIX Socket)
****************************************************************************/

#include <errno.h>
#include <stdio.h>
#include <netinet/in.h>
#include <mcos/mcos.h>
#include <svc/svc_if.h>
#include <svc/svc_if_socket.h>

#include <time.h>
#define MILLITONANO (1000000)

int accept(int socket, struct sockaddr *restrict address,
           socklen_t *restrict address_len)
{
    svc_packet_socket_accept_t p;

    p.id = SVCID_SOCKET_ACCEPT;
    p.socket = socket;
    p.address = address;
    p.address_len = address_len;
    return (int)call_svc((void*)&p);
}

int accept4(int socket, struct sockaddr *restrict address,
           socklen_t *restrict address_len, int flags)
{
    svc_packet_socket_accept4_t p;

    p.id = SVCID_SOCKET_ACCEPT4;
    p.socket = socket;
    p.address = address;
    p.address_len = address_len;
    p.flags = flags;
    return (int)call_svc((void*)&p);
}

int bind(int socket, const struct sockaddr *address, socklen_t address_len)
{
    svc_packet_socket_bind_t p;

    p.id = SVCID_SOCKET_BIND;
    p.socket = socket;
    p.address = address;
    p.address_len = address_len;
    return (int)call_svc((void*)&p);
}

int listen(int socket, int backlog)
{
    svc_packet_socket_listen_t p;

    p.id = SVCID_SOCKET_LISTEN;
    p.socket = socket;
    p.backlog = backlog;
    return (int)call_svc((void*)&p);
}

int connect(int socket, const struct sockaddr *address, socklen_t address_len)
{
    int iret = 0;
    svc_packet_socket_connect_t p;

    p.id = SVCID_SOCKET_CONNECT;
    p.socket = socket;
    p.address = address;
    p.address_len = address_len;

    struct timespec ts_req = {0, 20 * MILLITONANO};
    nanosleep(&ts_req, NULL);
    iret = (int)call_svc((void*)&p);
    nanosleep(&ts_req, NULL);

    return iret;
}

int shutdown(int socket, int how)
{
    svc_packet_socket_shutdown_t p;

    p.id = SVCID_SOCKET_SHUTDOWN;
    p.socket = socket;
    p.how = how;
    return (int)call_svc((void*)&p);
}

int socket(int domain, int type, int protocol)
{
    svc_packet_socket_socket_t p;

    p.id = SVCID_SOCKET_SOCKET;
    p.domain = domain;
    p.type = type;
    p.protocol = protocol;
    return (int)call_svc((void*)&p);
}

int socketpair(int domain, int type, int protocol, int socket_vector[2])
{
    svc_packet_socket_socketpair_t p;

    p.id = SVCID_SOCKET_SOCKETPAIR;
    p.domain = domain;
    p.type = type;
    p.protocol = protocol;
    p.socket_vector = socket_vector;
    return (int)call_svc((void*)&p);
}

ssize_t recv(int socket, void *buffer, size_t length, int flags)
{
    svc_packet_socket_recv_t p;
    ssize_t received_len;

    p.id = SVCID_SOCKET_RECV;
    p.socket = socket;
    p.buffer = buffer;
    p.length = length;
    p.flags = flags;
    p.received_len = &received_len;
    (void)call_svc((void*)&p);
    return *p.received_len;
}

ssize_t recvfrom(int socket, void *restrict buffer, size_t length, int flags,
                 struct sockaddr *restrict address, socklen_t *restrict address_len)
{
    svc_packet_socket_recvfrom_t p;
    ssize_t received_len;

    p.id = SVCID_SOCKET_RECVFROM;
    p.socket = socket;
    p.buffer = buffer;
    p.length = length;
    p.flags = flags;
    p.address = address;
    p.address_len = address_len;
    p.received_len = &received_len;
    (void)call_svc((void*)&p);
    return *p.received_len;
}

ssize_t recvmsg(int sfd, struct msghdr *pmhd, int flags)
{
    int     stype;
    int     stype_sz;
    int     stat;
    ssize_t rx_tt;
    int     i;

    /*! Check parameters */
    if ((pmhd == NULL) ||
        (pmhd-> msg_iov == NULL) ||
        (pmhd-> msg_iovlen == 0) ||
        (pmhd-> msg_iovlen >= IOV_MAX)) {
        errno = EINVAL;
        return -1;
    }

    stype_sz = sizeof(stype);
    if (getsockopt(sfd, SOL_SOCKET, SO_TYPE, &stype, &stype_sz) != 0) {
        /*! errno is set by getsockopt() */
        return -1;
    }

    rx_tt = 0;
    {
        struct sockaddr *psadr;
        socklen_t       *psadlen;

        ssize_t         rcvd;
        void            *pbuf;
        size_t          len;

        if (stype == SOCK_STREAM) {
            /*! Connection based */
            psadr = NULL;
            psadlen = NULL;
        } else {
            /*! Non-connected data-gram */
            psadr = (struct sockaddr *)pmhd-> msg_name;
            psadlen = &(pmhd-> msg_namelen);
        }

        /*! Message receiving... */
        for (i = 0; i < pmhd-> msg_iovlen; i++) {
            pbuf = pmhd-> msg_iov[i].iov_base;
            len = pmhd-> msg_iov[i].iov_len;

            if ((pbuf == NULL) || (len <= 0)) {
                /*! Skip buffer-data */
                continue;
            }

            rcvd = recvfrom(sfd, pbuf, len, flags, psadr, psadlen);
            if (rcvd < 0) {
                /*! errno is set by recv() */
                return -1;
            }

            rx_tt += rcvd;
            if (rcvd < len) {
                break;
            }
        }

        /*! System condition to quit loop
         *  All iov's are fulled (i == pmhd-> msg_iovlen)
         *  The length of received message is less than
         *  buffer-size of each
         */
    }

    return rx_tt;
}

ssize_t send(int socket, const void *buffer, size_t length, int flags)
{
    svc_packet_socket_send_t p;
    ssize_t sent_len;

    p.id = SVCID_SOCKET_SEND;
    p.socket = socket;
    p.buffer = buffer;
    p.length = length;
    p.flags = flags;
    p.sent_len = &sent_len;
    (void)call_svc((void*)&p);
    return *p.sent_len;
}

ssize_t sendmsg(int socket, const struct msghdr *message, int flags)
{
	int iType = 0;
	int iSize = sizeof(iType);
	ssize_t total_sentbyte = 0;
	struct sockaddr_in sin;
    struct sockaddr_in* psin;
    int i;

	if (getsockopt(socket, SOL_SOCKET, SO_TYPE, &iType, &iSize) < 0)
	{
        printf("sendmsg() error. getsockopt() < 0.\r\n");
		return -1;
	}

	if ((message == 0) || (message->msg_iov == 0) || (message->msg_iovlen <= 0) || (message->msg_iovlen > 0xFFFF))
	{
        printf("sendmsg() error. parameter error!.\r\n");
		return -1;
	}

    psin = (struct sockaddr_in *)message->msg_name;
    /* flags OFF. for PrConnectPro. */
	flags = 0x00;

	if (iType == SOCK_STREAM)
	{
		for (i = 0; i < message->msg_iovlen; i++)
		{
			total_sentbyte += send(socket, message->msg_iov[i].iov_base, message->msg_iov[i].iov_len, flags);
		}
	}
	else 
	{
		for (i = 0; i < message->msg_iovlen; i++)
		{
            ssize_t sentbyte = 0;
            sentbyte = sendto(socket, message->msg_iov[i].iov_base, message->msg_iov[i].iov_len, flags, 
								message->msg_name, sizeof(struct sockaddr_in));
            if (sentbyte < 0)
            {
                sentbyte = message->msg_iov[i].iov_len;
			}
			total_sentbyte += sentbyte;
		}
	}
	return total_sentbyte;
}

ssize_t sendto(int socket, const void *message, size_t length, int flags,
               const struct sockaddr *dest_addr, socklen_t dest_len)
{
    svc_packet_socket_sendto_t p;
    ssize_t sent_len;

    p.id = SVCID_SOCKET_SENDTO;
    p.socket = socket;
    p.message = message;
    p.length = length;
    p.flags = flags;
    p.dest_addr = dest_addr;
    p.dest_len = dest_len;
    p.sent_len = &sent_len;
    (void)call_svc((void*)&p);
    return *p.sent_len;
}

int getsockname(int socket, struct sockaddr *restrict address,
        socklen_t *restrict address_len)
{
    svc_packet_socket_getsockname_t p;

    p.id = SVCID_SOCKET_GETSOCKNAME;
    p.socket = socket;
    p.address = address;
    p.address_len = address_len;
    return (int)call_svc((void*)&p);
}

int getpeername(int socket, struct sockaddr *restrict address,
        socklen_t *restrict address_len)
{
    svc_packet_socket_getpeername_t p;

    p.id = SVCID_SOCKET_GETPEERNAME;
    p.socket = socket;
    p.address = address;
    p.address_len = address_len;
    return (int)call_svc((void*)&p);
}

int getsockopt(int socket, int level, int option_name,
        void *restrict option_value, socklen_t *restrict option_len)
{
    svc_packet_socket_getsockopt_t p;

    p.id = SVCID_SOCKET_GETSOCKOPT;
    p.socket = socket;
    p.level = level;
    p.option_name = option_name;
    p.option_value = option_value;
    p.option_len = option_len;
    return (int)call_svc((void*)&p);
}

int setsockopt(int socket, int level, int option_name,
        const void *option_value, socklen_t option_len)
{
    svc_packet_socket_setsockopt_t p;

    p.id = SVCID_SOCKET_SETSOCKOPT;
    p.socket = socket;
    p.level = level;
    p.option_name = option_name;
    p.option_value = option_value;
    p.option_len = option_len;
    return (int)call_svc((void*)&p);
}

int sockatmark(int socket)
{
    svc_packet_socket_sockatmark_t p;

    p.id = SVCID_SOCKET_SOCKATMARK;
    p.socket = socket;
    return (int)call_svc((void*)&p);
}

