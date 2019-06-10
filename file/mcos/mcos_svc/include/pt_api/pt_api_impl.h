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
[pt_api_impl.h] - Header for pthread TCB
****************************************************************************/
#ifndef PT_API_IMPL_H
#define PT_API_IMPL_H

#include <limits.h>
#include <mcos/mcos.h>
#include <signal.h>
#include <pt_api/pt.cfg>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef short int16_t;

#ifdef MCOS_USE_PROCESS_MODEL
#error "MCOS_USE_PROCESS_MODEL" is set somewhere unexpected.
#else
#define MCOS_USE_PROCESS_MODEL 1
#endif

#define MCOS_INLINE static inline

#define PT_NAME_MAX     (16)
typedef void (*funcPtr)();

typedef struct mcos_tcb
{
    void*           exinf;
    funcPtr         task;

    unsigned short  tskatr;
    signed short    mtxlist;

    mcos_id_t       tskid;
    unsigned char   tskpri;
    unsigned char   basepri;
    unsigned char   tskevt;
    unsigned char   wupcnt;
    mcos_id_t       waitid;

    unsigned int    tskwait:24;
    unsigned int    ceilpri:8;

    unsigned int    diswait:24;
    unsigned int    inipri:8;

    char dsname[PT_NAME_MAX];
} mcos_tcb_t;

#ifdef __GNUC__
#define PT_LITTLE_ENDIAN   (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#else
#error Please fix compile-time endian check
#endif

typedef struct pttcb
{
    mcos_tcb_t   mcostcb;
#define pthrent  mcostcb.task
#define pthrid   mcostcb.tskid
#define pthrpri  mcostcb.tskpri
#define pbasepri mcostcb.basepri
#define ptname   mcostcb.dsname

#if PT_LITTLE_ENDIAN
    uint16_t    flags;
    mcos_id_t   joiner;
#else
    mcos_id_t   joiner;
    uint16_t    flags;
#endif
    sigset_t    sigenab;
    sigset_t    sigpend;
    void*       cleanup;
    void*       robust;
#if MCOS_USE_PROCESS_MODEL
    void*       sigentry;
    void*       saventry;
    pid_t       pid;
#endif
    void*       ptspec[MCOS_CFG_PT_NUM_KEY];
} pttcb_t;

#define PTHREAD_PTHREAD     0x0001
#define PTHREAD_CANCELOK    0x0002
#define PTHREAD_CANENAB     0x0004
#define PTHREAD_CANASYNC    0x0008
#define PTHREAD_WAITING     0x0010
#define PTHREAD_WAITEND     0x0020
#define PTHREAD_CANPEND     0x0040
#define PTHREAD_WAKEUP      0x0080
#define PTHREAD_DETACHED    0x0100
#define PTHREAD_RRSCHED     0x0200
#define PTHREAD_TERMINATED  0x0400
#define PTHREAD_SPECIFIC    0x0800
#define PTHREAD_JOIN        0x0800
#define PTHREAD_USERSTACK   0x1000

#if MCOS_USE_PROCESS_MODEL
#define PTHREAD_PROCESS     0x2000
#endif

#define PT_NUM_SIG  (sizeof(sigset_t) * CHAR_BIT)

#ifdef __cplusplus
}
#endif

pttcb_t* pt_get_pttcb(void);
void pt_handle_interrupt(pttcb_t* pttcb);
void* _pt_handle_interrupt(pttcb_t* pttcb, siginfo_t* info, sigset_t* mask);
void* pt_signal_handler(void);
void pt_signal_entry(void);
int pt_init_signal_entry(void);
void* pt_signal_get(siginfo_t *info, sigset_t *rest);

#define CHECK_ALIGN(_x_, _a_)  ((unsigned)(uintptr_t)(_x_) & ((_a_) - 1))

#define STACK_ALIGN     8

#define CHECK_SPACE_ALIGN(_x_, _y_) ((uintptr_t)(_x_) & ((_y_) - 1))

#endif /* PT_API_IMPL.H */
