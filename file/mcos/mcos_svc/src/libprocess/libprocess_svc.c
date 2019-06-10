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
[libprocess_svc.c] - SVC interface library (Process)
****************************************************************************/

#include <svc/svc_if.h>
#include <svc/svc_if_process.h>

int posix_init_main(int flags, void *params)
{
    svc_packet_process_posix_init_main_t    p;

    p.id        = SVCID_PROCESS_POSIX_INIT_MAIN;
    p.flags     = flags;
    p.params    = params;
    return (int)call_svc((void*)&p);
}

int posix_spawn(
    pid_t * restrict pid,
    const char * restrict path,
    const posix_spawn_file_actions_t * acts,
    const posix_spawnattr_t * restrict attr,
    char * const * restrict argv,
    char * const * restrict envp)
{
    svc_packet_process_posix_spawn_t    p;

    p.id    = SVCID_PROCESS_POSIX_SPAWN;
    p.pid   = pid;
    p.path  = path;
    p.acts  = acts;
    p.attr  = attr;
    p.argv  = argv;
    p.envp  = envp;
    return (int)call_svc((void*)&p);
}

void _exit(int status)
{
    svc_packet_process_exit_t   p;

    p.id    = SVCID_PROCESS_EXIT;
    p.status= status;
    (void)call_svc((void*)&p);
}

void _Exit(int status)
{
    _exit(status);
}

pid_t waitpid(pid_t pid, int *stat_loc, int options)
{
    svc_packet_process_waitpid_t    p;
    pid_t   rpid;

    p.id        = SVCID_PROCESS_WAITPID;
    p.pid       = pid;
    p.stat_loc  = stat_loc;
    p.options   = options;
    p.rpid      = &rpid;
    (void)call_svc((void*)&p);
    return *p.rpid;
}

pid_t _getpid(void)
{
    svc_packet_process_getpid_t p;
    pid_t   pid;

    p.id    = SVCID_PROCESS_GETPID;
    p.pid   = &pid;
    (void)call_svc((void*)&p);
    return *p.pid;
}

pid_t getppid(void)
{
    svc_packet_process_getppid_t    p;
    pid_t   ppid;

    p.id    = SVCID_PROCESS_GETPPID;
    p.ppid  = &ppid;
    (void)call_svc((void*)&p);
    return *p.ppid;
}

pid_t getpgid(pid_t pid)
{
    svc_packet_process_getpgid_t    p;
    pid_t   pgid;

    p.id    = SVCID_PROCESS_GETPGID;
    p.pid   = pid;
    p.pgid  = &pgid;
    (void)call_svc((void*)&p);
    return *p.pgid;
}

int setpgid(pid_t pid, pid_t pgid)
{
    svc_packet_process_setpgid_t    p;

    p.id    = SVCID_PROCESS_SETPGID;
    p.pid   = pid;
    p.pgid  = pgid;
    return call_svc((void*)&p);
}

gid_t getgid(void)
{
    svc_packet_process_getgid_t p;
    gid_t   gid;

    p.id    = SVCID_PROCESS_GETGID;
    p.gid   = &gid;
    (void)call_svc((void*)&p);
    return *p.gid;
}

int setgid(gid_t gid)
{
    svc_packet_process_setgid_t p;

    p.id    = SVCID_PROCESS_SETGID;
    p.gid   = gid;
    return call_svc((void*)&p);
}

int setegid(gid_t egid)
{
    svc_packet_process_setegid_t    p;

    p.id    = SVCID_PROCESS_SETEGID;
    p.egid  = egid;
    return call_svc((void*)&p);
}

int setregid(gid_t rgid, gid_t egid)
{
    svc_packet_process_setregid_t   p;

    p.id    = SVCID_PROCESS_SETREGID;
    p.rgid  = rgid;
    p.egid  = egid;
    return call_svc((void*)&p);
}

int getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid)
{
    svc_packet_process_getresgid_t  p;

    p.id    = SVCID_PROCESS_GETRESGID;
    p.rgid  = rgid;
    p.egid  = egid;
    p.sgid  = sgid;
    return call_svc((void*)&p);
}

int setresgid(gid_t rgid, gid_t egid, gid_t sgid)
{
    svc_packet_process_setresgid_t  p;

    p.id    = SVCID_PROCESS_SETRESGID;
    p.rgid  = rgid;
    p.egid  = egid;
    p.sgid  = sgid;
    return call_svc((void*)&p);
}

uid_t getuid(void)
{
    svc_packet_process_getuid_t p;
    uid_t   uid;

    p.id    = SVCID_PROCESS_GETUID;
    p.uid   = &uid;
    (void)call_svc((void*)&p);
    return *p.uid;
}

int setuid(uid_t uid)
{
    svc_packet_process_setuid_t p;

    p.id    = SVCID_PROCESS_SETUID;
    p.uid   = uid;
    return call_svc((void*)&p);
}

int seteuid(uid_t euid)
{
    svc_packet_process_seteuid_t    p;

    p.id    = SVCID_PROCESS_SETEUID;
    p.euid  = euid;
    return call_svc((void*)&p);
}

int setreuid(uid_t ruid, uid_t euid)
{
    svc_packet_process_setreuid_t   p;

    p.id    = SVCID_PROCESS_SETREUID;
    p.ruid  = ruid;
    p.euid  = euid;
    return call_svc((void*)&p);
}

int getresuid(uid_t *ruid, uid_t *euid, uid_t *suid)
{
    svc_packet_process_getresuid_t  p;

    p.id    = SVCID_PROCESS_GETRESUID;
    p.ruid  = ruid;
    p.euid  = euid;
    p.suid  = suid;
    return call_svc((void*)&p);
}

int setresuid(uid_t ruid, uid_t euid, uid_t suid)
{
    svc_packet_process_setresuid_t  p;

    p.id    = SVCID_PROCESS_SETRESUID;
    p.ruid  = ruid;
    p.euid  = euid;
    p.suid  = suid;
    return call_svc((void*)&p);
}

int kill(pid_t pid, int sig)
{
    svc_packet_process_kill_t   p;

    p.id    = SVCID_PROCESS_KILL;
    p.pid   = pid;
    p.sig   = sig;
    return call_svc((void*)&p);
}

int _exec(const char* path, char* const argv[], char* const envp[])
{
    svc_packet_process_exec_t p;

    p.id = SVCID_PROCESS_EXEC;
    p.path = path;
    p.argv = argv;
    p.envp = envp;
    return call_svc((void*)&p);
}
