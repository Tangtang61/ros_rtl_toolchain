/*  $NetBSD: unistd.h,v 1.88 2001/07/29 22:18:45 wiz Exp $  */

/*-
 * Copyright (c) 1998, 1999 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Klaus Klein.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copyright (c) 1991, 1993, 1994
 *  The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *  This product includes software developed by the University of
 *  California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *  @(#)unistd.h    8.12 (Berkeley) 4/27/95
 */

/*
   Copyright(C) 2019 eSOL Co., Ltd.
   Modified to work with eMCOS.
*/

#ifndef _UNISTD_H_
#define _UNISTD_H_

#include <machine/ansi.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/unistd.h>


/*
 * IEEE Std 1003.1-90
 */
#define STDIN_FILENO    0   /* standard input file descriptor */
#define STDOUT_FILENO   1   /* standard output file descriptor */
#define STDERR_FILENO   2   /* standard error file descriptor */

#include <sys/null.h>
#include <sys/stat.h>

__BEGIN_DECLS
void _exit (int) __attribute__((__noreturn__));
int  access (const char *, int);
unsigned int alarm (unsigned int);
int  chdir (const char *);
int  chown (const char *, uid_t, gid_t);
int  close (int);
size_t   confstr (int, char *, size_t);
#ifndef __CUSERID_DECLARED
#define __CUSERID_DECLARED
/* also declared in stdio.h */
char    *cuserid (char *); /* obsolete */
#endif /* __CUSERID_DECLARED */
int  dup (int);
int  dup2 (int, int);
int  dup3 (int, int, int);
int  execl (const char *, const char *, ...);
int  execle (const char *, const char *, ...);
int  execlp (const char *, const char *, ...);
int  execlpe (const char *, const char *, ...); /* Non-standard*/
int  execv (const char *, char * const *);
int  execve (const char *, char * const *, char * const *);
int  execvp (const char *, char * const *);
int  execvpe (const char *, char * const *, char * const *); /* Non-standard*/
pid_t    fork (void);
long     fpathconf (int, int);
char    *getcwd (char *, size_t);
gid_t    getegid (void);
uid_t    geteuid (void);
gid_t    getgid (void);
int  getgroups (int, gid_t []);
__aconst char *getlogin (void);
pid_t    getpgrp (void);
pid_t    getpid (void);
pid_t    getppid (void);
uid_t    getuid (void);
int  isatty (int);
int  link (const char *, const char *);
long     pathconf (const char *, int);
int  pause (void);
int  pipe (int *);
int  pipe2 (int *, int);
ssize_t  read (int, void *, size_t);
int  rmdir (const char *);
int  setgid (gid_t);
int  setpgid (pid_t, pid_t);
pid_t    setsid (void);
int  setuid (uid_t);
unsigned int     sleep (unsigned int);
long     sysconf (int);
pid_t    tcgetpgrp (int);
int  tcsetpgrp (int, pid_t);
__aconst char *ttyname (int);
int  unlink (const char *);
ssize_t  write (int, const void *, size_t);

extern char **environ;

int     _close(int __fildes );
pid_t   _fork(void );
pid_t   _getpid(void );
int     _link(const char *__path1, const char *__path2 );
off_t   _lseek(int __fildes, off_t __offset, int __whence );
void *  _sbrk(intptr_t increment);
int     _unlink(const char *__path );
int     _execve(const char *__path, char * const __argv[], char * const __envp[] );

/*
 * IEEE Std 1003.2-92, adopted in X/Open Portability Guide Issue 4 and later
 */
#if (!defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)) || \
    (_POSIX_C_SOURCE - 0) >= 2 || (_XOPEN_SOURCE - 0) >= 4
int  getopt (int, char * const [], const char *);

extern   char *optarg;          /* getopt(3) external variables */
extern   int opterr;
extern   int optind;
extern   int optopt;
#endif


/*
 * The following three syscalls are also defined in <sys/types.h>
 * We protect them against double declarations.
 */
#ifndef __OFF_T_SYSCALLS_DECLARED
#define __OFF_T_SYSCALLS_DECLARED
off_t    lseek (int, off_t, int);
int  truncate (const char *, off_t);
/*
 * IEEE Std 1003.1b-93,
 * also found in X/Open Portability Guide >= Issue 4 Verion 2
 */
#if (!defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)) || \
    (_POSIX_C_SOURCE - 0) >= 199309L || \
    (defined(_XOPEN_SOURCE) && defined(_XOPEN_SOURCE_EXTENDED)) || \
    (_XOPEN_SOURCE - 0) >= 500
int  ftruncate (int, off_t);
#endif
#endif /* __OFF_T_SYSCALLS_DECLARED */


/*
 * IEEE Std 1003.1b-93, adopted in X/Open CAE Specification Issue 5 Version 2
 */
#if (!defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)) || \
    (_POSIX_C_SOURCE - 0) >= 199309L || (_XOPEN_SOURCE - 0) >= 500
int  fdatasync (int);
int  fsync (int);
#endif


/*
 * X/Open Portability Guide, all issues
 */
#if !defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE)
int  chroot (const char *);
int  nice (int);
#endif


/*
 * X/Open Portability Guide <= Issue 3
 */
