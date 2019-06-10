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

/*============================================================================
 fork.c     POSIX Layer Process fork library function
============================================================================*/
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include "libposix_local.h"


/* External function */
extern int _init_liblock(void);

/* Compile-time max atfork handlers value */
#define ATFORK_MAX  32

static pthread_mutex_t atfork_mutex = PTHREAD_MUTEX_INITIALIZER;
static int  atfork_count;
static void (*prepare_handler[ATFORK_MAX])(void);
static void (*parent_handler[ATFORK_MAX])(void);
static void (*child_handler[ATFORK_MAX])(void);

/* pthread_atfork() service */
int pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void))
{
    int     idx;
    int     sta = ENOMEM;

    (void)pthread_mutex_lock(&atfork_mutex);
    if ((idx = atfork_count) < ATFORK_MAX)
    {
        prepare_handler[idx] = prepare;
        parent_handler[idx]  = parent;
        child_handler[idx]   = child;
        atfork_count = idx + 1;
        sta = 0;
    }
    (void)pthread_mutex_unlock(&atfork_mutex);
    return sta;
}

/* fork() service */
pid_t fork(void)
{
    pid_t   pid;
    int     idx;
    int     cnt = atfork_count;

 /* Prepare handlers are executed in back order */
    for (idx = cnt-1; idx >= 0; idx--)
    {
        if (prepare_handler[idx] != NULL)
        {
            (*prepare_handler[idx])();
        }
    }
 /* Fork the process */
    pid = __fork();
 /* Negative return means error */
    if (pid >= 0)
    {
        if (pid != 0)
        {
         /* Parent executes parent handlers after fork */
            for (idx = 0; idx < cnt; idx++)
            {
                if (parent_handler[idx] != NULL)
                {
                    (*parent_handler[idx])();
                }
            }
        }
        else
        {
         /* Create new TKSE library locks for child (MLOCK()/LockDL()) */
            if (_init_liblock() < 0)
            {
                exit(0xff);
            }

         /* Install signal handler entry */
            extern int pt_init_signal_entry(void);
            pt_init_signal_entry();

         /* Child executes child handlers after fork */
            for (idx = 0; idx < cnt; idx++)
            {
                if (child_handler[idx] != NULL)
                {
                    (*child_handler[idx])();
                }
            }
        }
    }
    return pid;
}

pid_t vfork()
{
    return fork();
}
