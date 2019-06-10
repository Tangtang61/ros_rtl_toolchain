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
[svc_if_pipe.h] - SVC interface library header (POSIX Pipe)
****************************************************************************/

#ifndef SVC_IF_PIPE_H
#define SVC_IF_PIPE_H

#include <svc/svc_if.h>

/*
 * SVC Function ID
 */
#define SVCID_PIPE_PIPE         (SVCID_PIPE | 0x00000000)
#define SVCID_PIPE_PIPE2        (SVCID_PIPE | 0x00000001)
#define SVCID_PIPE_MKFIFO       (SVCID_PIPE | 0x00000002)

#ifndef _in_asm_source_

/*
 * SVC Parameter Packet
 */
#include <unistd.h>
#include <sys/stat.h>

/* pipe() */
typedef struct {
    int         id;
    int         *fildes;
} svc_packet_pipe_pipe_t;

/* pipe2() */
typedef struct {
    int         id;
    int         *fildes;
    int         flags;
} svc_packet_pipe_pipe2_t;

/* mkfifo() */
typedef struct {
    int             id;
    const char      *path;
    mode_t          mode;
} svc_packet_pipe_mkfifo_t;

/* List of POSIX Pipe APIs */
typedef union {
    int                         id;
    svc_packet_pipe_pipe_t      param_pipe;
    svc_packet_pipe_pipe2_t     param_pipe2;
    svc_packet_pipe_mkfifo_t    param_mkfifo;
} svc_packet_pipe_t;

#endif /* _in_asm_source_ */

#endif  /* #ifndef SVC_IF_PIPE_H */
