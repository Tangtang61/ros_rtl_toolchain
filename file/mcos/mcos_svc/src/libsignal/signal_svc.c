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
[signal_svc.c] - SVC interface library (POSIX Signal)
****************************************************************************/

#include <pt_api_impl.h>
#include <svc/svc_if.h>
#include <svc/svc_if_signal.h>

void* pt_signal_get(siginfo_t *info, sigset_t *rest)
{
    svc_packet_signal_pt_signal_get_t   p;
    void*   hdl;

    p.id        = SVCID_SIGNAL_PT_SIGNAL_GET;
    p.info      = info;
    p.rest      = rest;
    p.hdl       = &hdl;

    (void)call_svc((void*)&p);
    return *p.hdl;
}

void* _pt_handle_interrupt(pttcb_t *pttcb, siginfo_t *info, sigset_t *mask)
{
    svc_packet_pt_handle_interrupt_t p;
    void*   hdl;

    p.id    = SVCID_PT_HANDLE_INTERRUPT;
    p.pttcb = pttcb;
    p.info  = info;
    p.mask  = mask;
    p.hdl   = &hdl;

    (void)call_svc((void*)&p);
    return *p.hdl;
}

/* pthread_kill() API */
int pthread_kill(pthread_t thread, int sig)
{
    svc_packet_signal_pthread_kill_t    p;

    p.id        = SVCID_SIGNAL_PTHREAD_KILL;
    p.thread    = thread;
    p.sig       = sig;

    return (int)call_svc((void*)&p);
}

int pthread_sigmask(int how, const sigset_t *restrict set, sigset_t *restrict old)
{
    svc_packet_signal_pthread_sigmask_t p;

    p.id        = SVCID_SIGNAL_PTHREAD_SIGMASK;
    p.how       = how;
    p.set       = set;
    p.old       = old;

    return (int)call_svc((void*)&p);
}

int sigaction(int signo, const struct sigaction *restrict act, struct sigaction *restrict old)
{
    svc_packet_signal_sigaction_t   p;

    p.id        = SVCID_SIGNAL_SIGACTION;
    p.signo     = signo;
    p.act       = act;
    p.old       = old;

    return (int)call_svc((void*)&p);
}


int sigwait(const sigset_t* restrict set, int* restrict sig)
{
    svc_packet_signal_sigwait_t p;

    p.id        = SVCID_SIGNAL_SIGWAIT;
    p.set       = set;
    p.sig       = sig;

    return (int)call_svc((void*)&p);
}

int sigtimedwait(const sigset_t* restrict set, siginfo_t* restrict info, const struct timespec *restrict timeout)
{
    svc_packet_signal_sigtimedwait_t    p;

    p.id        = SVCID_SIGNAL_SIGTIMEDWAIT;
    p.set       = set;
    p.info      = info;
    p.timeout   = timeout;

    return (int)call_svc((void*)&p);
}

int sigpending(sigset_t* set)
{
    svc_packet_signal_sigpending_t  p;

    p.id        = SVCID_SIGNAL_SIGPENDING;
    p.set       = set;

    return (int)call_svc((void*)&p);
}

int sigsuspend(const sigset_t* sigmask)
{
    svc_packet_signal_sigsuspend_t  p;

    p.id        = SVCID_SIGNAL_SIGSUSPEND;
    p.sigmask   = sigmask;

    return (int)call_svc((void*)&p);
}

int sigqueue(pid_t pid, int signo, union sigval value)
{
    svc_packet_signal_sigqueue_t  p;

    p.id        = SVCID_SIGNAL_SIGQUEUE;
    p.pid       = pid;
    p.signo     = signo;
    p.value     = value;

    return (int)call_svc((void*)&p);
}
