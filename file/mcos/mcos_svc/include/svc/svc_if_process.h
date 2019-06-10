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
[svc_if_process.h] - SVC interface library header
****************************************************************************/

#ifndef SVC_IF_PROCESS_H
#define SVC_IF_PROCESS_H

#include <svc/svc_if.h>

/*
 * SVC Function ID
 */
#define SVCID_PROCESS_POSIX_INIT_MAIN   (SVCID_PROCESS | 0x00000000)    /* posix_init_main()*/
#define SVCID_PROCESS_POSIX_SPAWN       (SVCID_PROCESS | 0x00000001)    /* posix_spawn()    */
#define SVCID_PROCESS_EXIT              (SVCID_PROCESS | 0x00000002)    /* _exit()          */
#define SVCID_PROCESS_WAITPID           (SVCID_PROCESS | 0x00000003)    /* waitpid()        */
#define SVCID_PROCESS_GETPID            (SVCID_PROCESS | 0x00000004)    /* getpid()         */
#define SVCID_PROCESS_GETPPID           (SVCID_PROCESS | 0x00000005)    /* getppid()        */
#define SVCID_PROCESS_GETPGID           (SVCID_PROCESS | 0x00000006)    /* getpgid()        */
#define SVCID_PROCESS_SETPGID           (SVCID_PROCESS | 0x00000007)    /* setpgid()        */
#define SVCID_PROCESS_GETGID            (SVCID_PROCESS | 0x00000008)    /* getgid()         */
#define SVCID_PROCESS_SETGID            (SVCID_PROCESS | 0x00000009)    /* setgid()         */
#define SVCID_PROCESS_SETEGID           (SVCID_PROCESS | 0x0000000a)    /* setegid()        */
#define SVCID_PROCESS_SETREGID          (SVCID_PROCESS | 0x0000000b)    /* setregid()       */
#define SVCID_PROCESS_GETRESGID         (SVCID_PROCESS | 0x0000000c)    /* getresgid()      */
#define SVCID_PROCESS_SETRESGID         (SVCID_PROCESS | 0x0000000d)    /* setresgid()      */
#define SVCID_PROCESS_GETUID            (SVCID_PROCESS | 0x0000000e)    /* getuid()         */
#define SVCID_PROCESS_SETUID            (SVCID_PROCESS | 0x0000000f)    /* setuid()         */
#define SVCID_PROCESS_SETEUID           (SVCID_PROCESS | 0x00000010)    /* seteuid()        */
#define SVCID_PROCESS_SETREUID          (SVCID_PROCESS | 0x00000011)    /* setreuid()       */
#define SVCID_PROCESS_GETRESUID         (SVCID_PROCESS | 0x00000012)    /* getresuid()      */
#define SVCID_PROCESS_SETRESUID         (SVCID_PROCESS | 0x00000013)    /* setresuid()      */
#define SVCID_PROCESS_KILL              (SVCID_PROCESS | 0x00000014)    /* kill()           */
#define SVCID_PROCESS_FORK              (SVCID_PROCESS | 0x00000015)    /* fork()           */
#define SVCID_PROCESS_EXEC              (SVCID_PROCESS | 0x00000016)    /* exec()           */

#ifndef _in_asm_source_
/*
 * SVC Parameter Packet
 */
#include <spawn.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>

/* posix_init_main() */
typedef struct {
    int         id;
    int         flags;
    const void  *params;
} svc_packet_process_posix_init_main_t;

/* Bitfield posix_init_main() flags
 * kind      :  1    0:pre-initialize/1:post-initialize
 * reserved  :  15   (for future use)
 * version   :  8
 * size      :  8    length of parameters
 */
#define POSIX_INIT_MAIN_KIND_MASK   0x01
#define POSIX_INIT_MAIN_KIND_SHIFT  31
#define  POSIX_INIT_MAIN_KIND_PRE   0
#define  POSIX_INIT_MAIN_KIND_POST  1
#define POSIX_INIT_MAIN_SIZE_MASK   0xff
#define POSIX_INIT_MAIN_SIZE_SHIFT  0

/* Implementation version */
#define POSIX_INIT_MAIN_IMPL_VER    0U

/* Parameters structure */
typedef struct posix_init_main_params init_main_params_t;
struct posix_init_main_params
{
    uintptr_t implver;          /* Implementation version   */
    void  (*signalent)(void);   /* Signal handler entry     */
    void* (*threadent)(void*);  /* Common sub thread entry  */
    void* (*aiowoker)(void*);   /* AIO worker thread entry  */
};

extern int posix_init_main(int flags, void *params);

/* posix_spawn() */
typedef struct {
    int         id;
    pid_t                            * restrict pid;
    const char                       * restrict path;
    const posix_spawn_file_actions_t *acts;
    const posix_spawnattr_t          * restrict attr;
    char                             * const * restrict argv;
    char                             * const * restrict envp;
} svc_packet_process_posix_spawn_t;

