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
[mq_svc.c] - SVC interface library (POSIX Message Queue)
****************************************************************************/

#include <svc/svc_if.h>

#define mq_open __mq_open__
#include <svc/svc_if_mq.h>
#undef mq_open

int mq_close(mqd_t mqdes)
{
    svc_packet_mq_close_t p;

    p.id = SVCID_MQ_CLOSE;
    p.mqdes = mqdes;
    return (int)call_svc((void*)&p);
}

int mq_getattr(mqd_t mqdes, struct mq_attr *mqstat)
{
    svc_packet_mq_getattr_t p;

    p.id = SVCID_MQ_GETATTR;
    p.mqdes = mqdes;
    p.mqstat = mqstat;
    return (int)call_svc((void*)&p);
}

int mq_notify(mqd_t mqdes, const struct sigevent *notification)
{
    svc_packet_mq_notify_t p;

    p.id = SVCID_MQ_NOTIFY;
    p.mqdes = mqdes;
    p.notification = notification;
    return (int)call_svc((void*)&p);
}

mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr)
{
    svc_packet_mq_open_t p;
    mqd_t mqdes;

    p.id = SVCID_MQ_OPEN;
    p.name = name;
    p.oflag = oflag;
    p.mode = mode;
    p.attr = attr;
    p.mqdes_ptr = &mqdes;
    (void)call_svc((void*)&p);
    return *p.mqdes_ptr;
}

ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len,
        unsigned *msg_prio)
{
    svc_packet_mq_receive_t p;
    ssize_t received_len;

    p.id = SVCID_MQ_RECEIVE;
    p.mqdes = mqdes;
    p.msg_ptr = msg_ptr;
    p.msg_len = msg_len;
    p.msg_prio = msg_prio;
    p.received_len = &received_len;
    (void)call_svc((void*)&p);
    return *p.received_len;
}

ssize_t mq_timedreceive(mqd_t mqdes, char *restrict msg_ptr,
        size_t msg_len, unsigned *restrict msg_prio,
        const struct timespec *restrict abstime)
{
    svc_packet_mq_timedreceive_t p;
    ssize_t received_len;

    p.id = SVCID_MQ_TIMEDRECEIVE;
    p.mqdes = mqdes;
    p.msg_ptr = msg_ptr;
    p.msg_len = msg_len;
    p.msg_prio = msg_prio;
    p.abstime = abstime;
    p.received_len = &received_len;
    (void)call_svc((void*)&p);
    return *p.received_len;
}

int mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len,
        unsigned msg_prio)
{
    svc_packet_mq_send_t p;

    p.id = SVCID_MQ_SEND;
    p.mqdes = mqdes;
    p.msg_ptr = msg_ptr;
    p.msg_len = msg_len;
    p.msg_prio = msg_prio;
    return (int)call_svc((void*)&p);
}

int mq_timedsend(mqd_t mqdes, const char *msg_ptr, size_t msg_len,
        unsigned msg_prio, const struct timespec *abstime)
{
    svc_packet_mq_timedsend_t p;

    p.id = SVCID_MQ_TIMEDSEND;
    p.mqdes = mqdes;
    p.msg_ptr = msg_ptr;
    p.msg_len = msg_len;
    p.msg_prio = msg_prio;
    p.abstime = abstime;
    return (int)call_svc((void*)&p);
}

int mq_setattr(mqd_t mqdes, const struct mq_attr *restrict mqstat,
        struct mq_attr *restrict omqstat)
{
    svc_packet_mq_setattr_t p;

    p.id = SVCID_MQ_SETATTR;
    p.mqdes = mqdes;
    p.mqstat = mqstat;
    p.omqstat = omqstat;
    return (int)call_svc((void*)&p);
}

int mq_unlink(const char *name)
{
    svc_packet_mq_unlink_t p;

    p.id = SVCID_MQ_UNLINK;
    p.name = name;
    return (int)call_svc((void*)&p);
}

