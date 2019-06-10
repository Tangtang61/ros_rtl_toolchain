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
[pt_rwlock_if.h] - MCOS Pthread rwlock API interface definitions
****************************************************************************/
#ifndef PTHREAD_RWLOCK_H
#define PTHREAD_RWLOCK_H

#include <pt_thread_if.h>

/*
  Bitfields in rwlock value
  locked  : 16  writer id or read locks
  wrlock  : 1   wrlock else rdlock
  pshared : 1   process-shared (unused)
  waiters : 14  waiters count
*/

#define RWLOCK_LOCKED_MASK   0xffff
#define RWLOCK_LOCKED_SHIFT       0
#define RWLOCK_WRLOCK_MASK        1
#define RWLOCK_WRLOCK_SHIFT      16
#define RWLOCK_PSHARED_MASK       1
#define RWLOCK_PSHARED_SHIFT     17
#define RWLOCK_WAITING_MASK  0x3fff
#define RWLOCK_WAITING_SHIFT     18

/* Invalid value is writelock flag & no writer id */
#define RWLOCK_INVALID_MASK  ((RWLOCK_LOCKED_MASK << RWLOCK_LOCKED_SHIFT) \
                              | (RWLOCK_WRLOCK_MASK << RWLOCK_WRLOCK_SHIFT))
#define RWLOCK_INVALID_VALUE (RWLOCK_WRLOCK_MASK << RWLOCK_WRLOCK_SHIFT)

#if (RWLOCK_WRLOCK_MASK << RWLOCK_WRLOCK_SHIFT) != ((RWLOCK_LOCKED_MASK + 1) << RWLOCK_LOCKED_SHIFT)
#error Please check wrlock bit
#endif

#if ((RWLOCK_INVALID_MASK & (RWLOCK_LOCKED_MASK << RWLOCK_LOCKED_SHIFT)) == 0)
#error Please check locked mask
#endif

/* Attributes */
#define RWLOCK_ATTR_SHARED  0x0001

 /* Server requests and replies */
#define PT_RWLOCK_BASE_REQID    (PT_BASE_REQID + (PT_RWLOCK_REQ_GRP << PT_REQ_GRP_SHFT))

#define PT_RWLOCK_CANCEL_REQID  (PT_WAIT_CANCEL_REQID + PT_RWLOCK_BASE_REQID)
#define PT_RWLOCK_CHGPRI_REQID  (PT_WAIT_CHGPRI_REQID + PT_RWLOCK_BASE_REQID)

/* Rwlock request message ids */
#define PT_RWLOCK_WAIT_REQID    (2 + PT_RWLOCK_BASE_REQID)
#define PT_RWLOCK_WAKE_REQID   (3 + PT_RWLOCK_BASE_REQID)
#define PT_RWLOCK_DESTROY_REQID (4 + PT_RWLOCK_BASE_REQID)

/* Rwlock request reply ids */
#define PT_RWLOCK_WAIT_REPID    (PT_OFFS_REPID + PT_RWLOCK_WAIT_REQID)
#define PT_RWLOCK_WAKE_REPID    (PT_OFFS_REPID + PT_RWLOCK_WAKE_REQID)
#define PT_RWLOCK_DESTROY_REPID (PT_OFFS_REPID + PT_RWLOCK_DESTROY_REQID)

