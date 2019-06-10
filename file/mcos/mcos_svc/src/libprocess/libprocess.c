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
[libprocess.c] - Process related library function
****************************************************************************/
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <pt_api_impl.h>
#include <stdio.h>

int killpg(pid_t grp, int sig)
{
    return kill(-grp, sig);
}

pid_t wait(int *stat_loc)
{
    return waitpid((pid_t)-1, stat_loc, 0);
}

pid_t getpid(void)
{
    pid_t       pid;
    pttcb_t*    pttcb;

    pttcb = pt_get_pttcb();
    if (pttcb != 0)
    {
        pid = pttcb->pid;
    }
    else
    {
        extern pid_t _getpid(void);
        pid = _getpid();
    }
    return pid;
}

pid_t getpgrp(void)
{
    return getpgid(0);
}

int setpgrp(void)
{
    return setpgid(0, 0);
}

gid_t getegid(void)
{
    gid_t rgid;
    gid_t egid;
    gid_t sgid;
    int   res;

    res = getresgid(&rgid, &egid, &sgid);
    if (res != 0)
    {
        return (gid_t)res;
    }
    else
    {
        return egid;
    }
}

uid_t geteuid(void)
{
    uid_t ruid;
    uid_t euid;
    uid_t suid;
    int   res;

    res = getresuid(&ruid, &euid, &suid);
    if (res != 0)
    {
        return (uid_t)res;
    }
    else
    {
        return euid;
    }
}

pid_t setsid (void)
{
    printf("setsid(): eMCOS does not support this POSIX API.\n");
    return -1;
}
