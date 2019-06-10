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
 sys/unistd.h
============================================================================*/

#ifndef __SYS_UNISTD_H__
#define __SYS_UNISTD_H__

#include <sys/features.h>

#ifdef  __cplusplus
extern  "C" {
#endif

/* access function */
#define F_OK        0   /* test for existence of file */
#define X_OK        0x01    /* test for execute or search permission */
#define W_OK        0x02    /* test for write permission */
#define R_OK        0x04    /* test for read permission */

/* whence values for lseek(2) */
#define SEEK_SET    0   /* set file offset to offset */
#define SEEK_CUR    1   /* set file offset to current plus offset */
#define SEEK_END    2   /* set file offset to EOF plus offset */

/* whence values for lseek(2); renamed by POSIX 1003.1 */
#define L_SET       SEEK_SET
#define L_INCR      SEEK_CUR
#define L_XTND      SEEK_END

/* configurable system variables */
#define _SC_AIO_LISTIO_MAX                  1
#define _SC_AIO_MAX                         2
#define _SC_AIO_PRIO_DELTA_MAX              3
#define _SC_ARG_MAX                         4
#define _SC_ATEXIT_MAX                      5
#define _SC_BC_BASE_MAX                     6
#define _SC_BC_DIM_MAX                      7
#define _SC_BC_SCALE_MAX                    8
#define _SC_BC_STRING_MAX                   9
#define _SC_CHILD_MAX                       10
#define _SC_CLK_TCK                         11
#define _SC_COLL_WEIGHTS_MAX                12
#define _SC_DELAYTIMER_MAX                  13
#define _SC_EXPR_NEST_MAX                   14
#define _SC_HOST_NAME_MAX                   15
#define _SC_IOV_MAX                         16
#define _SC_LINE_MAX                        17
#define _SC_LOGIN_NAME_MAX                  18
#define _SC_NGROUPS_MAX                     19
#define _SC_GETGR_R_SIZE_MAX                20
#define _SC_GETPW_R_SIZE_MAX                21
#define _SC_MQ_OPEN_MAX                     22
#define _SC_MQ_PRIO_MAX                     23
#define _SC_OPEN_MAX                        24
#define _SC_ADVISORY_INFO                   25
#define _SC_BARRIERS                        26
#define _SC_ASYNCHRONOUS_IO                 27
#define _SC_CLOCK_SELECTION                 28
#define _SC_CPUTIME                         29
#define _SC_FSYNC                           30
#define _SC_IPV6                            31
#define _SC_JOB_CONTROL                     32
#define _SC_MAPPED_FILES                    33
#define _SC_MEMLOCK                         34
#define _SC_MEMLOCK_RANGE                   35
#define _SC_MEMORY_PROTECTION               36
#define _SC_MESSAGE_PASSING                 37
#define _SC_MONOTONIC_CLOCK                 38
#define _SC_PRIORITIZED_IO                  39
#define _SC_PRIORITY_SCHEDULING             40
#define _SC_RAW_SOCKETS                     41
#define _SC_READER_WRITER_LOCKS             42
#define _SC_REALTIME_SIGNALS                43
#define _SC_REGEXP                          44
#define _SC_SAVED_IDS                       45
#define _SC_SEMAPHORES                      46
#define _SC_SHARED_MEMORY_OBJECTS           47
#define _SC_SHELL                           48
#define _SC_SPAWN                           49
#define _SC_SPIN_LOCKS                      50
#define _SC_SPORADIC_SERVER                 51
#define _SC_SS_REPL_MAX                     52
#define _SC_SYNCHRONIZED_IO                 53
#define _SC_THREAD_ATTR_STACKADDR           54
#define _SC_THREAD_ATTR_STACKSIZE           55
#define _SC_THREAD_CPUTIME                  56
#define _SC_THREAD_PRIO_INHERIT             57
#define _SC_THREAD_PRIO_PROTECT             58
#define _SC_THREAD_PRIORITY_SCHEDULING      59
#define _SC_THREAD_PROCESS_SHARED           60
#define _SC_THREAD_ROBUST_PRIO_INHERIT      61
#define _SC_THREAD_ROBUST_PRIO_PROTECT      62
#define _SC_THREAD_SAFE_FUNCTIONS           63
#define _SC_THREAD_SPORADIC_SERVER          64
#define _SC_THREADS                         65
#define _SC_TIMEOUTS                        66
#define _SC_TIMERS                          67
#define _SC_TRACE                           68
#define _SC_TRACE_EVENT_FILTER              69
#define _SC_TRACE_EVENT_NAME_MAX            70
#define _SC_TRACE_INHERIT                   71
#define _SC_TRACE_LOG                       72
#define _SC_TRACE_NAME_MAX                  73
#define _SC_TRACE_SYS_MAX                   74
#define _SC_TRACE_USER_EVENT_MAX            75
#define _SC_TYPED_MEMORY_OBJECTS            76
#define _SC_VERSION                         77
#define _SC_V6_ILP32_OFF32                  78
#define _SC_V6_ILP32_OFFBIG                 79
#define _SC_V6_LP64_OFF64                   80
#define _SC_V6_LPBIG_OFFBIG                 81
#define _SC_2_C_BIND                        82
#define _SC_2_C_DEV                         83
#define _SC_2_CHAR_TERM                     84
#define _SC_2_FORT_DEV                      85
#define _SC_2_FORT_RUN                      86
#define _SC_2_LOCALEDEF                     87
#define _SC_2_PBS                           88
#define _SC_2_PBS_ACCOUNTING                89
#define _SC_2_PBS_CHECKPOINT                90
#define _SC_2_PBS_LOCATE                    91
#define _SC_2_PBS_MESSAGE                   92
#define _SC_2_PBS_TRACK                     93
#define _SC_2_SW_DEV                        94
#define _SC_2_UPE                           95
#define _SC_2_VERSION                       96
#define _SC_PAGESIZE                        97
#define _SC_PAGE_SIZE                       _SC_PAGESIZE
#define _SC_THREAD_DESTRUCTOR_ITERATIONS    98
#define _SC_THREAD_KEYS_MAX                 99
#define _SC_THREAD_STACK_MIN                100
#define _SC_THREAD_THREADS_MAX              101
#define _SC_RE_DUP_MAX                      102
#define _SC_RTSIG_MAX                       103
#define _SC_SEM_NSEMS_MAX                   104
#define _SC_SEM_VALUE_MAX                   105
#define _SC_SIGQUEUE_MAX                    106
#define _SC_STREAM_MAX                      107
#define _SC_SYMLOOP_MAX                     108
#define _SC_TIMER_MAX                       109
#define _SC_TTY_NAME_MAX                    110
#define _SC_TZNAME_MAX                      111
#define _SC_XBS5_ILP32_OFF32                112
#define _SC_XBS5_ILP32_OFFBIG               113
#define _SC_XBS5_LP64_OFF64                 114
#define _SC_XBS5_LPBIG_OFFBIG               115
#define _SC_XOPEN_CRYPT                     116
#define _SC_XOPEN_ENH_I18N                  117
#define _SC_XOPEN_LEGACY                    118
#define _SC_XOPEN_REALTIME                  119
#define _SC_XOPEN_REALTIME_THREADS          120
#define _SC_XOPEN_SHM                       121
#define _SC_XOPEN_STREAMS                   122
#define _SC_XOPEN_UNIX                      123
#define _SC_XOPEN_VERSION                   124

#define _SC_NPROCESSORS_CONF               1001
#define _SC_NPROCESSORS_ONLN               1002

#define _PC_LINK_MAX                      0
#define _PC_MAX_CANON                     1
#define _PC_MAX_INPUT                     2
#define _PC_NAME_MAX                      3
#define _PC_PATH_MAX                      4
#define _PC_PIPE_BUF                      5
#define _PC_CHOWN_RESTRICTED              6
#define _PC_NO_TRUNC                      7
#define _PC_VDISABLE                      8
#define _PC_ASYNC_IO                      9
#define _PC_PRIO_IO                      10
#define _PC_SYNC_IO                      11
#define _PC_FILESIZEBITS                 12
#define _PC_2_SYMLINKS                   13
#define _PC_SYMLINK_MAX                  14
#define _PC_ALLOC_SIZE_MIN               15
#define _PC_REC_INCR_XFER_SIZE           16
#define _PC_REC_MAX_XFER_SIZE            17
#define _PC_REC_MIN_XFER_SIZE            18
#define _PC_REC_XFER_ALIGN               19
#define _PC_TIMESTAMP_RESOLUTION         20

#ifdef  __cplusplus
}
#endif

#endif


