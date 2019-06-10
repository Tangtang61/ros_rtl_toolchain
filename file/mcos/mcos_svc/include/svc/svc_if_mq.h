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
[svc_if_mq.h] - SVC interface library header (POSIX Message Queue)
****************************************************************************/

#ifndef SVC_IF_MQ_H
#define SVC_IF_MQ_H

#include <svc/svc_if.h>

/*
 * SVC Function ID
 */
#define SVCID_MQ_CLOSE             (SVCID_MQ | 0x00000000) /* mq_close()          */
#define SVCID_MQ_GETATTR           (SVCID_MQ | 0x00000001) /* mq_getattr()        */
#define SVCID_MQ_NOTIFY            (SVCID_MQ | 0x00000002) /* mq_notify()         */
#define SVCID_MQ_OPEN              (SVCID_MQ | 0x00000003) /* mq_open()           */
#define SVCID_MQ_RECEIVE           (SVCID_MQ | 0x00000004) /* mq_receive()        */
#define SVCID_MQ_TIMEDRECEIVE      (SVCID_MQ | 0x00000005) /* mq_timedreceive()   */
#define SVCID_MQ_SEND              (SVCID_MQ | 0x00000006) /* mq_send()           */
#define SVCID_MQ_TIMEDSEND         (SVCID_MQ | 0x00000007) /* mq_timedsend()      */
#define SVCID_MQ_SETATTR           (SVCID_MQ | 0x00000008) /* mq_setattr()        */
#define SVCID_MQ_UNLINK            (SVCID_MQ | 0x00000009) /* mq_unlink()         */
                                                                          
#ifndef _in_asm_source_

/*
 * SVC Parameter Packet
 */
#include <mqueue.h>

/* mq_close()          */
typedef struct {
    int                   id;
    mqd_t                 mqdes;
} svc_packet_mq_close_t;

/* mq_getattr()        */
typedef struct {
    int                   id;
    mqd_t                 mqdes;
    struct mq_attr        *mqstat;
} svc_packet_mq_getattr_t;

/* mq_notify()         */
typedef struct {
    int                   id;
    mqd_t                 mqdes;
    const struct sigevent *notification;
} svc_packet_mq_notify_t;

/* mq_open()           */
typedef struct {
    int                   id;
    const char            *name;
    int                   oflag;
    mode_t                mode;
    struct mq_attr        *attr;
    mqd_t                 *mqdes_ptr;
} svc_packet_mq_open_t;

/* mq_receive()        */
typedef struct {
    int                   id;
    mqd_t                 mqdes;
    char                  *msg_ptr;
    size_t                msg_len;
    unsigned              *msg_prio;
    ssize_t               *received_len;
} svc_packet_mq_receive_t;

/* mq_timedreceive()   */
typedef struct {
    int                   id;
    mqd_t                 mqdes;
    char                  *restrict msg_ptr;
    size_t                msg_len;
    unsigned              *restrict msg_prio;
    const struct timespec *restrict abstime;
    ssize_t               *received_len;
} svc_packet_mq_timedreceive_t;

/* mq_send()           */
typedef struct {
    int                   id;
    mqd_t                 mqdes;
    const char            *msg_ptr;
    size_t                msg_len;
    unsigned              msg_prio;
} svc_packet_mq_send_t;

/* mq_timedsend()      */
typedef struct {
    int                   id;
    mqd_t                 mqdes;
    const char            *msg_ptr;
    size_t                msg_len;
    unsigned              msg_prio;
    const struct timespec *abstime;
} svc_packet_mq_timedsend_t;

/* mq_setattr()        */
typedef struct {
    int                   id;
    mqd_t                 mqdes;
    const struct mq_attr  *restrict mqstat;
    struct mq_attr        *restrict omqstat;
} svc_packet_mq_setattr_t;

/* mq_unlink()         */
typedef struct {
    int                   id;
    const char            *name;
} svc_packet_mq_unlink_t;

/* ID of POSIX Message Queue */
typedef struct {
    int                   id;
} svc_packet_mq_t;

#endif /* _in_asm_source_ */

#endif  /* #ifndef SVC_IF_MQ_H */
