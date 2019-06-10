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
[svc_if_aio.h] - SVC interface library header (POSIX Async I/O)
****************************************************************************/

#ifndef SVC_IF_AIO_H
#define SVC_IF_AIO_H

#include <svc/svc_if.h>

/*
 * SVC Function ID
 */
#define SVCID_AIO_READ      (SVCID_AIO | 0x00000000)    /* aio_read()    */
#define SVCID_AIO_WRITE     (SVCID_AIO | 0x00000001)    /* aio_write()   */
#define SVCID_AIO_CANCEL    (SVCID_AIO | 0x00000002)    /* aio_cancel()  */
#define SVCID_AIO_SUSPEND   (SVCID_AIO | 0x00000003)    /* aio_suspend() */
#define SVCID_AIO_RETURN    (SVCID_AIO | 0x00000004)    /* aio_return()  */
#define SVCID_AIO_ERROR     (SVCID_AIO | 0x00000005)    /* aio_error()   */
#define SVCID_AIO_FSYNC     (SVCID_AIO | 0x00000006)    /* aio_fsync()   */
#define SVCID_LIO_LISTIO    (SVCID_AIO | 0x00000007)    /* lio_listio()  */
#define SVCID_AIO_WORKER    (SVCID_AIO | 0x00000008)    /* aio_worker()  */

#ifndef _in_asm_source_

/*
 * SVC Parameter Packet
 */
#include <pthread.h>

/* aio_read() */
typedef struct {
    int         id;
    struct      aiocb* acb;
} svc_packet_aio_read_t;

/* aio_write() */
typedef struct {
    int         id;
    struct      aiocb* acb;
} svc_packet_aio_write_t;

/* aio_cancel() */
typedef struct {
    int         id;
    int         fildes;
    struct      aiocb* acb;
} svc_packet_aio_cancel_t;

/* aio_suspend() */
typedef struct {
    int          id;
    const struct aiocb* const* list;
    int          nent;
    const struct timespec* timeout;
} svc_packet_aio_suspend_t;

/* aio_return() */
typedef struct {
    int         id;
    struct      aiocb* acb;
    ssize_t     *return_len;
} svc_packet_aio_return_t;

/* aio_error() */
typedef struct {
    int          id;
    const struct aiocb* acb;
} svc_packet_aio_error_t;

/* aio_fsync() */
typedef struct {
    int         id;
    struct      aiocb* acb;
    int         op;
} svc_packet_aio_fsync_t;

/* lio_listio() */
typedef struct {
    int         id;
    int         mode;
    struct      aiocb * const* list;
    int         nent;
    struct      sigevent *restrict sig;
} svc_packet_lio_listio_t;

/* aio_worker_pthread() */
typedef struct {
    int         id;
    void        *arg;
} svc_packet_aio_worker_t;

/* ID of POSIX Async I/O */
typedef struct {
    int         id;
} svc_packet_aio_t;

#endif /* _in_asm_source_ */

#endif  /* #ifndef SVC_IF_AIO_H */
