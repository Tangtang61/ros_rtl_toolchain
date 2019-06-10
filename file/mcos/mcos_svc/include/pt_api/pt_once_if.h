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
[pt_once_if.h] - MCOS Pthread once API interface definitions
****************************************************************************/
#ifndef PT_ONCE_IF_H
#define PT_ONCE_IF_H

/*
  Bitfield of once value
  locked    : 1   locked for init
  finished  : 1   finished
  server    : 1   server was accessed
  waiting   : 29  waiting threads count
*/
#define ONCE_LOCKED_MASK       1
#define ONCE_LOCKED_SHIFT      0
#define ONCE_FINISH_MASK       1
#define ONCE_FINISH_SHIFT      1
#define ONCE_SERVER_MASK       1
#define ONCE_SERVER_SHIFT      2
#define ONCE_WAITING_SHIFT     3
#define ONCE_WAITING_MASK      0x1fffffff

#if (ONCE_LOCKED_MASK << ONCE_LOCKED_SHIFT) != 1
#error Please check once locked bit
#endif

#if (ONCE_FINISH_MASK << ONCE_FINISH_SHIFT) != 2
#error Please check once finished bit
#endif

/* Should be in sync with pthread.h */
#define ONCE_INIT_VALUE        0

#define PT_ONCE_BASE_REQID    (PT_BASE_REQID + (PT_ONCE_REQ_GRP << PT_REQ_GRP_SHFT))

/* Common server requests */
#define PT_ONCE_CANCEL_REQID  (PT_WAIT_CANCEL_REQID + PT_ONCE_BASE_REQID)
#define PT_ONCE_CHGPRI_REQID  (PT_WAIT_CHGPRI_REQID + PT_ONCE_BASE_REQID)

/* Once request message ids */
#define PT_ONCE_WAIT_REQID    (2 + PT_ONCE_BASE_REQID)
#define PT_ONCE_FINISH_REQID  (3 + PT_ONCE_BASE_REQID)

/* Once request reply ids */
#define PT_ONCE_WAIT_REPID    (PT_OFFS_REPID + PT_ONCE_WAIT_REQID)
#define PT_ONCE_FINISH_REPID  (PT_OFFS_REPID + PT_ONCE_FINISH_REQID)

/* Theory of operation.
   First wait request will create object in server,
   the server bit will be set in object.
   Finish request will be called by the locker thread
   with a flag that waiters are present or not.
   In the former case server will set finished flag
   and resume all waiters. In the latter case object is removed.
   The last waiting thread will call server with remove.
   LS bits of once address are
   00 - used by wait request
   01 - used when locker thread was canceled to wakeup waiter
   10 - used by locker thread to denote once finished
   11 - used by last waiter thread to remove once object
 */

#ifdef __cplusplus
extern "C" {
#endif

 /* Wait on once request packet */
typedef struct pt_once_wait_req
{
    reqid_t      reqid;  /* Request id */
    mcos_id_t    caller; /* Caller thread id */
    uint32_t     once;   /* Once address */
    uint8_t      thrpri; /* Caller priority */
    uint8_t      rsvd8;
    uint16_t     rsvd16;
} pt_once_wait_req_t;

 /* Finish once request packet */
typedef struct pt_once_finish_req
{
    reqid_t      reqid;  /* Request id */
    mcos_id_t    caller; /* Caller thread id */
    uint32_t     once;   /* Once address & flags */
} pt_once_finish_req_t;

 /* Once wait reply header */
typedef struct pt_once_wait_rep
{
    repid_t      repid;  /* Reply ID */
    mcos_er_t    error;  /* Error code */
    uint32_t     dummy[2];  /* Size as pt_api_wait_rep */
} pt_once_wait_rep_t;

/* Once finish request has no reply */

/* pthread_once() helpers */
int pt_once_locked(uint32_t once);
int pt_once_finish(uint32_t once);

#ifdef __cplusplus
}
#endif

#endif /* PT_ONCE_IF_H */
