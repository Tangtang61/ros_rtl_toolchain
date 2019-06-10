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
[svc_if_signal.h] - SVC interface library header (POSIX Signal)
****************************************************************************/

#ifndef SVC_IF_SIGNAL_H
#define SVC_IF_SIGNAL_H

#include <svc/svc_if.h>

/*
 * SVC Function ID
 */
#define SVCID_SIGNAL_PTHREAD_KILL       (SVCID_SIGNAL | 0x00000000)     /* pthread_kill()   */
#define SVCID_SIGNAL_PTHREAD_SIGMASK    (SVCID_SIGNAL | 0x00000001)     /* pthread_sigmask()*/
#define SVCID_SIGNAL_SIGACTION          (SVCID_SIGNAL | 0x00000002)     /* sigaction()      */
#define SVCID_SIGNAL_SIGWAIT            (SVCID_SIGNAL | 0x00000003)     /* sigwait()        */
#define SVCID_SIGNAL_SIGTIMEDWAIT       (SVCID_SIGNAL | 0x00000004)     /* sigtimedwait()   */
#define SVCID_SIGNAL_SIGPENDING         (SVCID_SIGNAL | 0x00000005)     /* sigpending()     */
#define SVCID_SIGNAL_SIGSUSPEND         (SVCID_SIGNAL | 0x00000006)     /* sigsuspend()     */
#define SVCID_SIGNAL_SIGQUEUE           (SVCID_SIGNAL | 0x00000007)     /* sigqueue()       */
#define SVCID_SIGNAL_PT_SIGNAL_GET      (SVCID_SIGNAL | 0x00000008)     /* pt_signal_get()  */
#define SVCID_PT_HANDLE_INTERRUPT       (SVCID_SIGNAL | 0x00000009)     /* _pt_handle_interrupt() */

/*
 * SVC Parameter Packet
 */
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

/* pt_signal_get() */
typedef struct {
    int         id;
    siginfo_t   *info;
    sigset_t    *rest;
    void        **hdl;
} svc_packet_signal_pt_signal_get_t;

typedef struct pttcb pttcb_t;
typedef struct {
    int         id;
    pttcb_t     *pttcb;
    siginfo_t   *info;
    sigset_t    *mask;
    void        **hdl;
} svc_packet_pt_handle_interrupt_t;

/* pthread_kill() */
typedef struct {
    int         id;
    pthread_t   thread;
    int         sig;
} svc_packet_signal_pthread_kill_t;

/* pthread_sigmask() */
typedef struct {
    int                     id;
    int                     how;
    const sigset_t          *restrict set;
    sigset_t                *restrict old;
} svc_packet_signal_pthread_sigmask_t;

/* sigaction() */
typedef struct {
    int                     id;
    int                     signo;
    const struct sigaction  *restrict act;
    struct sigaction        *restrict old;
} svc_packet_signal_sigaction_t;

/* sigwait() */
typedef struct {
    int                     id;
    const sigset_t          *restrict set;
    int                     *restrict sig;
} svc_packet_signal_sigwait_t;

/* sigtimedwait() */
typedef struct {
    int                     id;
    const sigset_t          *restrict set;
    siginfo_t               *restrict info;
    const struct timespec   *restrict timeout;
} svc_packet_signal_sigtimedwait_t;

/* sigpending() */
typedef struct {
    int                     id;
    sigset_t                *set;
} svc_packet_signal_sigpending_t;

/* sigsuspend() */
typedef struct {
    int                     id;
    const sigset_t          *sigmask;
} svc_packet_signal_sigsuspend_t;

/* sigqueue() */
typedef struct {
    int                     id;
    pid_t                   pid;
    int                     signo;
    union sigval            value;
} svc_packet_signal_sigqueue_t;

/* List of Signal APIs */
typedef union {
    int         id;
    svc_packet_signal_pthread_kill_t    param_signal_pthread_kill_;
    svc_packet_signal_pthread_sigmask_t param_signal_pthread_sigmask_;
    svc_packet_signal_sigaction_t       param_signal_sigaction_;
    svc_packet_signal_sigwait_t         param_signal_sigwait_;
    svc_packet_signal_sigtimedwait_t    param_signal_sigtimedwait_;
    svc_packet_signal_sigpending_t      param_signal_sigpending_;
    svc_packet_signal_sigsuspend_t      param_signal_sigsuspend_;
    svc_packet_signal_sigqueue_t        param_signal_sigqueue_;
    svc_packet_signal_pt_signal_get_t   param_signal_pt_signal_get_;
    svc_packet_pt_handle_interrupt_t    param_pt_handle_interrupt_;
} svc_packet_signal_t;

#endif  /* #ifndef SVC_IF_SIGNAL_H */
