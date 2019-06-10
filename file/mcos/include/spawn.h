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
 spawn.h   POSIX Layer   Process spawn definitions
============================================================================*/
#ifndef __SPAWN_H__
#define __SPAWN_H__

#ifdef  __cplusplus
extern  "C" {
#endif

#if !defined COMPILER_RESTRICT
#if defined __cplusplus
#define COMPILER_RESTRICT
#else /* __cplusplus */
#define COMPILER_RESTRICT restrict
#endif /* __cplusplus */
#endif /* COMPILER_RESTRICT */

#include <sys/types.h>
#include <signal.h>
#include <sched.h>

/* Spawn attributes flags */
#define POSIX_SPAWN_RESETIDS        1
#define POSIX_SPAWN_SETPGROUP       2
#define POSIX_SPAWN_SETSCHEDPARAM   4
#define POSIX_SPAWN_SETSCHEDULER    8
#define POSIX_SPAWN_SETSIGDEF      16
#define POSIX_SPAWN_SETSIGMASK     32
 /* Non-standard */
#define POSIX_SPAWN_SETSYSTEM_NP   64
#define POSIX_SPAWN_SETDEBUG_NP   128

typedef struct posix_spawn_file_actions
{
    int      actions_count;
    void*    actions_data;
} posix_spawn_file_actions_t;

typedef struct posix_spawnattr
{
    unsigned short spawn_flags;
    unsigned char  spawn_priority;
    unsigned char  spawn_scheduler;
    pid_t          spawn_groupid;
    sigset_t       spawn_sigmask;
    sigset_t       spawn_sigdefault;
    int            spawn_lcid;
} posix_spawnattr_t;

/* Prototypes */
int   posix_spawn(pid_t *COMPILER_RESTRICT, const char *COMPILER_RESTRICT,
          const posix_spawn_file_actions_t *,
          const posix_spawnattr_t *COMPILER_RESTRICT, char *const *COMPILER_RESTRICT,
          char *const *COMPILER_RESTRICT);
int   posix_spawn_file_actions_addclose(posix_spawn_file_actions_t *,
          int);
int   posix_spawn_file_actions_adddup2(posix_spawn_file_actions_t *,
          int, int);
int   posix_spawn_file_actions_addopen(posix_spawn_file_actions_t *COMPILER_RESTRICT,
          int, const char *COMPILER_RESTRICT, int, mode_t);
int   posix_spawn_file_actions_destroy(posix_spawn_file_actions_t *);
int   posix_spawn_file_actions_init(posix_spawn_file_actions_t *);
int   posix_spawnattr_destroy(posix_spawnattr_t *);
int   posix_spawnattr_getsigdefault(const posix_spawnattr_t *COMPILER_RESTRICT,
          sigset_t *COMPILER_RESTRICT);
int   posix_spawnattr_getflags(const posix_spawnattr_t *COMPILER_RESTRICT,
          short *COMPILER_RESTRICT);
int   posix_spawnattr_getpgroup(const posix_spawnattr_t *COMPILER_RESTRICT,
          pid_t *COMPILER_RESTRICT);
int   posix_spawnattr_getschedparam(const posix_spawnattr_t *COMPILER_RESTRICT,
          struct sched_param *COMPILER_RESTRICT);
int   posix_spawnattr_getschedpolicy(const posix_spawnattr_t *COMPILER_RESTRICT,
          int *COMPILER_RESTRICT);
int   posix_spawnattr_getsigmask(const posix_spawnattr_t *COMPILER_RESTRICT,
          sigset_t *COMPILER_RESTRICT);
int   posix_spawnattr_init(posix_spawnattr_t *);
int   posix_spawnattr_setsigdefault(posix_spawnattr_t *COMPILER_RESTRICT,
          const sigset_t *COMPILER_RESTRICT);
int   posix_spawnattr_setflags(posix_spawnattr_t *, short);
int   posix_spawnattr_setpgroup(posix_spawnattr_t *, pid_t);
int   posix_spawnattr_setschedparam(posix_spawnattr_t *COMPILER_RESTRICT,
          const struct sched_param *COMPILER_RESTRICT);
int   posix_spawnattr_setschedpolicy(posix_spawnattr_t *, int);

int   posix_spawnattr_setsigmask(posix_spawnattr_t *COMPILER_RESTRICT,
          const sigset_t *COMPILER_RESTRICT);
int   posix_spawnp(pid_t *COMPILER_RESTRICT, const char *COMPILER_RESTRICT,
          const posix_spawn_file_actions_t *,
          const posix_spawnattr_t *COMPILER_RESTRICT,
          char *const *COMPILER_RESTRICT, char *const *COMPILER_RESTRICT);

int posix_spawnattr_setlcid_np(posix_spawnattr_t *COMPILER_RESTRICT attr, int lcid);
int posix_spawnattr_getlcid_np(const posix_spawnattr_t *COMPILER_RESTRICT attr,
          int *COMPILER_RESTRICT lcid);

#ifdef  __cplusplus
}
#endif

#endif /* __SPAWN_H__ */
