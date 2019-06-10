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
 exec.c     POSIX Layer exec() series library function
============================================================================*/
#include <unistd.h>
#include <errno.h>
#include "libposix_local.h"
#include <stdlib.h>

/* execl() service */
int execl(const char *path, const char *arg0, ... /*, (char *)0 */)
{
    int         sta;
    int         acnt;
    va_list     list;
    char**      argv;

    /* Check length of file path */
    sta = _posix_check_execfile1(path);
    if (sta == 0)
    {
        /* Check if executable file exists */
        sta = _posix_check_execfile2(path);
        if (sta == 0)
        {
            sta = EINVAL;
            if (arg0 != NULL)
            {
                /* Count arguments */
                acnt = 1;
                va_start(list, arg0);
                while (va_arg(list, const char*) != NULL)
                {
                    acnt++;
                }
                va_end(list);

                /* Setup arguments */
                sta = ENOMEM;
                argv = (char**)malloc((acnt + 1) * sizeof(*argv));
                if (argv != NULL)
                {
                    va_start(list, arg0);
                    acnt = 0;
                    argv[acnt] = (char*)arg0;
                    while (argv[acnt++] != NULL)
                    {
                        argv[acnt] = (char*)va_arg(list, const char*);
                    }
                    va_end(list);

                    /* Call process creation routine
                     *  Note: Upon successful, exec() will not return, but
                     *        memory of "argv" will be freed within exec(). */
                    sta = _exec(path, argv, (char* const*)environ);
                    free(argv);
                }
            }
        }
    }

    if (sta != 0)
    {
        errno = sta;
        sta = -1;
    }

    return sta;
}

/* execle() service */
int execle(const char *path, const char *arg0, ... /*, (char *)0, char *const envp[]*/)
{
    int         sta;
    int         acnt;
    va_list     list;
    char**      argv;
    char* const*envp;

    /* Check length of file path */
    sta = _posix_check_execfile1(path);
    if (sta == 0)
    {
        /* Check if executable file exists */
        sta = _posix_check_execfile2(path);
        if (sta == 0)
        {
            sta = EINVAL;
            if (arg0 != NULL)
            {
                /* Count arguments */
                acnt = 1;
                va_start(list, arg0);
                while (va_arg(list, const char*) != NULL)
                {
                    acnt++;
                }
                va_end(list);

                /* Setup arguments */
                sta = ENOMEM;
                argv = (char**)malloc((acnt + 1) * sizeof(*argv));
                if (argv != NULL)
                {
                    va_start(list, arg0);
                    acnt = 0;
                    argv[acnt] = (char*)arg0;
                    while (argv[acnt++] != NULL)
                    {
                        argv[acnt] = (char*)va_arg(list, const char*);
                    }
                    envp = va_arg(list, char* const*);
                    va_end(list);

                    /* Call process creation routine
                     *  Note: Upon successful, exec() will not return, but
                     *        memory of "argv" will be freed within exec(). */
                    sta = _exec(path, argv, envp);
                    free(argv);
                }
            }
        }
    }

    if (sta != 0)
    {
        errno = sta;
        sta = -1;
    }

    return sta;
}

/* execlp() service */
int execlp(const char *file, const char *arg0, ... /*, (char *)0 */)
{
    int         sta;
    char*       path;
    char*       temp;
    int         acnt;
    va_list     list;
    char**      argv;

    /* Check length of file path */
    sta = _posix_check_execfile1(file);
    if (sta == 0)
    {
        /* Check if executable file exists
         * "PATH" (and "SHELL") may be used to parse file name.
         * If "ENOEXEC" is returned, it means invoking the sh utility. */
        temp = (char*)file;
        sta = _posix_check_execfile3(file, &temp, 1);
        if (    (sta == 0)
             || (sta == ENOEXEC) )
        {
            if (arg0 != NULL)
            {
                /* Get executable file path */
                if (sta == ENOEXEC)
                {
                    path = _posix_get_shell_path();
                }
                else
                {
                    path = temp;
                }

                /* Count arguments */
                acnt = 1;
                va_start(list, arg0);
                while (va_arg(list, const char*) != NULL)
                {
                    acnt++;
                }
                va_end(list);
                if (sta == ENOEXEC)
                {
                    acnt++;
                }

                /* Setup arguments */
                argv = (char**)malloc((acnt + 1) * sizeof(*argv));
                if (argv != NULL)
                {
                    va_start(list, arg0);
                    acnt = 0;
                    argv[acnt] = (char*)arg0;
                    if (sta == ENOEXEC)
                    {
                        /* Put file name as an argument for sh utility */
                        argv[++acnt] = temp;
                    }
                    while (argv[acnt++] != NULL)
                    {
                        argv[acnt] = (char*)va_arg(list, const char*);
                    }
                    va_end(list);

                    /* Call process creation routine
                     *  Note: Upon successful, exec() will not return, but
                     *        memory of "argv", "temp" will be freed within exec(). */
                    sta = _exec(path, argv, (char* const*)environ);
                    free(argv);
                }
                else
                {
                    sta = ENOMEM;
                }
                /* Cleanup buffers upon error */
                if (temp != path)
                {
                    _posix_rel_shell_path(path);
                }
            }
            else
            {
                sta = EINVAL;
            }
            /* Cleanup buffers upon error */
            if (temp != file)
            {
                free(temp);
            }
        }
    }

    if (sta != 0)
    {
        errno = sta;
        sta = -1;
    }

    return sta;
}