/*
  Theory of operation.
  The idea is that Lock will always send Wait if
  rwlock is found Locked or Waiters exist.
  W(U,R) means rdlock, only waiters exist
  W(U,W) means wrlock, only waiters exist
  W(R,R) means rdlock, rwlock is rdlocked
  W(W,R) means rdlock, rwlock is wrlocked
  W(R,W) means wrlock, rwlock is rdlocked
  W(W,W) means wrlock, rwlock is wrlocked

  The Unlock will always send U-packet if Waiters exist.
  So if Waiters are present it is not possible
   - L->U rwlock transition without server assistance
   - U->L rwlock transition without server assistance
  However these transitions are possible if no Waiters
  
Requests to server
  U with no object creates it with U-state
  U with empty queue sets U-state
  U with waiters sets R/W-state and resumes waiter(s)

  (Locked, Locker)

  W(U,R) with no object creates it with R-state, continues
       Rwlock cannot be locked outside server if waiters
  W(U,R) with empty queue checks state
       if R-state continues
          Means U has not yet arrived or waiter was resumed
          (concurrently with the caller)
       if W-state enqueued
          Means U has not yet arrived or waiter was resumed
          (concurrently with the caller)
       if U-state sets R-state, continues
          Rwlock cannot be locked outside server.
  W(U,R) with waiters (means R or W state active)
       if W-state enqueued
       if R-state checks waiter priority
          if higher priority writer waiter, enqueued
          if lower priority waiter, continues

  W(U,W) with no object creates it with W-state, continues
       Rwlock cannot be locked outside server if waiters
  W(U,W) with empty queue checks state
       if W-state enqueued
          Means U has not yet arrived or waiter was resumed
          (rwlock cannot be unlocked outside server if waiters)
       if R-state enqueued
          Means U has not yet arrived or waiter was resumed
          (rwlock cannot be unlocked outside server if waiters)
       if U-state sets W-state, continues
          Rwlock cannot be locked outside server.
  W(U,W) with waiters, enqueued (means R or W state active)

  W(R,R) with no object creates it with R-state, continues
         Means waiters are registered but not yet reached server
  W(R,R) with empty queue checks state
         if R-state continues
            Means U has not been sent or reached the server
         if W-state sets R-state, continues
            Means lock type was changed outside the server
         if U-state sets R-state and returns EWOULDBLOCK
            Means either rwlock was locked outside server
            or U was received before W(R,R).
            Caller must recheck and will lock rwlock if unlocked
            or issue W(R,R) again, this time blocking.
  W(R,R) with waiters (means R-state active)
       if W-state - should not happen, state can't change!
       if R-state checks waiter priority
          if higher priority writer waiter, enqueued
          if lower priority waiter, continues

  W(R,W) with no object creates it with R-state, enqueued
         Means U has not been sent or yet reached the server.
  W(R,W) with empty queue checks state
         if W-state sets R-state, enqueued
            Means lock type was changed outside the server
         if R-state enqueued
            Means U has not been sent or reached the server
         if U-state sets R-state and returns EWOULDBLOCK
            Means either rwlock was locked outside server
            or U was received before W(R,W).
            Caller must recheck and will lock rwlock if unlocked
            or issue W(L) again, this time blocking.
  W(R,W) with waiters (means R-state active), enqueued
       if R-state, enqueued
       if W-state -  bug! state can't change outside server

  W(W,X) with no object creates it with W-state, enqueued
         Means U has not been sent or yet reached the server.
  W(W,X) with empty queue checks state
         if W-state enqueued
          Means U has not yet arrived or waiter was resumed
         if R-state, sets W-state, enqueued
            Means lock type was changed outside the server
         if U-state sets W-state and returns EWOULDBLOCK
            Means either rwlock was locked outside server
            or U was received before W(W,X).
            Caller must recheck and will lock rwlock if unlocked
            or issue W(L) again, this time blocking.
  W(W,X) with waiters (means W state active)
       if W-state, enqueued
       if R-state - bug! state can't change outside server

EWOULDBLOCK returned causes the Waiter to try again
lock the rwlock *without* counting other waiters.
Because EWOULDBLOCK will be returned only once this is safe.

Rwlock state transitions in server
  - rwlock object is created when
<!> - U is sent when waiters exist and reaches server before W
        U-state is set, although waiters may exit and rwlock locked
        So we can have here a state difference, thus
        a W(U,X) request will be resumed with EWOUDLOCK to recheck.
    - W(U,X) is sent when waiters found and reaches server before W
        X-state is set and caller continues.
        Correct because real rwlock cannot be locked without server.
    - W(R,R) is sent whan fastest waiter reaches server before U
        R-state is set and caller continues.
        Currect because real rwlock cannot be unlocked without server.
    - W(W,X) is sent whan fastest waiter reaches server before U
        W-state is set and caller is enqueued.
        Currect because real rwlock cannot be unlocked without server.

  - U->R transition in server
    - When W(U,R) is received with empty queue and object is U-state
      Correct because real rwlock cannot be locked without server.
    - When W(R,R) is received with empty queue and object is U-state
      Correct because real rwlock cannot be locked without server.
    - When W(W,R) is received with empty queue and object is U-state.
      R-state is set and EWOULDBLOCK is returned.
      Rationale is that U-state is either valid (U was received)
      and caller can try to lock the rwlock, or rwlock was locked
      outside the server and caller will issue W(W,R) again.

  - U->W transition in server
    - When W(U,W) is received with empty queue and object is U-state
      Correct because real rwlock cannot be locked without server.
    - When W(R,W) is received with empty queue and object is U-state
      Correct because real rwlock cannot be locked without server.
    - When W(W,W) is received with empty queue and object is U-state.
      W-state is set and EWOULDBLOCK is returned.
      Rationale is that U-state is either valid (U was received)
      and caller can try to lock the rwlock, or rwlock was locked
      outside the server and caller will issue W(W,W) again.

  - X->U transition in server
<!>   - U with empty queue sets U-state
        U-state is set, although waiters may exit and rwlock locked
        So we can have here a state difference, thus
        a W(X,U) request will be resumed with EWOUDLOCK to recheck.

Rwlock object states
  00 - Unlocked
  01 - R-locked
  10 - W-locked
  11 - unknown (unused)

When rwlock and server states are different
  - rwlock is X-state and server is U-state
    May happen when U was sent with no object or empty queue
    and subsequently rwlock was Locked with no waiters.
    The first waiter will call W(X,Y) and EWOULDBLOCK will
    be returned ans object will be set to L-state.
  - rwlock is U-state and server is X-state
    Happens when the last woken locker unlocks rwlock with no waiters.
    The next locker will lock it locally
    and first W request will fix the state in server.
  - rwlock is X-state and server is Y-state
    Happens when the last woken locker unlocks rwlock with no waiters
    and the next locker locks it with a different lock.
    This will be corrected at the first W request.
*/

