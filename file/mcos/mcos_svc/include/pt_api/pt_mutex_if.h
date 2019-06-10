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
[pt_mutex_if.h] - MCOS Pthread mutex interface definitions
****************************************************************************/
#ifndef PT_MUTEX_IF_H
#define PT_MUTEX_IF_H

#include <pt_thread_if.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Bitfield mutex value structure.
   Tuned to allow 32-bit mutex only.
   locked    :  1    locked if nonzero
   pshared   :  1    process shared (unused)
   errcheck  :  1    errorcheck mutex if nonzero
   recursive :  1    recursive mutex if nonzero
   inherit   :  1    priority inherit if nonzero
   protected :  1    priority protect if nonzero
   robust    :  1    robust mutex if nonzero
   ownerdead :  1    robust mutex owner dead
   ceiling   :  8    ceiling/ownerpri if protected
   waiting   : 16    waiting threads count
*/
#define MUTEX_LOCKED_MASK           1
#define MUTEX_LOCKED_SHIFT          0
#define MUTEX_PSHARED_MASK          1
#define MUTEX_PSHARED_SHIFT         1
#define MUTEX_KIND_MASK             3
#define MUTEX_KIND_SHIFT            2
#define MUTEX_ERRORCHECK_MASK       1
#define MUTEX_ERRORCHECK_SHIFT      2
#define MUTEX_RECURSIVE_MASK        1
#define MUTEX_RECURSIVE_SHIFT       3
#define MUTEX_PROTECT_MASK          3
#define MUTEX_PROTECT_SHIFT         4
#define MUTEX_INHERIT_MASK          1
#define MUTEX_INHERIT_SHIFT         4
#define MUTEX_PRIOCEIL_MASK         1
#define MUTEX_PRIOCEIL_SHIFT        5
#define MUTEX_ROBUST_MASK           1
#define MUTEX_ROBUST_SHIFT          6
#define MUTEX_OWNERDEAD_MASK        1
#define MUTEX_OWNERDEAD_SHIFT       7
#define MUTEX_CEILING_MASK       0xff
#define MUTEX_CEILING_SHIFT         8
#define MUTEX_WAITING_MASK     0xffff
#define MUTEX_WAITING_SHIFT        16

#if (MUTEX_LOCKED_MASK << MUTEX_LOCKED_SHIFT) != 1
#error Please check locked bit
#endif

/* Locked & errorcheck & owner dead is the invalid mutex value */
#define MUTEX_INVALID_MASK      ((MUTEX_LOCKED_MASK << MUTEX_LOCKED_SHIFT) \
                                 | (MUTEX_ERRORCHECK_MASK << MUTEX_ERRORCHECK_SHIFT) \
                                 | (MUTEX_ROBUST_MASK << MUTEX_ROBUST_SHIFT) \
                                 | (MUTEX_OWNERDEAD_MASK << MUTEX_OWNERDEAD_SHIFT))

#define MUTEX_INVALID_VALUE     ((MUTEX_LOCKED_MASK << MUTEX_LOCKED_SHIFT) \
                                 | (MUTEX_ERRORCHECK_MASK << MUTEX_ERRORCHECK_SHIFT) \
                                 | (MUTEX_OWNERDEAD_MASK << MUTEX_OWNERDEAD_SHIFT))

/* Locked & recursive & owner dead is the notrecoverable mutex value */
#define MUTEX_NOTRECOVER_MASK   ((MUTEX_LOCKED_MASK << MUTEX_LOCKED_SHIFT) \
                                 | (MUTEX_RECURSIVE_MASK << MUTEX_RECURSIVE_SHIFT) \
                                 | (MUTEX_ROBUST_MASK << MUTEX_ROBUST_SHIFT) \
                                 | (MUTEX_OWNERDEAD_MASK << MUTEX_OWNERDEAD_SHIFT))

#define MUTEX_NOTRECOVER_VALUE  ((MUTEX_LOCKED_MASK << MUTEX_LOCKED_SHIFT) \
                                 | (MUTEX_RECURSIVE_MASK << MUTEX_RECURSIVE_SHIFT) \
                                 | (MUTEX_OWNERDEAD_MASK << MUTEX_OWNERDEAD_SHIFT))

 /* Server requests and replies */
#define PT_MUTEX_BASE_REQID     (PT_BASE_REQID + (PT_MUTEX_REQ_GRP << PT_REQ_GRP_SHFT))

#define PT_MUTEX_CANCEL_REQID   (PT_WAIT_CANCEL_REQID + PT_MUTEX_BASE_REQID)
#define PT_MUTEX_CHGPRI_REQID   (PT_WAIT_CHGPRI_REQID + PT_MUTEX_BASE_REQID)

#define PT_MUTEX_DESTROY_REQID  (2 + PT_MUTEX_BASE_REQID)
#define PT_MUTEX_WAIT_REQID     (3 + PT_MUTEX_BASE_REQID)
#define PT_MUTEX_WAKE_REQID     (4 + PT_MUTEX_BASE_REQID)