/* execlpe() service (Non-POSIX standard) */
int execlpe(const char *file, const char *arg0, ... /*, (char *)0, char *const envp[]*/)
{
    int         sta;
    char*       path;
    char*       temp;
    int         acnt;
    va_list     list;
    char**      argv;
    char* const*envp;

    /* Check length of file path */
    sta = _posix_check_execfile1(file);
    if (sta == 0)
    {
        /* Check if executable file exists
         * "PATH" (and "SHELL") may be used to parse file name.
         * If "ENOEXEC" is returned, it means invoking the sh utility. */
        temp = (char*)file;
        sta = _posix_check_execfile3(file, &temp, 1);
        if (    (sta == 0)
             || (sta == ENOEXEC) )
        {
            if (arg0 != NULL)
            {
                /* Get executable file path */
                if (sta == ENOEXEC)
                {
                    path = _posix_get_shell_path();
                }
                else
                {
                    path = temp;
                }

                /* Count arguments */
                acnt = 1;
                va_start(list, arg0);
                while (va_arg(list, const char*) != NULL)
                {
                    acnt++;
                }
                va_end(list);
                if (sta == ENOEXEC)
                {
                    acnt++;
                }

                /* Setup arguments */
                argv = (char**)malloc((acnt + 1) * sizeof(*argv));
                if (argv != NULL)
                {
                    va_start(list, arg0);
                    acnt = 0;
                    argv[acnt] = (char*)arg0;
                    if (sta == ENOEXEC)
                    {
                        /* Put file name as an argument for sh utility */
                        argv[++acnt] = temp;
                    }
                    while (argv[acnt++] != NULL)
                    {
                        argv[acnt] = (char*)va_arg(list, const char*);
                    }
                    envp = va_arg(list, char* const*);
                    va_end(list);

                    /* Call process creation routine
                     *  Note: Upon successful, exec() will not return, but
                     *        memory of "argv", "temp" will be freed within exec(). */
                    sta = _exec(path, argv, envp);
                    free(argv);
                }
                else
                {
                    sta = ENOMEM;
                }
                /* Cleanup buffers upon error */
                if (temp != path)
                {
                    _posix_rel_shell_path(path);
                }
            }
            else
            {
                sta = EINVAL;
            }
            /* Cleanup buffers upon error */
            if (temp != file)
            {
                free(temp);
            }
        }
    }

    if (sta != 0)
    {
        errno = sta;
        sta = -1;
    }

    return sta;
}

/* execv() service */
int execv(const char *path, char *const argv[])
{
    int         sta;

    /* Check length of file path */
    sta = _posix_check_execfile1(path);
    if (sta == 0)
    {
        /* Check if executable file exists */
        sta = _posix_check_execfile2(path);
        if (sta == 0)
        {
            /* Call process creation routine
             *  Note: Upon successful, exec() will not return */
            sta = _exec(path, argv, (char* const*)environ);
        }
    }

    if (sta != 0)
    {
        errno = sta;
        sta = -1;
    }

    return sta;
}

