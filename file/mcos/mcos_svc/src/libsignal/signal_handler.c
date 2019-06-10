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
[signal_handler.c] - Functions for asynchronous signal
****************************************************************************/

#include <signal.h>
#include <pt_api_impl.h>
#include <posix_atomic.h>
#include <svc/svc_if_signal.h>

/* Synchronous signal entry */
void pt_handle_interrupt(pttcb_t* pttcb)
{
    void            (*hdl)(int, struct siginfo*, void*);
    sigset_t        mask;
    struct siginfo  info;
    int             loop;

    loop = 1;
    while (loop != 0)
    {
        hdl = (void (*)(int, struct siginfo*, void*))_pt_handle_interrupt(pttcb, &info, &mask);
        if (hdl != 0)
        {
         /* Disable additional signals */
            sigset_t sigenab = pttcb->sigenab;
            posix_atomic_and(&pttcb->sigenab, mask);
            (*hdl)(info.si_signo, &info, 0);
            pttcb->sigenab = sigenab;
        }
        else
        {
            loop = 0;
        }
    }
    return;
}

/* Asynchronous signal entry
 * to call the handler written in high-level language */
void* pt_signal_handler(void)
{
    void            *ret;
    pttcb_t         *pttcb;
    void            (*hdl)(int, struct siginfo*, void*);
    sigset_t        set;
    struct siginfo  info;
    int             loop;

    set = 0;
    loop = 1;
    while (loop != 0)
    {
        hdl = (void (*)(int, struct siginfo*, void*))pt_signal_get(&info, &set);
        if (hdl != 0)
        {
            (*hdl)(info.si_signo, &info, 0);
        }
        else
        {
            loop = 0;
        }
    }

#if MCOS_USE_PROCESS_MODEL
    /* Return interrupted address for continuation */
    pttcb = pt_get_pttcb();
    if (pttcb != NULL)
    {
        ret = pttcb->saventry;
        pttcb->saventry = 0;
    }
    else
#endif  /* #if MCOS_USE_PROCESS_MODEL */
    {
        ret = 0;
    }
    return ret;
}

static int pt_set_signal_entry(void* entry)
{
    int     sta;
#if MCOS_USE_PROCESS_MODEL
    pttcb_t *pttcb;

    pttcb = pt_get_pttcb();
    if (pttcb != NULL)
    {
        pttcb->sigentry = entry;
        sta = 0;
    }
    else
#endif  /* #if MCOS_USE_PROCESS_MODEL */
    {
        sta = -1;
    }
    return sta;
}

/* Install signal handler entry */
int pt_init_signal_entry(void)
{
    return pt_set_signal_entry((void*)pt_signal_entry);
}
