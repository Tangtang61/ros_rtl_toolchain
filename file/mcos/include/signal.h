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
 signal.h   POSIX Layer  Signal definitions
============================================================================*/
#ifndef __signal_h
#define __signal_h

#ifndef __SIGNAL_H__
/*
 * NOTE : Other middleware uses __SIGNAL_H__ macro to check
 *        whether its own errno definition should be used or not.
 */
#define __SIGNAL_H__
#endif  /* #ifndef __SIGNAL_H__ */

#if !defined COMPILER_RESTRICT
#if defined __cplusplus
#define COMPILER_RESTRICT
#else /* __cplusplus */
#define COMPILER_RESTRICT restrict
#endif /* __cplusplus */
#endif /* COMPILER_RESTRICT */

#include <sys/cdefs.h>
#include <sys/types.h>

#ifndef __SIGNAL_DECLS
#define __SIGNAL_DECLS
__BEGIN_DECLS
/* Signal numbers */
#if defined (__ghs__)
#define SIGINT      2
#define SIGILL      4
#define SIGABRT     6
#define SIGFPE      8
#define SIGSEGV     11
#define SIGTERM     15

/* standard bsd signals in addition to these */
#define SIGHUP      1
/* SIGINT */
#define SIGQUIT     3
/* SIGILL */
#define SIGTRAP     5
#define SIGIOT      SIGABRT
#define SIGEMT      7
/* SIGFPE */
#define SIGKILL     9
#define SIGBUS      10
/* SIGSEGV */
#define SIGSYS      12
#define SIGPIPE     13
#define SIGALRM     14
/* SIGTERM */
#define SIGURG      17
#define SIGSTOP     18
#define SIGTSTP     19
#define SIGCONT     20
#define SIGCHLD     21
#define SIGCLD      SIGCHLD
#define SIGTTIN     22
#define SIGTTOU     23
#define SIGIO       24
#define SIGXCPU     25
#define SIGXTIM     26
#define SIGXFSZ     27
#define SIGVTALRM   28
#define SIGPROF     29
#define SIGWINCH    30
#define SIGUSR1     31
#define SIGUSR2     32

/* POSIX only flags */
#define SIGPOLL    SIGIO      /* Pollable event (XSI) */
#define SIGRTMIN   34         /* Minimal realtime signal */
#define SIGRTMAX   35         /* Maximal realtime signal */

#else
#define SIGABRT     1         /* Process abort signal */
#define SIGALRM     2         /* Alarm clock */
#define SIGBUS      3         /* Access to an undefined portion of a memory object */
#define SIGCHLD     4         /* Child process terminated, stopped or continued */
#define SIGCONT     5         /* Continue executing, if stopped */
#define SIGFPE      6         /* Erroneous arithmetic operation */
#define SIGHUP      7         /* Hangup */
#define SIGILL      8         /* Illegal instruction */
#define SIGKILL     9         /* Kill (cannot be caught or ignored)*/
#define SIGINT     10         /* Terminal interrupt signal */
#define SIGPIPE    11         /* Write on a pipe with no one to read it */
#define SIGQUIT    12         /* Terminal quit signal */
#define SIGSEGV    13         /* Invalid memory reference */
#define SIGSTOP    14         /* Stop executing (cannot be caught or ignored)*/
#define SIGTERM    15         /* Termination signal */
#define SIGTSTP    16         /* Terminal stop signal */
#define SIGTTIN    17         /* Background process attempting read */
#define SIGTTOU    18         /* Background process attempting write */
#define SIGUSR1    19         /* User-defined signal 1 */
#define SIGUSR2    20         /* User-defined signal 2 */
#define SIGPOLL    21         /* Pollable event (XSI) */
#define SIGSYS     22         /* Bad system call */
#define SIGTRAP    23         /* Trace/breakpoint trap */
#define SIGURG     24         /* High bandwidth data is available at a socket */
#define SIGRTMIN   25         /* Minimal realtime signal */
#define SIGRTMAX   32         /* Maximal realtime signal */

/* These are actually not supported but are defined (POSIX requirement) */
#define SIGPROF    33         /* Profiling timer expired */
#define SIGVTALRM  34         /* Virtual timer expired (XSI) */
#define SIGXCPU    35         /* CPU time limit exceeded */
#define SIGXFSZ    36         /* File size limit exceeded */

#endif

/* Special signal handler values */
#define SIG_DFL   (void (*)(int))0
#define SIG_IGN   (void (*)(int))1
#define SIG_HOLD  (void (*)(int))2
#define SIG_ERR   (void (*)(int))-1

/* 64-bit SIG_ATOMIC_T is sufficient for most architectures */
typedef unsigned long long SIG_ATOMIC_T;
/* Types */
__BEGIN_NAMESPACE_STD
typedef SIG_ATOMIC_T sig_atomic_t;  /* Architecture-dependent */
__END_NAMESPACE_STD

typedef unsigned int sigset_t;      /* 32 signals */

/* Signal value */
union sigval
{
    int    sival_int;                               /* Integer signal value */
    void  *sival_ptr;                               /* Pointer signal value */
};

/* Signal info */
typedef struct siginfo
{
    int           si_signo;                         /* Signal number */
    int           si_code;                          /* Signal code */
    union
    {
        union sigval si_value;                      /* Signal value */

	struct
        {
	    pid_t si_pid;
	    uid_t si_uid;
        } _kill;

        void *si_addr;
        long si_band;
    } _sifields;

} siginfo_t;

# define si_value	_sifields.si_value
# define si_pid		_sifields._kill.si_pid
# define si_uid		_sifields._kill.si_uid
# define si_addr	_sifields.si_addr
# define si_band	_sifields.si_band

