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
[pt_thread_if.h] - MCOS POSIX pthread interface definitions
****************************************************************************/
#ifndef PT_THREAD_IF_H
#define PT_THREAD_IF_H

#include <pthread.h>
#include <sys/types.h> /* for pthread_attr_t, PTHREAD_NAME_MAX */
#include <pt_api/pt.cfg>  /* for MCOS_CFG_PT_SSIZE_MIN/MAX, MCOS_CFG_PT_MIN/MAX_PRI */

#ifdef __cplusplus
extern "C" {
#endif

#define MCOS_CFG_THR_DEFAULT_STACKSIZE      (1024*1024)

typedef __uintptr_t uintptr_t;
typedef uint16_t    reqid_t;
typedef uint16_t    repid_t;
typedef int16_t     mcos_er_t;
typedef int16_t     mcos_erid_t;

 /* Bitfield attr[0]
    priority    :  8  priority
    detached    :  1  detached
    policy      :  2  SCHED_FIFO, SCHED_RR etc
    userstack   :  1  user-supplied stack
    scope       :  1  scope system
    inherit     :  1  inheritsched
    stdmsg      :  1  standard message
    msginherit  :  1  message inherit
    lcid        : 16  LCID */
#define PTHREAD_ATTR_PRIO_MASK         0xff
#define PTHREAD_ATTR_PRIO_SHIFT           0
#define PTHREAD_ATTR_DETACHED_MASK        1
#define PTHREAD_ATTR_DETACHED_SHIFT       8
#define PTHREAD_ATTR_POLICY_MASK          3
#define PTHREAD_ATTR_POLICY_SHIFT         9
#define PTHREAD_ATTR_USERSTACK_MASK       1
#define PTHREAD_ATTR_USERSTACK_SHIFT     11
#define PTHREAD_ATTR_SCOPE_MASK           1
#define PTHREAD_ATTR_SCOPE_SHIFT         12
#define PTHREAD_ATTR_INHERIT_MASK         1
#define PTHREAD_ATTR_INHERIT_SHIFT       13
#define PTHREAD_ATTR_STDMSG_MASK          1
#define PTHREAD_ATTR_STDMSG_SHIFT        14
#define PTHREAD_ATTR_MSGINHERIT_MASK      1
#define PTHREAD_ATTR_MSGINHERIT_SHIFT    15
#define PTHREAD_ATTR_LCID_MASK       0xffff
#define PTHREAD_ATTR_LCID_SHIFT          16

#define PTHREAD_ATTR_INVALID   0

 /* Attributes words named indexes */
#define ATIX    0     /* Attribute bits */
#define SZIX    1     /* Stack size */

#ifdef __cplusplus
}
#endif

#endif /* PT_THREAD_IF_H */
