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
[posix_atomic.h] - MCOS POSIX API atomics generic version
****************************************************************************/
#ifndef POSIX_ATOMIC_H
#define POSIX_ATOMIC_H

#ifdef __cplusplus
extern "C" {
#endif

 /* Atomic compare and set.
    Returns prvious memory value. */
int posix_atomic_cmpset(void* _p_, int _v_, int _n_);

/* Note we don't use 'snooze' or 'syncm' instructions
   because a contention failure window should be very short. */
int posix_atomic_add(void* _p_, int _v_);

int posix_atomic_sub(void* _p_, int _v_);

int posix_atomic_and(void* _p_, int _v_);

int posix_atomic_or(void* _p_, int _v_);

void posix_atomic_spinlock(int* _p_);

void posix_atomic_spinunlock(int* _p_);

void posix_atomic_set(void* _p_, int _v_);

int posix_atomic_get(void* _p_);

void posix_atomic_set_ptr(void* _p_, void* _v_);

void* posix_atomic_get_ptr(void* _p_);

void posix_atomic_purge(void* _p_);

int posix_crit_enter(void);

void posix_crit_leave(int _r_);

void sigsetjmp__(void);

#ifdef __cplusplus
extern "C" {
#endif

#endif /* POSIX_ATOMIC_H */
