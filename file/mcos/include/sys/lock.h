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
 sys/lock.h
============================================================================*/

#ifndef _SYS_LOCK_H_
#define _SYS_LOCK_H_

#include <sys/cdefs.h>
#include <stddef.h>
#include <sys/pthread_mutex.h>

__BEGIN_DECLS

typedef pthread_mutex_t _LOCK_T, _LOCK_RECURSIVE_T;
typedef pthread_mutexattr_t _libc_lockattr_t;
struct _libc_rec_lock_init_entry {
    _LOCK_T * lock;
    struct _libc_rec_lock_init_entry * next;
};
void _libc_rec_lock_init_add(struct _libc_rec_lock_init_entry *);
void _libc_rec_lock_init_run(void);

#define __LOCK_INIT(_qualifier, _designator) \
    _qualifier _LOCK_T _designator = PTHREAD_MUTEX_INITIALIZER;

#define __LOCK_INIT_RECURSIVE(_qualifier, _designator) \
    _qualifier _LOCK_RECURSIVE_T _designator; \
    _qualifier struct _libc_rec_lock_init_entry _init_ent ## _designator __WEAK_IF_PUBLIC ## _qualifier = { &_designator }; \
    _qualifier void _ctor ## _designator(void) __attribute__((constructor)) __WEAK_IF_PUBLIC ## _qualifier; \
    _qualifier void _ctor ## _designator(void) { _libc_rec_lock_init_add(&_init_ent ## _designator); }

#define __WEAK_IF_PUBLICstatic
#define __WEAK_IF_PUBLIC __attribute__((weak))

#define __lock_init(_lock) pthread_mutex_init(&(_lock), NULL)
#define __lock_acquire(_lock) pthread_mutex_lock(&(_lock))
#define __lock_try_acquire(lock) pthread_mutex_try_lock(&(_lock))
#define __lock_release(_lock) pthread_mutex_unlock(&(_lock))
#define __lock_close(_lock) pthread_mutex_destroy(&(_lock))

#define __lock_init_recursive(_lock) \
    ({ \
        _libc_lockattr_t attr; \
        pthread_mutexattr_init(&attr); \
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE); \
        pthread_mutex_init(&(_lock), &attr); \
        pthread_mutexattr_destroy(&attr); \
    })
#define __lock_acquire_recursive(_lock) __lock_acquire(_lock)
#define __lock_try_acquire_recursive(lock) __lock_try_acquire(_lock)
#define __lock_release_recursive(_lock) __lock_release(_lock)
#define __lock_close_recursive(_lock) __lock_close(_lock)

__END_DECLS

#endif /* _SYS_LOCK_H_ */