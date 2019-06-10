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
 sys/poll.h - Logical File System (LFS) I/O multiplexing definitions
============================================================================*/

#ifndef _SYS_POLL_H_
#define _SYS_POLL_H_

#ifdef  __cplusplus
extern  "C" {
#endif

 /* Number of pollfd structures type */
typedef int nfds_t;

struct pollfd
{
    int   fd;       /* File descriptor */
    short events;   /* Input events */
    short revents;  /* Output events */
};

 /* Input/output events */
#define POLLIN          1       /* Non-high-pri data may be read */
#define POLLRDNORM      2       /* Normal data may be read */
#define POLLRDBAND      4       /* Priority data may be read */
#define POLLPRI         8       /* High-pri data may be read */
#define POLLOUT         16      /* Normal data may be written */
#define POLLWRNORM      POLLOUT /* Normal data may be written */
#define POLLWRBAND      32      /* Priority data may be written */

 /* Output events only */
#define POLLERR         64      /* Error has occurred */
#define POLLHUP         128     /* Device disconnected */
#define POLLNVAL        256     /* Invalid fd member */

 /* Prototypes */
int   poll(struct pollfd[], nfds_t, int);

#ifdef  __cplusplus
}
#endif

#endif  /* _SYS_POLL_H_ */
