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
 libposix_local.h - POSIX library local interfaces
============================================================================*/
#ifndef __LIBPOSIX_LOCAL_H__
#define __LIBPOSIX_LOCAL_H__

#include <pthread.h>
#include <signal.h>
#include <dirent.h>
#include <stdarg.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#ifndef MCOS
#include <posix_internal.h>
#else
#include <stdlib.h>
#include <posix/process.cfg>
#endif

#ifdef  __cplusplus
extern  "C" {
#endif

/*
 * pthread_cond_wait/timedwait internal structure
 */
struct cond_wait_clup
{
    pthread_cond_t*     cond;
    pthread_mutex_t*    mutex;
};
typedef struct cond_wait_clup cond_wait_clup_t;

/*
 * libposix initializer/finalizer
 */
extern int _libposix_init(void);
extern int _libposix_fini(void);
extern int libposix_reset(void);
extern void posix_libc_mutex_initialize(void);
extern void posix_libc_mutex_finalize(void);
extern void posix_libc_mutex_reset(void);
extern void posix_libc_rwlock_initialize(void);
extern void posix_libc_rwlock_finalize(void);
extern void posix_libc_rwlock_reset(void);

/*
 * Internal system calls and functions
 */
extern int _pthread_barrier_wait(unsigned int* user, int pshared, int options, unsigned int val);
extern int _pthread_cond_wait(unsigned int* user, int pshared, int options, unsigned int val);
extern int _pthread_cond_timedwait(unsigned int* restrict user, int pshared, int options,
                                   unsigned int val, int realtime,
                                   const struct timespec* restrict abstmo);
extern int _pthread_cond_signal(unsigned int* restrict user, int pshared, int options,
                                unsigned int* restrict other);
extern int _pthread_cond_broadcast(unsigned int* restrict user, int pshared, int options,
                                   unsigned int* restrict other);
extern int _pthread_mutex_lock(unsigned int* user, int pshared, int options, unsigned int val);
extern int _pthread_mutex_timedlock(unsigned int* restrict user, int pshared, int options,
                                    unsigned int val, int realtime,
                                    const struct timespec* restrict abstmo);
extern int _pthread_mutex_unlock(unsigned int* restrict user, int pshared, int options,
                                 unsigned int* restrict other);
extern int _pthread_rwlock_rdlock(unsigned int* user, int pshared, int options, unsigned int val);
extern int _pthread_rwlock_wrlock(unsigned int* user, int pshared, int options, unsigned int val);
extern int _pthread_rwlock_timedrdlock(unsigned int* restrict user, int pshared, int options,
                                       unsigned int val, int realtime,
                                       const struct timespec* restrict abstmo);
extern int _pthread_rwlock_timedwrlock(unsigned int* restrict user, int pshared, int options,
                                       unsigned int val, int realtime,
                                       const struct timespec* restrict abstmo);
extern int _pthread_rwlock_unlock(unsigned int* restrict user, int pshared, int options,
                                  unsigned int* restrict other);
extern int _sem_post(unsigned int* restrict user, int pshared, int options,
                     unsigned int* restrict other);
extern int _sem_timedwait(unsigned int* restrict user, int pshared, int options,
                          unsigned int val, int realtime, const struct timespec* restrict abstmo);
extern int _sem_wait(unsigned int* user, int pshared, int options, unsigned int val);
extern int _sigsuspend(const sigset_t* set);
extern int _sigwait(const sigset_t *restrict set, int *restrict sig);
extern struct dirent* __readdir(DIR* dir, struct dirent* ent);
extern int _select(int nfds, fd_set* restrict rfds, fd_set* restrict wfds,
                   fd_set* restrict efds, const struct timespec* restrict spec);
extern pthread_t       __pthread_self(void);
#ifndef MCOS
extern pthread_user_t* _posix_pthread_user(void);
extern pthread_user_t* __posix_pthread_user(void);
extern proc_user_t*    _posix_proc_user(void);
extern pthread_user_t* _pthread_user(proc_user_t* proc);
#endif
extern int*   __posix_tsd(void);
extern void** _posix_get_key_area(pthread_key_t key);
extern unsigned int _posix_thread_get_thrd_param(void);
extern void         _posix_thread_set_thrd_param(unsigned int param);
extern void _pthread_exit(void* sta);
extern void _posix_proc_exit(int sta);
extern int _posix_system_context(void);
extern int _posix_check_context_space(unsigned int *addr);
extern int _posix_check_execfile_access(const char * file);
extern int _posix_check_execfile1(const char* file);
extern int _posix_check_execfile2(const char* file);
extern int _posix_check_execfile3(const char* file, char** path, int sh);
extern char* _posix_get_shell_path(void);
extern void  _posix_rel_shell_path(char* shell);
extern int libposix_check_addr_private(unsigned int addr);
extern int posix_malloc_selector(void);
extern int posix_malloc_get_config_granularity(void);
extern int posix_malloc_get_config_mmap_threshold(void);
extern int posix_malloc_get_config_trim_threshold(void);
extern pid_t __fork(void);
extern pid_t _fork(void);
extern int _exec(const char* path, char* const argv[], char* const envp[]);
extern int _ioctl(int fildes, int request, void* arg);
extern int _pthread_getattr_np(pthread_t thread, pthread_attr_t *restrict attr);

/*
 * Misc
 */
extern char **environ;

extern void __localtime_ini(void) __attribute__ ((weak));
extern void __localtime_fini(void) __attribute__ ((weak));

extern void posix_dlmalloc_reset(void) __attribute__ ((weak));

#ifdef  __cplusplus
}
#endif

#endif /* #ifndef __LIBPOSIX_LOCAL_H__ */
