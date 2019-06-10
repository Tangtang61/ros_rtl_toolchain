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
 posix_spawnp.c   POSIX Layer   Process spawn by path library function
============================================================================*/
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <spawn.h>
#include <unistd.h>
#include <sys/stat.h>
#include "libposix_local.h"

#define MALLOC_GLOBAL   /* Avoid replacing malloc() with "global_malloc()". */
#include <pt_api_impl.h>
#define PTHREAD_PRIO_MAX    (MCOS_CFG_PT_MAX_PRI)
#define PTHREAD_PRIO_MIN    (MCOS_CFG_PT_MIN_PRI)

/* Helper to validate spawn attributes */
static int posix_spawnattr_valid(const posix_spawnattr_t *attr)
{
    return (1
#ifdef MCOS_CFG_PT_CHECK_ARGUMENTS
            && (attr != 0)
            && (CHECK_ALIGN(attr, sizeof(attr->spawn_sigmask)) == 0)
#endif
    );
}

int posix_spawnattr_init(posix_spawnattr_t *attr)
{
    if (posix_spawnattr_valid((const posix_spawnattr_t*)attr))
    {
        attr->spawn_flags     = 0;
        attr->spawn_priority  = (PTHREAD_PRIO_MAX - PTHREAD_PRIO_MIN + 1) / 2;
        attr->spawn_scheduler = SCHED_FIFO;
        attr->spawn_groupid   = getpgid(0);
        (void)sigemptyset(&attr->spawn_sigmask);
        (void)sigemptyset(&attr->spawn_sigdefault);
        attr->spawn_lcid = MCOS_LCID_INHERIT/*posix_sysinfo[POSIX_SYSINFO_DEFAULT_LCID]*/;
        return 0;
    }
    return EINVAL;
}

int posix_spawnattr_destroy(posix_spawnattr_t* attr)
{
    if (posix_spawnattr_valid((const posix_spawnattr_t*)attr))
    {
        memset(attr, 0, sizeof(*attr));
        return 0;
    }
    return EINVAL;
}

int posix_spawnattr_getflags(const posix_spawnattr_t *restrict attr, short *restrict flags)
{
    if (posix_spawnattr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (flags != 0)
        && (CHECK_ALIGN(flags, sizeof(*flags)) == 0)
#endif
    )
    {
        *flags = (short)attr->spawn_flags;
        return 0;
    }
    return EINVAL;
}

int posix_spawnattr_setflags(posix_spawnattr_t *attr, short flags)
{
    if (posix_spawnattr_valid(attr)
        && ((flags
             & ~(  POSIX_SPAWN_RESETIDS
                 | POSIX_SPAWN_SETPGROUP
                 | POSIX_SPAWN_SETSCHEDPARAM
                 | POSIX_SPAWN_SETSCHEDULER
                 | POSIX_SPAWN_SETSIGDEF
                 | POSIX_SPAWN_SETSIGMASK/*
                 | POSIX_SPAWN_SETSYSTEM_NP*/
                 | POSIX_SPAWN_SETDEBUG_NP)) == 0))
    {
        attr->spawn_flags = flags;
        return 0;
    }
    return EINVAL;
}

int posix_spawnattr_getschedpolicy(const posix_spawnattr_t *restrict attr, int *restrict policy)
{
    if (posix_spawnattr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (policy!= 0)
        && (CHECK_ALIGN(policy, sizeof(*policy)) == 0)
#endif
    )
    {
        *policy = attr->spawn_scheduler;
        return 0;
    }
    return EINVAL;
}

int posix_spawnattr_setschedpolicy(posix_spawnattr_t* attr, int policy)
{
    if (posix_spawnattr_valid(attr)
        && (   (policy == SCHED_FIFO)
            || (policy == SCHED_RR)
            || (policy == SCHED_SPORADIC)
            || (policy == SCHED_OTHER) ))
    {
        if (policy == SCHED_SPORADIC)
        {
            return ENOTSUP;
        }
        attr->spawn_scheduler = (unsigned char)policy;
        return 0;
    }
    return EINVAL;
}

int posix_spawnattr_getschedparam(const posix_spawnattr_t *restrict attr, struct sched_param *restrict param)
{
    if (posix_spawnattr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (param != 0)
        && (CHECK_ALIGN(param, sizeof(param->sched_priority)) == 0)
#endif
    )
    {
        param->sched_priority = attr->spawn_priority;
        return 0;
    }
    return EINVAL;
}