#if defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE - 0) <= 3
int  rename (const char *, const char *) __RENAME(__posix_rename);
#endif


/*
 * X/Open Portability Guide >= Issue 4
 */
#if (!defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)) || \
    (_XOPEN_SOURCE - 0) >= 4
__aconst char *crypt (const char *, const char *);
int  encrypt (char *, int);
char    *getpass (const char *);
pid_t    getsid (pid_t);
#endif


/*
 * X/Open Portability Guide >= Issue 4 Version 2
 */
#if (!defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)) || \
    (defined(_XOPEN_SOURCE) && defined(_XOPEN_SOURCE_EXTENDED)) || \
    (_XOPEN_SOURCE - 0) >= 500

#define F_ULOCK     0
#define F_LOCK      1
#define F_TLOCK     2
#define F_TEST      3

int  brk (void *);
int  fchdir (int);
int  fchown (int, uid_t, gid_t);
int  getdtablesize (void);
long     gethostid (void);
int  gethostname (char *, size_t);
__attribute__((__pure__)) int getpagesize (void);       /* legacy */
pid_t getpgid (pid_t);
int  lchown (const char *, uid_t, gid_t);

int  lockf (int, int, off_t);
int  readlink (const char *, char *, size_t);
void    *sbrk (intptr_t);
/* XXX prototype wrong! */
int setpgrp(void);
int getresuid(uid_t *ruid, uid_t *euid, uid_t *suid);
int setresuid(uid_t ruid, uid_t euid, uid_t suid);
int getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid);
int setresgid(gid_t rgid, gid_t egid, gid_t sgid);
int  setregid (gid_t, gid_t);
int  setreuid (uid_t, uid_t);
void     swab (const void *, void *, ssize_t);
int  symlink (const char *, const char *);
void     sync (void);
useconds_t ualarm (useconds_t, useconds_t);
int  usleep (useconds_t);
#ifdef __LIBC12_SOURCE__
pid_t    vfork (void);
pid_t    __vfork14 (void);
#else
pid_t    vfork (void)          __RENAME(__vfork14);
#endif

#ifndef __AUDIT__
char    *getwd (char *);           /* obsoleted by getcwd() */
#endif

/*
 * select() needs struct timeval, but it is defines in sys/time.h, and unistd.h
 * does not include it, so this forward declaration is needed.
 */
#if __STDC__
struct timeval;             /* select(2) XXX */
#endif
#ifdef _LIBCSTD
int  select (int, fd_set *, fd_set *, fd_set *, struct timeval *);
#endif /* #ifdef _LIBCSTD */
#endif /* (!defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)) || ... */


/*
 * X/Open CAE Specification Issue 5 Version 2
 */
#if (!defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)) || \
    (_XOPEN_SOURCE - 0) >= 500
ssize_t  pread (int, void *, size_t, off_t);
ssize_t  pwrite (int, const void *, size_t, off_t);
#endif


/*
 * Implementation-defined extensions
 */
int  acct (const char *);
int  des_cipher (const char *, char *, long, int);
int  des_setkey (const char *);
void     endusershell (void);
int  exect (const char *, char * const *, char * const *);
int  fchroot (int);
int  getdomainname (char *, size_t);
int  getgrouplist (const char *, gid_t, gid_t *, int *);
mode_t   getmode (const void *, mode_t);
int  getsubopt (char **, char * const *, char **);
__aconst char *getusershell (void);
int  initgroups (const char *, gid_t);
int  iruserok (u_int32_t, int, const char *, const char *);
int      issetugid (void);
int  nfssvc (int, void *);
int  profil (char *, size_t, u_long, u_int);
#ifndef __PSIGNAL_DECLARED
#define __PSIGNAL_DECLARED
/* also in signal.h */
void    psignal (unsigned int, const char *);
#endif /* __PSIGNAL_DECLARED */
int  rcmd (char **, int, const char *,
        const char *, const char *, int *);
int  reboot (int, char *);
int  revoke (const char *);
int  rresvport (int *);
int  ruserok (const char *, int, const char *, const char *);
int  setdomainname (const char *, size_t);
int  setegid (gid_t);
int  seteuid (uid_t);
int  setgroups (int, const gid_t *);
int  sethostid (long);
int  sethostname (const char *, size_t);
int  setlogin (const char *);
void    *setmode (const char *);
int  setrgid (gid_t);
int  setruid (uid_t);
void     setusershell (void);
void     strmode (mode_t, char *);
__aconst char *strsignal (int);
int  swapctl (int, const void *, int);
int  swapon (const char *);        /* obsoleted by swapctl() */
int  syscall (int, ...);
#ifndef __HITACHI_VERSION__ /* Hew does not support 64bit integer */
/* quad_t    __syscall (quad_t, ...); */
#endif  /* __HITACHI_VERSION__ */
int  undelete (const char *);

#if 1 /*INET6*/
int  rcmd_af (char **, int, const char *,
        const char *, const char *, int *, int);
int  rresvport_af (int *, int);
int  iruserok_sa (const void *, int, int, const char *, const char *);
#endif

extern   int optreset;      /* getopt(3) external variable */
extern   char *suboptarg;   /* getsubopt(3) external variable */

__END_DECLS

#endif /* !_UNISTD_H_ */