/* execve() service */
int execve(const char *path, char *const argv[], char *const envp[])
{
    int         sta;

    /* Check length of file path */
    sta = _posix_check_execfile1(path);
    if (sta == 0)
    {
        /* Check if executable file exists */
        sta = _posix_check_execfile2(path);
        if (sta == 0)
        {
            /* Call process creation routine
             *  Note: Upon successful, exec() will not return */
            sta = _exec(path, argv, envp);
        }
    }

    if (sta != 0)
    {
        errno = sta;
        sta = -1;
    }

    return sta;
}

/* execvp() service */
int execvp(const char *file, char *const argv[])
{
    int         sta;
    char*       path;
    char*       temp;
    int         acnt;
    char**      argv2;
    char* const* pargv;

    /* Check length of file path */
    sta = _posix_check_execfile1(file);
    if (sta == 0)
    {
        /* Check if executable file exists
         * "PATH" (and "SHELL") may be used to parse file name.
         * If "ENOEXEC" is returned, it means invoking the sh utility. */
        temp = (char*)file;
        sta = _posix_check_execfile3(file, &temp, 1);
        if (    (sta == 0)
             || (sta == ENOEXEC) )
        {
            /* Get executable file path */
            argv2 = NULL;
            if (sta == ENOEXEC)
            {
                path = _posix_get_shell_path();

                /* Count arguments */
                acnt = 0;
                while (argv[acnt] != NULL)
                {
                    acnt++;
                }

                /* Setup arguments */
                argv2 = (char**)malloc((acnt + 2) * sizeof(*argv2));
                if (argv2 != NULL)
                {
                    argv2[0] = argv[0];
                    argv2[1] = temp;
                    acnt = 1;
                    do {
                        argv2[acnt+1] = argv[acnt];
                    } while (argv2[acnt++] != NULL);
                }
                /* If fail to allocate memory, _exec() will return error */
                pargv = argv2;
            }
            else
            {
                path = temp;
                pargv = argv;
            }

            /* Call process creation routine
             *  Note: Upon successful, exec() will not return, but
             *        memory of "argv2", "temp" will be freed within exec(). */
            sta = _exec(path, pargv, (char* const*)environ);

            /* Cleanup buffers upon error */
            if (argv2 != NULL)
            {
                free(argv2);
            }
            if (temp != file)
            {
                free(temp);
            }
            if (temp != path)
            {
                _posix_rel_shell_path(path);
            }
        }
    }

    if (sta != 0)
    {
        errno = sta;
        sta = -1;
    }

    return sta;
}

/* execvpe() service (Non-POSIX standard) */
int execvpe(const char *file, char *const argv[], char *const envp[])
{
    int         sta;
    char*       path;
    char*       temp;
    int         acnt;
    char**      argv2;
    char* const* pargv;

    /* Check length of file path */
    sta = _posix_check_execfile1(file);
    if (sta == 0)
    {
        /* Check if executable file exists
         * "PATH" (and "SHELL") may be used to parse file name.
         * If "ENOEXEC" is returned, it means invoking the sh utility. */
        temp = (char*)file;
        sta = _posix_check_execfile3(file, &temp, 1);
        if (    (sta == 0)
             || (sta == ENOEXEC) )
        {
            /* Get executable file path */
            argv2 = NULL;
            if (sta == ENOEXEC)
            {
                path = _posix_get_shell_path();

                /* Count arguments */
                acnt = 0;
                while (argv[acnt] != NULL)
                {
                    acnt++;
                }

                /* Setup arguments */
                argv2 = (char**)malloc((acnt + 2) * sizeof(*argv2));
                if (argv2 != NULL)
                {
                    argv2[0] = argv[0];
                    argv2[1] = temp;
                    acnt = 1;
                    do {
                        argv2[acnt+1] = argv[acnt];
                    } while (argv2[acnt++] != NULL);
                }
                /* If fail to allocate memory, _exec() will return error */
                pargv = argv2;
            }
            else
            {
                path = temp;
                pargv = argv;
            }

            /* Call process creation routine
             *  Note: Upon successful, exec() will not return, but
             *        memory of "argv2", "temp" will be freed within exec(). */
            sta = _exec(path, pargv, envp);

            /* Cleanup buffers upon error */
            if (argv2 != NULL)
            {
                free(argv2);
            }
            if (temp != file)
            {
                free(temp);
            }
            if (temp != path)
            {
                _posix_rel_shell_path(path);
            }
        }
    }

    if (sta != 0)
    {
        errno = sta;
        sta = -1;
    }

    return sta;
}
