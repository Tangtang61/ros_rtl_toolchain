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
[launch_proc_main.c]
****************************************************************************/

#include <stdlib.h>
#include <unistd.h>
#include <svc/svc_if_process.h>

extern int main(int argc, char **argv, char **envp);
extern void _libc_rec_lock_init_run(void);
extern char **environ;

extern int pt_init_signal_entry(void);
extern void  pt_signal_entry(void);
extern void* pt_process_thread_entry(void *arg);
extern void* aio_worker_thread_entry(void *arg);

struct message
{
    int m_type;
    int m_size;
    char m_body[32];
};

typedef struct message message_t;

signed int launch_proc_main(message_t * msg)
{
    signed int  ret;
    int         argc;
    int         envc;
    intptr_t    offs;
    char**      argv;
    char**      envp;
    intptr_t *   offp;
    int         flags;
    const init_main_params_t  params = {
        POSIX_INIT_MAIN_IMPL_VER,
        pt_signal_entry,
        pt_process_thread_entry,
        aio_worker_thread_entry,
    };

    argc = 0;
    argv = (char**)&msg->m_body;
    offp = (intptr_t*)&msg->m_body;
    while ((offs = *offp++) != 0) {
        argv[argc++] = (char*)msg + offs;
    }
    argv[argc] = 0;

    envc = 0;
    envp = argv + argc + 1;
    while ((offs = *offp++) != 0) {
        envp[envc++] = (char*)msg + offs;
    }
    envp[envc] = 0;
    environ = envp;

    pt_init_signal_entry();

    flags  = ((POSIX_INIT_MAIN_KIND_POST & POSIX_INIT_MAIN_KIND_MASK) 
                << POSIX_INIT_MAIN_KIND_SHIFT);
    flags |= ((sizeof(params) & POSIX_INIT_MAIN_SIZE_MASK) 
                << POSIX_INIT_MAIN_SIZE_SHIFT);
    posix_init_main(flags, (void*)&params);
    _libc_rec_lock_init_run();

    ret = main(argc, argv, envp);
    return ret;
}
