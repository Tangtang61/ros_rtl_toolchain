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
[__fork_armgcc.S] - fork() interface routine
****************************************************************************/

#define _in_asm_source_
#include <svc/svc_if_process.h>

    .global __fork

/* pid_t __fork() */
    .type   __fork, %function
__fork:
  /* Save callee-saved registers so that
     they will be duplicated to child */
    stp   x19, x20, [sp, #-16]!
    stp   x21, x22, [sp, #-16]!
    stp   x23, x24, [sp, #-16]!
    stp   x25, x26, [sp, #-16]!
    stp   x27, x28, [sp, #-16]!
    stp   x29, lr,  [sp, #-16]!

    stp   q8, q9,   [sp, #-32]!
    stp   q10, q11, [sp, #-32]!
    stp   q12, q13, [sp, #-32]!
    stp   q14, q15, [sp, #-32]!

/* Pass SVC packet in stack */
    ldr   x0, =SVCID_PROCESS_FORK
    ldr   x1, =fork_return
/* Second dword in stack is real return address */
    stp   x0, x1, [sp, #-16]!

/* Pass sp address as packet pointer */
    mov   x0, sp
    ldr   x1, =call_svc
    blr   x1

/* Restore callee-saved registers */
fork_return:
    nop
    add   sp, sp, #16
    ldp   q14, q15, [sp], #32
    ldp   q12, q13, [sp], #32
    ldp   q10, q11, [sp], #32
    ldp   q8, q9,   [sp], #32

    ldp   x29, lr,  [sp], #16
    ldp   x27, x28, [sp], #16
    ldp   x25, x26, [sp], #16
    ldp   x23, x24, [sp], #16
    ldp   x21, x22, [sp], #16
    ldp   x19, x20, [sp], #16
    ret
