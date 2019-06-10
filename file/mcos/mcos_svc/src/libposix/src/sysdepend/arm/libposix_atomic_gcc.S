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
[ libposix_atomic_armclang.S ] -
****************************************************************************/

#include <machine/setjmp.h>

    .section .text

/*
 * Atomic compare values and set new if equal. Returns previous.
 *  int posix_atomic_cmpset(void* p, int c, int t)
 */
    .global posix_atomic_cmpset
    .type   posix_atomic_cmpset, %function
posix_atomic_cmpset:
    mov   x4, x0
_posix_atomic_cmpset:
    ldxr  w0, [x4]
    cmp   w1, w0
    bne   _exit_err
    stxr  w3, w2, [x4]
    cbnz  w3, _posix_atomic_cmpset
    dmb   sy
    ret

_exit_err:
    clrex
    ret

/*
 * Atomic AND value. Returns previous.
 *   int posix_atomic_add(void* p, int t)
 */
    .global posix_atomic_add
    .type   posix_atomic_add, %function
posix_atomic_add:
    mov   x4, x0
_posix_atomic_add:
    ldxr  w0, [x4]
    add   w2, w0, w1
    stxr  w3, w2, [x4]
    cbnz  w3, _posix_atomic_add
    dmb   sy
    ret


/*
 * Atomic AND value. Returns previous.
 *  int posix_atomic_sub(void* p, int t)
 */
    .global posix_atomic_sub
    .type   posix_atomic_sub, %function
posix_atomic_sub:
    mov   x4, x0
_posix_atomic_sub:
    ldxr  w0, [x4]
    sub   w2, w0, w1
    stxr  w3, w2, [x4]
    cbnz  w3, _posix_atomic_sub
    dmb   sy
    ret


/*
 * Atomic AND value. Returns previous.
 *   int posix_atomic_and(void* p, int t)
 */
    .global posix_atomic_and
    .type   posix_atomic_and, %function
posix_atomic_and:
    mov   x4, x0
_posix_atomic_and:
    ldxr  w0, [x4]
    and   w2, w0, w1
    stxr  w3, w2, [x4]
    cbnz  w3, _posix_atomic_and
    dmb   sy
    ret


/*
 * Atomic OR value. Returns previous.
 *  int posix_atomic_or(void* p, int t)
 */
    .global posix_atomic_or
    .type   posix_atomic_or, %function
posix_atomic_or:
    mov   x4, x0
_posix_atomic_or:
    ldxr  w0, [x4]
    orr   w2, w0, w1
    stxr  w3, w2, [x4]
    cbnz  w3, _posix_atomic_or
    dmb   sy
    ret


/*
 * Atomic spin lock
 *  void posix_atomic_spinlock(int* _p_)
 */
    .global posix_atomic_spinlock
    .type   posix_atomic_spinlock, %function
posix_atomic_spinlock:
    mov   w1, #1
_atomic_spinlock_loop:
    ldxr  w2, [x0]
    cbz   w2, _get_lock
    wfe
    b     _atomic_spinlock_loop
_get_lock:
    stxr  w2, w1, [x0]
    cbnz  w2, _atomic_spinlock_loop
    dmb   sy
    ret

/*
 * Atomic spin unlock
 *  void posix_atomic_spinunlock(int* _p_)
 */
    .global posix_atomic_spinunlock
    .type   posix_atomic_spinunlock, %function
posix_atomic_spinunlock:
    str   wzr, [x0]
    dmb   sy
    sev
    ret

/* sigsetjmp() API */
    .extern __sigsetjmp
    .extern setjmp
    .global sigsetjmp
    .type   sigsetjmp, %function
sigsetjmp:
    stp     x0, x30, [sp,#-16]!
    bl      __sigsetjmp
    ldp     x0, x30, [sp],#16
    ldr     x1, =setjmp
    br      x1