#define PT_MUTEX_DESTROY_REPID  (PT_OFFS_REPID + PT_MUTEX_DESTROY_REQID)
#define PT_MUTEX_WAIT_REPID     (PT_OFFS_REPID + PT_MUTEX_WAIT_REQID)
#define PT_MUTEX_WAKE_REPID     (PT_OFFS_REPID + PT_MUTEX_WAKE_REQID)

 /*
  Theory of operation.
  The idea is that Lock will always send Wait if
  mutex is found Locked or Waiters exist.
  W(U) means only waiters exist
  W(L) means mutex is locked and may be waiters exist.
  The Unlock will always send U-packet if Waiters exist.
  So if Waiters are present it is not possible
   - L->U mutex transition without server assistance
   - U->L mutex transition without server assistance
  However these transitions are possible if no Waiters

Requests to server
  U with no object creates it with U-state
  U with empty queue sets U-state
  U with waiters sets L-state and resumes a waiter

  W(U) with no object creates it with L-state, continues
       Mutex cannot be locked outside server if waiters
  W(U) with empty queue checks state
       if L-state enqueued
          Means U has not yet arrived or waiter was resumed
          (concurrently with the caller)
       if U-state sets L-state, continues
          Mutex cannot be locked outside server if waiters
  W(U) with waiters - enqueued (means L-state active)

  W(L) with no object creates it with L-state, enqueued
       Means U has not been sent or yet reached the server.
  W(L) with empty queue checks state
       if L-state enqueued
          Means U has not been sent or reached the server
          (mutex cannot be unlocked outside server if waiters)
       if U-state sets L-state and returns EWOULDBLOCK
          Means either mutex was locked outside server
          or U was received before W(L)
          Caller must recheck and will lock mutex if unlocked
          or issue W(L) again, this time blocking
  W(L) with waiters - enqueued (means L-state active)

EWOULDBLOCK returned causes the Waiter to try again
lock the mutex *without* counting other waiters.
Because EWOULDBLOCK will be returned only once this is safe.

Mutex state transitions in server
  - mutex object is created when
<!> - U is sent when waiters exist and reaches server before W
        U-state is set, although waiters may exit and mutex locked
        So we can have here a state difference, thus
        a W(L) request will be resumed with EWOUDLOCK to recheck.
    - W(U) is sent when waiters found and reaches server before W
        L-state is set and caller continues.
        Correct because real mutex cannot be locked without server.
    - W(L) is sent whan fastest waiter reaches server before U
        L-state is set and caller is enqueued.
        Currect because real mutex cannot be unlocked without server.

  - U->L transition in server
    - When W(U) is received with empty queue and object is U-state
      Correct because real mutex cannot be locked without server.
    - When W(L) is received with empty queue and object is U-state.
      L-state is set and EWOULDBLOCK is returned.
      Rationale is that U-state is either valid (U was received)
      and caller can try to lock the mutex, or mutex was locked
      outside the server and caller will issue W(L) again.

  - L->U transition in server
<!>   - U with empty queue sets U-state
        U-state is set, although waiters may exit and mutex locked
        So we can have here a state difference, thus
        a W(L) request will be resumed with EWOUDLOCK to recheck.

Mutex object states
  00 - Unlocked
  01 - Locked
  10 - Nonrecover
  11 - Illegal

When mutex and server states are different
  - mutex is L-state and server is U-state
    May happen when U was sent with no object or empty queue
    and subsequently mutex was Locked with no waiters.
    The first waiter will call W(L) and EWOULDBLOCK will
    be returned ans object will be set to L-state.
  - mutex is U-state and server is L-state
    Happens when the last woken locker unlocks mutex with no waiters.
    Next locker will lock the mutex so states will be consistent.
 */

typedef struct pt_mutex_destroy_req
{
    reqid_t      reqid;
    mcos_id_t    caller;
    uint32_t     mutex;
} pt_mutex_destroy_req_t;

typedef struct pt_mutex_wait_req
{
    reqid_t      reqid;
    mcos_id_t    caller;
    uint32_t     mutex;
    uint8_t      thrpri;
    uint8_t      rsvd8;
    uint16_t     rsvd16;
} pt_mutex_wait_req_t;

typedef struct pt_mutex_wake_req
{
    reqid_t      reqid;
    mcos_id_t    caller;
    uint32_t     mutex;
} pt_mutex_wake_req_t;

 /* Mutex wake bits */
#define MUTEX_WAIT_NOTRECOVER   1

 /* Mutex object states */
#define MUTEX_STATE_UNLOCKED    0
#define MUTEX_STATE_LOCKED      1
#define MUTEX_STATE_NOTRECOVER  2
#define MUTEX_STATE_INVALID     3
#define MUTEX_STATE_MASK        3

typedef struct pt_mutex_wait_rep
{
    repid_t      repid;
    mcos_er_t    error;
    uint32_t     dummy[2]; /* size as pt_api_wait_rep */
} pt_mutex_wait_rep_t;

/* Mutex attributes */
#define MUTEX_ATTR_TYPE_MASK        0x03
#define MUTEX_ATTR_TYPE_SHIFT       2
#define MUTEX_ATTR_PROTOCOL_MASK    0x03
#define MUTEX_ATTR_PROTOCOL_SHIFT   4
#define MUTEX_ATTR_ROBUST_MASK      1
#define MUTEX_ATTR_ROBUST_SHIFT     6
#define MUTEX_ATTR_SHARED_MASK      0x01
#define MUTEX_ATTR_SHARED_SHIFT     7
#define MUTEX_ATTR_PRIO_MASK        0xff
#define MUTEX_ATTR_PRIO_SHIFT       8

/* Invalidation and validation check */
#define MUTEX_ATTR_INVALID          0
#define MUTEX_ATTR_DEFAULT          (((MCOS_CFG_PT_MAX_PRI - MCOS_CFG_PT_MIN_PRI + 1) / 2) << MUTEX_ATTR_PRIO_SHIFT)

int pt_mutexattr_valid(const pthread_mutexattr_t* attr);

#ifdef __cplusplus
}
#endif

#endif /* PT_MUTEX_IF_H */
