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
[signal_arm_gcc.S] - POSIX signal CPU architecture dependent part
****************************************************************************/

#define _in_asm_source_

    .section .text

/*
 * void pt_signal_entry(void);
 * Input     :   none
 * Output    :   none
 * Return    :   none
 * Note      :   none
 */
    .extern pt_signal_handler
    .global pt_signal_entry
    .type   pt_signal_entry, %function
pt_signal_entry:
    /* x0 and x1 */
    stp     x0, x1, [sp, #-16]!
    /* NZCV, FPSR, FPSR */
    mrs     x1, nzcv
    stp     x0, x1, [sp, #-16]!
    mrs     x0, fpcr
    mrs     x1, fpsr
    stp     x0, x1, [sp, #-16]!
    /* x2 ~ x29 */
    stp     x2,  x3,  [sp, #-16]!
    stp     x4,  x5,  [sp, #-16]!
    stp     x6,  x7,  [sp, #-16]!
    stp     x8,  x9,  [sp, #-16]!
    stp     x10, x11, [sp, #-16]!
    stp     x12, x13, [sp, #-16]!
    stp     x14, x15, [sp, #-16]!
    stp     x16, x17, [sp, #-16]!
    stp     x18, x19, [sp, #-16]!
    stp     x20, x21, [sp, #-16]!
    stp     x22, x23, [sp, #-16]!
    stp     x24, x25, [sp, #-16]!
    stp     x26, x27, [sp, #-16]!
    stp     x28, x29, [sp, #-16]!
    /* q0 ~ q31 */
    stp     q0,  q1,  [sp, #-32]!
    stp     q2,  q3,  [sp, #-32]!
    stp     q4,  q5,  [sp, #-32]!
    stp     q6,  q7,  [sp, #-32]!
    stp     q8,  q9,  [sp, #-32]!
    stp     q10, q11, [sp, #-32]!
    stp     q12, q13, [sp, #-32]!
    stp     q14, q15, [sp, #-32]!
    stp     q16, q17, [sp, #-32]!
    stp     q18, q19, [sp, #-32]!
    stp     q20, q21, [sp, #-32]!
    stp     q22, q23, [sp, #-32]!
    stp     q24, q25, [sp, #-32]!
    stp     q26, q27, [sp, #-32]!
    stp     q28, q29, [sp, #-32]!
    stp     q30, q31, [sp, #-32]!

    /* Call high-level signal handler processing
     * Return address of this handler will be stored into r0. */
    bl      pt_signal_handler
    /* x0 : should be the original(before interrupted) return address */

    /* q0 ~ q31 */
    ldp     q30, q31, [sp], #32
    ldp     q28, q29, [sp], #32
    ldp     q26, q27, [sp], #32
    ldp     q24, q25, [sp], #32
    ldp     q22, q23, [sp], #32
    ldp     q20, q21, [sp], #32
    ldp     q18, q19, [sp], #32
    ldp     q16, q17, [sp], #32
    ldp     q14, q15, [sp], #32
    ldp     q12, q13, [sp], #32
    ldp     q10, q11, [sp], #32
    ldp     q8,  q9,  [sp], #32
    ldp     q6,  q7,  [sp], #32
    ldp     q4,  q5,  [sp], #32
    ldp     q2,  q3,  [sp], #32
    ldp     q0,  q1,  [sp], #32
    /* x4 ~ x29 */
    ldp     x28, x29, [sp], #16
    ldp     x26, x27, [sp], #16
    ldp     x24, x25, [sp], #16
    ldp     x22, x23, [sp], #16
    ldp     x20, x21, [sp], #16
    ldp     x18, x19, [sp], #16
    ldp     x16, x17, [sp], #16
    ldp     x14, x15, [sp], #16
    ldp     x12, x13, [sp], #16
    ldp     x10, x11, [sp], #16
    ldp     x8,  x9,  [sp], #16
    ldp     x6,  x7,  [sp], #16
    ldp     x4,  x5,  [sp], #16
    ldp     x2,  x3,  [sp], #16
    /* NZCV, FPSR, FPSR */
    ldp     x1, x30,  [sp], #16
    msr     fpcr, x1
    msr     fpsr, x30
    ldp     x1, x30,  [sp], #16
    msr     nzcv, x30
    /* x0 and x1 */
    mov     x30, x0
    ldp     x0,  x1,  [sp], #16

    ret