int posix_spawnattr_setschedparam(posix_spawnattr_t *restrict attr, const struct sched_param *restrict param)
{
    if (posix_spawnattr_valid(attr)
        && (param != 0)
        && (CHECK_ALIGN(param, sizeof(param->sched_priority)) == 0)
        && (param->sched_priority >= PTHREAD_PRIO_MIN)
        && (param->sched_priority <= PTHREAD_PRIO_MAX))
    {
        attr->spawn_priority = (unsigned char)param->sched_priority;
        return 0;
    }
    return EINVAL;
}

int posix_spawnattr_getlcid_np(const posix_spawnattr_t *restrict attr, int *restrict lcid)
{
    if (posix_spawnattr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (lcid != 0)
        && (CHECK_ALIGN(lcid, sizeof(*lcid)) == 0)
#endif
    )
    {
        *lcid = attr->spawn_lcid;
        return 0;
    }
    return EINVAL;
}

extern mcos_bool_t mcos_is_validlcid(const mcos_id_t lcid);
int posix_spawnattr_setlcid_np(posix_spawnattr_t *restrict attr, int lcid)
{
    if (posix_spawnattr_valid(attr)
        && (   (lcid == MCOS_LCID_ANY)
            || (lcid == MCOS_LCID_SELF)
            || (lcid == MCOS_LCID_INHERIT)
            || mcos_is_validlcid(lcid)))
    {
        attr->spawn_lcid = lcid;
        return 0;
    }
    return EINVAL;
}

int posix_spawnattr_getpgroup(const posix_spawnattr_t *restrict attr, pid_t *restrict grid)
{
    if (posix_spawnattr_valid(attr)
#ifdef MCOS_CFG_PT_CHECK_ARGUMENTS
        && (grid != 0)
        && (CHECK_ALIGN(grid, sizeof(*grid)) == 0)
#endif
    )
    {
        *grid = attr->spawn_groupid;
        return 0;
    }
    return EINVAL;
}

int posix_spawnattr_setpgroup(posix_spawnattr_t* attr, pid_t grid)
{
#define PROC_IDENT_MAX          0xffff
    if (posix_spawnattr_valid(attr)
        && (grid <= PROC_IDENT_MAX))
    {
        attr->spawn_groupid = grid;
        return 0;
    }
    return EINVAL;
}

int posix_spawnattr_getsigmask(const posix_spawnattr_t *restrict attr, sigset_t *restrict mask)
{
    if (posix_spawnattr_valid(attr)
#ifdef MCOS_CFG_PT_CHECK_ARGUMENTS
        && (mask != 0)
        && (CHECK_ALIGN(mask, sizeof(*mask)) == 0)
#endif
    )
    {
        *mask = attr->spawn_sigmask;
        return 0;
    }
    return EINVAL;
}

int posix_spawnattr_setsigmask(posix_spawnattr_t *restrict attr, const sigset_t *restrict mask)
{
    if (posix_spawnattr_valid(attr)
        && (mask != 0)
        && (CHECK_ALIGN(mask, sizeof(*mask)) == 0)
        && ((*mask & ((1 << (SIGKILL - 1)) | (1 << (SIGSTOP - 1)))) == 0))
    {
        attr->spawn_sigmask = *mask;
        return 0;
    }
    return EINVAL;
}

int posix_spawnattr_getsigdefault(const posix_spawnattr_t *restrict attr, sigset_t *restrict mask)
{
    if (posix_spawnattr_valid(attr)
#ifdef MCOS_CFG_PT_CHECK_ARGUMENTS
        && (mask != 0)
        && (CHECK_ALIGN(mask, sizeof(*mask)) == 0)
#endif
    )
    {
        *mask = attr->spawn_sigdefault;
        return 0;
    }
    return EINVAL;
}

int posix_spawnattr_setsigdefault(posix_spawnattr_t *restrict attr, const sigset_t *restrict mask)
{
    if (posix_spawnattr_valid(attr)
        && (mask != 0)
        && (CHECK_ALIGN(mask, sizeof(*mask)) == 0))
    {
        attr->spawn_sigdefault = *mask;
        return 0;
    }
    return EINVAL;
}

/* Check executable file-1
 * (length of file path)    */
int _posix_check_execfile1(const char* file)
{
    int     sta;
    size_t  slen;

    sta = EINVAL;
    if (file != 0)
    {
        sta = ENOENT;
        slen = strlen(file);
        if (slen != 0)
        {
            sta = ENAMETOOLONG;
            if (slen < PATH_MAX)
            {
                sta = 0;
            }
        }
    }
    return sta;
}