/* Signal mask operations */
#define SIG_UNBLOCK   0   /* Unblock specified signals */
#define SIG_BLOCK     1   /* Block specified signals */
#define SIG_SETMASK   2   /* Set signal mask directly */

/* Signal action */
struct sigaction
{
    union sa_action
    {
        void (*sa_hdl)(int);                       /* Signal handler */
        void (*sa_act)(int, siginfo_t *, void *);  /* Signal action */
    } sa_action;
    int      sa_flags;        /* Special flags */
    sigset_t sa_mask;         /* Set of signals to be blocked during signal handler */
};
#define sa_handler    sa_action.sa_hdl
#define sa_sigaction  sa_action.sa_act

/* Signal action flags */
#define SA_SIGINFO    0x001  /* Queued signal extended information */
#define SA_NOCLDSTOP  0x002  /* Do not generate SIGCHLD when children stop or continue */

/* These are XSI extensions */
#define SA_NOCLDWAIT  0x004  /* Do not create zombies for dead children */
#define SA_RESETHAND  0x008  /* Causes handler to become SIG_DFL */
#define SA_NODEFER    0x010  /* Do not block signal at handler entry */
#define SA_RESTART    0x020  /* Causes EINTR not to be returned (unsupported) */
#define SA_ONSTACK    0x040  /* Alternate stack for handler (unsupported) */

/* Signal code values */
#define SI_USER     0        /* Signal sent by kill() or pthread_kill() */
#define SI_QUEUE    1        /* Signal sent by the sigqueue() */
#define SI_TIMER    2        /* Signal generated by expiration of a timer */
#define SI_ASYNCIO  3        /* Signal generated by completion of an asynchronous I/O */
#define SI_MESGQ    4        /* Arrival of a message on an empty message queue */

/* Signal event */
struct sigevent
{
    int                 sigev_notify;               /* Notification type        */
    int                 sigev_signo;                /* Signal number            */
    union sigval        sigev_value;                /* Signal value             */
    void  (*sigev_notify_function)(union sigval);   /* Notification function    */
    pthread_attr_t *    sigev_notify_attributes;    /* Notification attributes  */
};

/* Notification types */
#define SIGEV_NONE    0   /* No asynchronous notification */
#define SIGEV_SIGNAL  1   /* Normal signal delivery */
#define SIGEV_THREAD  2   /* Thread-based notification */

enum
{
    ILL_ILLOPC = 1,
    ILL_ILLOPN,
    ILL_ILLADR,
    ILL_ILLTRP,
    ILL_PRVOPC,
    ILL_PRVREG,
    ILL_COPROC,
    ILL_BADSTK
};

enum
{
    FPE_INTDIV = 1,
    FPE_INTOVF,
    FPE_FLTDIV,
    FPE_FLTOVF,
    FPE_FLTUND,
    FPE_FLTRES,
    FPE_FLTINV,
    FPE_FLTSUB
};

enum
{
    SEGV_MAPERR = 1,
    SEGV_ACCERR
};

enum
{
    BUS_ADRALN = 1,
    BUS_ADRERR,
    BUS_OBJERR,
    BUS_MCEERR_AR,
    BUS_MCEERR_AO
};

enum
{
    POLL_IN = 1,
    POLL_OUT,
    POLL_MSG,
    POLL_ERR,
    POLL_PRI,
    POLL_HUP
};

#define SS_ONSTACK      1
#define SS_DISABLE      2
#define MINSIGSTKSZ     5120
#define SIGSTKSZ        16384

typedef struct st_sigaltstack
{
    void *ss_sp;
    int ss_flags;
    size_t ss_size;
} stack_t;

extern int sigaltstack(const stack_t *COMPILER_RESTRICT, stack_t *COMPILER_RESTRICT);

#include <time.h>

/* Prototypes */
__BEGIN_NAMESPACE_STD
int    raise(int);
void (*signal(int, void (*)(int)))(int);
__END_NAMESPACE_STD
int    kill(pid_t, int);
int    killpg(pid_t, int);
int    pthread_kill(pthread_t, int);
int    pthread_sigmask(int, const sigset_t *COMPILER_RESTRICT, sigset_t *COMPILER_RESTRICT);
int    sigaction(int, const struct sigaction *COMPILER_RESTRICT, struct sigaction *COMPILER_RESTRICT);

int    sigaddset(sigset_t *, int);
int    sigdelset(sigset_t *, int);
int    sigemptyset(sigset_t *);
int    sigfillset(sigset_t *);
int    sigismember(const sigset_t *, int);

int    sigpending(sigset_t *);
int    sigprocmask(int, const sigset_t *COMPILER_RESTRICT, sigset_t *COMPILER_RESTRICT);

int    sigqueue(pid_t, int, const union sigval);
int    sigsuspend(const sigset_t *);

int    sigtimedwait(const sigset_t *COMPILER_RESTRICT, siginfo_t *COMPILER_RESTRICT, const struct timespec *COMPILER_RESTRICT);
int    sigwait(const sigset_t *COMPILER_RESTRICT, int *COMPILER_RESTRICT);
int    sigwaitinfo(const sigset_t *COMPILER_RESTRICT, siginfo_t *COMPILER_RESTRICT);

int    sighold(int);
int    sigignore(int);
int    sigpause(int);
int    sigrelse(int);
int    siginterrupt(int, int);
void (*sigset(int, void (*)(int)))(int);
__END_DECLS
#endif /* __SIGNAL_DECLS */

#ifndef __SIGNAL_NO_EXPORTS  /* defined in ARM RVCT <csignal> */
__USING_NAMESPACE_STD(sig_atomic_t)
__USING_NAMESPACE_STD(raise)
__USING_NAMESPACE_STD(signal)
#endif  /* #ifndef __SIGNAL_NO_EXPORTS */

#endif /* __signal_h */
