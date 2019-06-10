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
[aio_svc.c] - SVC interface library (POSIX Async I/O)
****************************************************************************/

#include <svc/svc_if.h>
#include <svc/svc_if_aio.h>
#include <inttypes.h>

int aio_worker(void *arg);
void* aio_worker_thread_entry(void* arg)
{
    int sta;

    sta = aio_worker(arg);
    (void)pthread_exit((void*)(intptr_t)sta);
    return (void*)(intptr_t)sta;
}

int aio_read(struct aiocb *acb)
{
    svc_packet_aio_read_t p;

    p.id  = SVCID_AIO_READ;
    p.acb = acb;
    return (int)call_svc((void*)&p);
}

int aio_write(struct aiocb *acb)
{
    svc_packet_aio_write_t p;

    p.id  = SVCID_AIO_WRITE;
    p.acb = acb;
    return (int)call_svc((void*)&p);
}

int aio_cancel(int fildes, struct aiocb *acb)
{
    svc_packet_aio_cancel_t p;

    p.id     = SVCID_AIO_CANCEL;
    p.fildes = fildes;
    p.acb    = acb;
    return (int)call_svc((void*)&p);
}

int aio_suspend(const struct aiocb *const list[], int nent,
        const struct timespec *timeout)
{
    svc_packet_aio_suspend_t p;

    p.id      = SVCID_AIO_SUSPEND;
    p.list    = list;
    p.nent    = nent;
    p.timeout = timeout;
    return (int)call_svc((void*)&p);
}

ssize_t aio_return(struct aiocb *acb)
{
    svc_packet_aio_return_t p;
    ssize_t return_len;

    p.id         = SVCID_AIO_RETURN;
    p.acb        = acb;
    p.return_len = &return_len;
    (void)call_svc((void*)&p);
    return *p.return_len;
}

int aio_error(const struct aiocb *acb)
{
    svc_packet_aio_error_t p;

    p.id  = SVCID_AIO_ERROR;
    p.acb = acb;
    return (int)call_svc((void*)&p);
}

int aio_fsync(int op, struct aiocb *acb)
{
    svc_packet_aio_fsync_t p;

    p.id  = SVCID_AIO_FSYNC;
    p.op  = op;
    p.acb = acb;
    return (int)call_svc((void*)&p);
}

int lio_listio(int mode, struct aiocb *const list[],
        int nent, struct sigevent *restrict sig)
{
    svc_packet_lio_listio_t p;

    p.id   = SVCID_LIO_LISTIO;
    p.mode = mode;
    p.list = list;
    p.nent = nent;
    p.sig  = sig;
    return (int)call_svc((void*)&p);
}

int aio_worker(void *arg)
{
    svc_packet_aio_worker_t p;

    p.id  = SVCID_AIO_WORKER;
    p.arg = arg;
    return (int)call_svc((void*)&p);
}