/* Destroy rwlock (no reply) */
typedef struct pt_rwlock_destroy_req
{
    reqid_t      reqid;
    mcos_id_t    caller;
    uint32_t     rwlock;
} pt_rwlock_destroy_req_t;

/* Unlock rwlock (no reply) */
typedef struct pt_rwlock_wake_req
{
    reqid_t      reqid;
    mcos_id_t    caller;
    uint32_t     rwlock;
} pt_rwlock_wake_req_t;

/* Wait on the rwlock */
typedef struct pt_rwlock_wait_req
{
    reqid_t      reqid;
    mcos_id_t    caller;
    uint32_t     rwlock;
    uint8_t      thrpri;
    uint8_t      wrlock;
    uint16_t     rsvd16;
} pt_rwlock_wait_req_t;

/* Wait LS bits of wrlock address
   00 - unlocked
   01 - R-locked
   10 - W-locked
   11 - invalid */
#define RWLOCK_WAIT_UNLOCKED   0
#define RWLOCK_WAIT_RDLOCKED   1
#define RWLOCK_WAIT_WRLOCKED   2
#define RWLOCK_WAIT_INVALID    3
#define RWLOCK_WAIT_MASK       3

/* size as pt_api_wait_rep */
typedef struct pt_rwlock_wait_rep
{
    repid_t      repid;
    mcos_er_t    error;
    uint32_t     dummy[2];
} pt_rwlock_wait_rep_t;

/* Rwlock state bits (same as wait bits)
   00 - unlocked
   01 - R-locked
   10 - W-locked
   11 - unknown */
#define RWLOCK_STATE_UNLOCKED  0
#define RWLOCK_STATE_RDLOCKED  1
#define RWLOCK_STATE_WRLOCKED  2
#define RWLOCK_STATE_UNKNOWN   3
#define RWLOCK_STATE_MASK      3

/* Prototypes */
int pt_rwlock_timedwait(pttcb_t* pttcb, uint32_t rwlock, int wrlock, mcos_systime_t* absptr);

#endif /* PTHREAD_RWLOCK_H */
