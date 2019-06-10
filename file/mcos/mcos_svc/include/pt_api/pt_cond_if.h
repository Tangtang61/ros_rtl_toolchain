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
[pt_cond_if.h] - MCOS Pthread cond API interface definitions
****************************************************************************/
#ifndef PT_COND_IF_H
#define PT_COND_IF_H

#include <pt_thread_if.h>

/*
  Bitfield of cond value
  monotime  :  1 unused
  pshared   :  1 unused
  invalid   :  1
  waiting   : 29
*/
#define COND_MONOTIME_MASK       1
#define COND_MONOTIME_SHIFT      0
#define COND_PSHARED_MASK        1
#define COND_PSHARED_SHIFT       1
#define COND_INVALID_MASK        1
#define COND_INVALID_SHIFT       2
#define COND_WAITING_SHIFT       3
#define COND_WAITING_MASK        0x1fffffff

 /* Server requests and replies */
#define PT_COND_BASE_REQID       (PT_BASE_REQID + (PT_COND_REQ_GRP << PT_REQ_GRP_SHFT))

#define PT_COND_CANCEL_REQID     (PT_WAIT_CANCEL_REQID + PT_COND_BASE_REQID)
#define PT_COND_CHGPRI_REQID     (PT_WAIT_CHGPRI_REQID + PT_COND_BASE_REQID)

/* Cond request message ids */
#define PT_COND_WAIT_REQID      (2 + PT_COND_BASE_REQID)
#define PT_COND_SIGNAL_REQID    (3 + PT_COND_BASE_REQID)
#define PT_COND_DESTROY_REQID   (4 + PT_COND_BASE_REQID)

/* Cond request reply ids */
#define PT_COND_WAIT_REPID      (PT_OFFS_REPID + PT_COND_WAIT_REQID)
#define PT_COND_SIGNAL_REPID    (PT_OFFS_REPID + PT_COND_SIGNAL_REQID)
#define PT_COND_DESTROY_REPID   (PT_OFFS_REPID + PT_COND_DESTROY_REQID)

 /* Cond attributes */
#define COND_ATTR_MONOTIME 0x0001
#define COND_ATTR_SHARED   0x0002

/* Theory of operation.
   First wait request will create object.
   until cond is destroyed.
   Wait requests are enqueued.
   Signal request resumed first waiter.
   Broadcast resumes all waiters.
   Destroy request removes the object. */

#ifdef __cplusplus
extern "C" {
#endif

 /* Wait on cond request packet */
typedef struct pt_cond_wait_req
{
    reqid_t      reqid;  /* Request id */
    mcos_id_t    caller; /* Caller thread id */
    uint32_t     cond;   /* Cond address */
    uint8_t      thrpri; /* Caller priority */
    uint8_t      rsvd8;
    uint16_t     rsvd16;
} pt_cond_wait_req_t;

 /* Signal/broadcast cond request packet.
    If LS 2bits are nonzero it is broadcast */
typedef struct pt_cond_signal_req
{
    reqid_t      reqid;  /* Request id */
    mcos_id_t    caller; /* Caller thread id */
    uint32_t     cond;   /* Cond address & flags */
} pt_cond_signal_req_t;

#define PT_COND_SIGNAL    0
#define PT_COND_BROADCAST 1

 /* Destroy cond quest packet */
typedef struct pt_cond_destroy_req
{
    reqid_t      reqid;  /* Request id */
    mcos_id_t    caller; /* Caller thread id */
    uint32_t     cond;   /* Cond address */
} pt_cond_destroy_req_t;

 /* Cond wait reply header */
typedef struct pt_cond_wait_rep
{
    repid_t      repid;  /* Reply ID */
    mcos_er_t    error;  /* Error code */
    uint32_t     dummy[2]; /* Size as pt_api_wait_rep */
} pt_cond_wait_rep_t;

/* Cond signal and destroy have no reply */

 /* Prototype */
int pt_cond_timedwait(pthread_cond_t* restrict cond,
                      pthread_mutex_t* restrict mutex,
                      const mcos_systime_t* restrict stime);

#ifdef __cplusplus
}
#endif

#endif /* PT_COND_IF_H */