/* _exit() */
typedef struct {
    int         id;
    int         status;
} svc_packet_process_exit_t;

/* waitpid() */
typedef struct {
    int         id;
    pid_t       pid;
    int         *stat_loc;
    int         options;
    pid_t       *rpid;
} svc_packet_process_waitpid_t;

/* getpid() */
typedef struct {
    int         id;
    pid_t       *pid;
} svc_packet_process_getpid_t;

/* getppid() */
typedef struct {
    int         id;
    pid_t       *ppid;
} svc_packet_process_getppid_t;

/* getpgid() */
typedef struct {
    int         id;
    pid_t       pid;
    pid_t       *pgid;
} svc_packet_process_getpgid_t;

/* setpgid() */
typedef struct {
    int         id;
    pid_t       pid;
    pid_t       pgid;
} svc_packet_process_setpgid_t;

/* getgid() */
typedef struct {
    int         id;
    gid_t       *gid;
} svc_packet_process_getgid_t;

/* setgid() */
typedef struct {
    int         id;
    gid_t       gid;
} svc_packet_process_setgid_t;

/* setegid() */
typedef struct {
    int         id;
    gid_t       egid;
} svc_packet_process_setegid_t;

/* setregid() */
typedef struct {
    int         id;
    gid_t       rgid;
    gid_t       egid;
} svc_packet_process_setregid_t;

/* getresgid() */
typedef struct {
    int         id;
    gid_t       *rgid;
    gid_t       *egid;
    gid_t       *sgid;
} svc_packet_process_getresgid_t;

/* setresgid() */
typedef struct {
    int         id;
    gid_t       rgid;
    gid_t       egid;
    gid_t       sgid;
} svc_packet_process_setresgid_t;

/* getuid() */
typedef struct {
    int         id;
    uid_t       *uid;
} svc_packet_process_getuid_t;

/* setuid() */
typedef struct {
    int         id;
    uid_t       uid;
} svc_packet_process_setuid_t;

/* seteuid() */
typedef struct {
    int         id;
    uid_t       euid;
} svc_packet_process_seteuid_t;

/* setreuid() */
typedef struct {
    int         id;
    uid_t       ruid;
    uid_t       euid;
} svc_packet_process_setreuid_t;

/* getresuid() */
typedef struct {
    int         id;
    uid_t       *ruid;
    uid_t       *euid;
    uid_t       *suid;
} svc_packet_process_getresuid_t;

/* setresuid() */
typedef struct {
    int         id;
    uid_t       ruid;
    uid_t       euid;
    uid_t       suid;
} svc_packet_process_setresuid_t;

/* kill() */
typedef struct {
    int         id;
    pid_t       pid;
    int         sig;
} svc_packet_process_kill_t;

/* fork() */
typedef struct {
    int             id;
    void*           retadr;
} svc_packet_process_fork_t;

/* exec() */
typedef struct {
    int             id;
    const char *    path;
    char* const*    argv;
    char* const*    envp;
} svc_packet_process_exec_t;

/* List of Process APIs */
typedef union {
    int         id;
    svc_packet_process_posix_init_main_t    param_process_posix_init_main_;
    svc_packet_process_posix_spawn_t        param_process_posix_spawn_;
    svc_packet_process_exit_t               param_process_exit_;
    svc_packet_process_waitpid_t            param_process_waitpid_;
    svc_packet_process_getpid_t             param_process_getpid_;
    svc_packet_process_getppid_t            param_process_getppid_;
    svc_packet_process_getpgid_t            param_process_getpgid_;
    svc_packet_process_setpgid_t            param_process_setpgid_;
    svc_packet_process_getgid_t             param_process_getgid_;
    svc_packet_process_setgid_t             param_process_setgid_;
    svc_packet_process_setegid_t            param_process_setegid_;
    svc_packet_process_setregid_t           param_process_setregid_;
    svc_packet_process_getresgid_t          param_process_getresgid_;
    svc_packet_process_setresgid_t          param_process_setresgid_;
    svc_packet_process_getuid_t             param_process_getuid_;
    svc_packet_process_setuid_t             param_process_setuid_;
    svc_packet_process_seteuid_t            param_process_seteuid_;
    svc_packet_process_setreuid_t           param_process_setreuid_;
    svc_packet_process_getresuid_t          param_process_getresuid_;
    svc_packet_process_setresuid_t          param_process_setresuid_;
    svc_packet_process_kill_t               param_process_kill_;
    svc_packet_process_fork_t               param_process_fork_;
    svc_packet_process_exec_t               param_process_exec_;
} svc_packet_process_t;

#endif /* #ifndef _in_asm_source_ */

#endif  /* #ifndef SVC_IF_PROCESS_H */