// TODO! check file format & permissions
int _posix_check_execfile_access(const char* file)
{
    struct stat buf;
    int ret = stat(file, &buf);
    if (ret == 0)
    {
        if (!S_ISREG(buf.st_mode))
        {
            ret = EACCES;
        }
    }
    else
    {
        ret = errno;
    }
    return ret;
}


/* Check executable file-2
 * (whether file exists, has a permission, has a recognized format) */
int _posix_check_execfile2(const char* file)
{
    return _posix_check_execfile_access(file);
}

/* Check executable file-3
 * (search for executable file,
 *  if file path is solved by "PATH", "*path" will be updated) */
int _posix_check_execfile3(const char* file, char** path, int sh)
{
    int     sta;
    int     lenv;
    int     lcom;
    int     lfil;
    char*   env;
    char*   penv;
    char*   name;
    char*   temp;
    char*   comp;
    char*   save;

 /* Will check PATH env if file name has no slash */
    if (    (strchr(file, '/') == 0)
         && ((env = getenv("PATH")) != 0) )
    {
     /* Allocate buffers */
        sta = ENOMEM;
        name = (char*)malloc(PATH_MAX);
        if (name != 0)
        {
            lenv = strlen(env) + 1;
            penv = (char*)malloc(lenv);
            if (penv != 0)
            {
             /* Traverse PATH components */
                lfil = strlen(file);
                temp = (char*)memcpy(penv, env, lenv);
                while ((comp = strtok_r(temp, ":", &save)) != 0)
                {
                    temp = 0;
                    lcom = strlen(comp);
                    if ((lcom + lfil + 2) <= PATH_MAX)
                    {
                     /* Compose pathname */
                        memcpy(name, comp, lcom);
                        while (name[lcom - 1] == '/')
                        {
                            lcom -= 1;
                        }
                        name[lcom] = '/';
                        memcpy(name + lcom + 1, file, lfil + 1);
                     /* Check if file exists and its format */
                        sta = _posix_check_execfile_access(name);
                        if (    (sta == 0)
                             || ((sh != 0) && (sta == ENOEXEC)) )
                        {
                         /* If recognized executable file is found or
                          * need to invoke command interpreter, stop search */
                            *path = name;
                            name = 0;
                            break;
                        }
                        else if (sta == EINVAL)
                        {
                         /* This means unrecognized executable (Non-ELF) */
                            break;
                        }
                        else
                        {
                            /* Retry */;
                        }
                    }
                }
             /* Any executable file is not found */
                if (comp == 0)
                {
                    sta = ENOENT;
                }
                free(penv);
            }
         /* Release name buffer upon error */
            if (name != 0)
            {
                free(name);
            }
        }
    }
    else
    {
     /* Check if file exists and its format */
        sta = _posix_check_execfile_access(file);
    }

    return sta;
}

/* Get path name of command interpreter (sh utility) */
char* _posix_get_shell_path(void)
{
    int     sta;
    char*   env;
    size_t  lenv;
    char*   shell;

    shell = (char*)malloc(PATH_MAX);
    if (shell != 0)
    {
        sta = EACCES;
        env = getenv("SHELL");
        if (env != NULL)
        {
            sta = ENAMETOOLONG;
            lenv = strlen(env);
            if (lenv < PATH_MAX)
            {
             /* Assume only a single interpreter is set */
                (void)memcpy(shell, env, (lenv + 1));
                sta = 0;
            }
        }
     /* Release buffer upon error */
        if (sta != 0)
        {
            free(shell);
            shell = 0;
        }
    }

    return shell;
}

/* Release path name of command interpreter */
void _posix_rel_shell_path(char* shell)
{
    if (shell != 0)
    {
        free(shell);
    }
}

/* posix_spawnp() service */
int posix_spawnp(pid_t *restrict prid, const char *restrict file,
                 const posix_spawn_file_actions_t *acts,
                 const posix_spawnattr_t *restrict attr,
                 char *const argv[restrict], char * const envp[restrict])
{
    int     sta;
    char*   path;

    {
        sta = _posix_check_execfile1(file);
        if (sta == 0)
        {
            path = (char*)file;
            sta = _posix_check_execfile3(file, &path, 0);
            if (sta == 0)
            {
                sta = posix_spawn(prid, path, acts, attr, argv, envp);
            }
            if (path != file)
            {
                free(path);
            }
        }
    }

    return sta;
}
