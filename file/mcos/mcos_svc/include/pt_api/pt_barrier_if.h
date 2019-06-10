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
[pt_barrier_if.h] - MCOS Pthread barrier interface definitions
****************************************************************************/
#ifndef PT_BARRIER_IF_H
#define PT_BARRIER_IF_H

#include <pt_thread_if.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Bitfield barrier value structure.
  pshared  :  1  process-shared
  count    : 15  target threads count
  waiting  : 16  waiting threads count
*/
#define BARRIER_PSHARED_MASK          1
#define BARRIER_PSHARED_SHIFT         0
#define BARRIER_COUNT_MASK       0x7fff
#define BARRIER_COUNT_SHIFT           1
#define BARRIER_WAITING_MASK     0xffff
#define BARRIER_WAITING_SHIFT        16

/* Zero count is invalid */
#define BARRIER_INVALID_MASK      BARRIER_COUNT_MASK
#define BARRIER_INVALID_SHIFT     BARRIER_COUNT_SHIFT
#define BARRIER_INVALID_VALUE     0

 /* Delete barrier in server */
#define BARRIER_DESTROY_MASK       1
#define BARRIER_DESTROY_SHIFT      0

 /* Barrier attributes */
#define BARRIER_ATTR_SHARED  0x0001

 /* Server requests and replies */
#define PT_BARRIER_BASE_REQID     (PT_BASE_REQID + (PT_BARRIER_REQ_GRP << PT_REQ_GRP_SHFT))

#define PT_BARRIER_CANCEL_REQID   (PT_WAIT_CANCEL_REQID + PT_BARRIER_BASE_REQID)
#define PT_BARRIER_CHGPRI_REQID   (PT_WAIT_CHGPRI_REQID + PT_BARRIER_BASE_REQID)

#define PT_BARRIER_WAIT_REQID     (2 + PT_BARRIER_BASE_REQID)
#define PT_BARRIER_DESTROY_REQID  (3 + PT_BARRIER_BASE_REQID)

#define PT_BARRIER_WAIT_REPID     (PT_OFFS_REPID + PT_BARRIER_WAIT_REQID)
#define PT_BARRIER_DESTROY_REPID  (PT_OFFS_REPID + PT_BARRIER_DESTROY_REQID)

 /* Inform server for destroyed barrier.
    LS bit tells to delete it */
typedef struct pt_barrier_destroy_req
{
    reqid_t      reqid;
    mcos_id_t    caller;
    uint32_t     barrier;
} pt_barrier_destroy_req_t;

/* Wait on the barrier */
typedef struct pt_barrier_wait_req
{
    reqid_t      reqid;
    mcos_id_t    caller;
    uint32_t     barrier;
    uint16_t     count;
    uint8_t      thrpri;
    uint8_t      rsvd8;
} pt_barrier_wait_req_t;

/* size as pt_api_wait_rep */
typedef struct pt_barrier_wait_rep
{
    repid_t      repid;
    mcos_er_t    error;
    uint32_t     dummy[2];
} pt_barrier_wait_rep_t;

#ifdef __cplusplus
}
#endif

#endif /* PT_BARRIER_IF_H */
