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
[pipe_svc.c] - SVC interface library (POSIX Pipe)
****************************************************************************/

#include <svc/svc_if.h>
#include <svc/svc_if_pipe.h>

/* pipe() API */
int pipe(int fildes[2])
{
    svc_packet_pipe_pipe_t  p;

    p.id        = SVCID_PIPE_PIPE;
    p.fildes    = fildes;
    return (int)call_svc((void*)&p);
}

/* pipe2() API */
int pipe2(int fildes[2], int flags)
{
    svc_packet_pipe_pipe2_t p;

    p.id        = SVCID_PIPE_PIPE2;
    p.fildes    = fildes;
    p.flags     = flags;
    return (int)call_svc((void*)&p);
}

/* mkfifo() API */
int mkfifo(const char * path, mode_t mode)
{
    svc_packet_pipe_mkfifo_t    p;

    p.id        = SVCID_PIPE_MKFIFO;
    p.path      = path;
    p.mode      = mode;
    return (int)call_svc((void*)&p);
}
