/* Copyright (c) 2009, 2010, 2011, 2012 ARM Ltd.  All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:
 1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
 3. The name of the company may not be used to endorse or promote
    products derived from this software without specific prior written
    permission.

 THIS SOFTWARE IS PROVIDED BY ARM LTD ``AS IS'' AND ANY EXPRESS OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL ARM LTD BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

/* ANSI concatenation macros.  */
#define CONCAT(a, b) CONCAT2(a, b)
#define CONCAT2(a, b) a ## b

#ifdef __USER_LABEL_PREFIX__
#define FUNCTION( name ) CONCAT (__USER_LABEL_PREFIX__, name)
#else
#error __USER_LABEL_PREFIX is not defined
#endif

#ifdef HAVE_INITFINI_ARRAY
#define _init	__libc_init_array
#define _fini	__libc_fini_array
#endif

/* In ELF64, the large addressing model is used and R_AARCH64_ABS64
   reloc is generated to relocate a 64-bit address.  Since 64-bit
   relocation is not available in ELF32, in order to have
   a single code path for both ELF64 and ELF32 classes, we synthesize
   a 64-bit relocation by using R_AARCH64_P32_ABS32 on one of the two
   .word directives, depending on the endianness.  */

.macro GEN_DWORD name
#if defined(__ILP32__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	.word \name
	.word 0
#elif defined(__ILP32__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	.word 0
	.word \name
#else
	.dword \name
#endif
.endm

/* Help tackle the pointer size difference between ELF64 and ELF32.  */
#ifdef __ILP32__
#define PTR_REG(n)	w##n
#define PTR_SIZE	4
#define PTR_LOG_SIZE	2
#else
#define PTR_REG(n)	x##n
#define PTR_SIZE	8
#define PTR_LOG_SIZE	3
#endif

	.text
.macro FUNC_START name
	.global \name
\name:
.endm

	.align	2

	FUNC_START	_mainCRTStartup
	FUNC_START	_start

	str x0, [sp, #-16]! /* Save argument */

	/* Setup an initial dummy frame with saved fp=0 and saved lr=0 */
	mov	x29, 0
	stp	x29, x29, [sp, #-16]!
	mov	x29, sp

       /* Initialize exception vector table, flatmap, etc.  */
        bl      FUNCTION (_cpu_init_hook)

	/* Zero the memory in the .bss section.  */
	ldr	x0, .LC1		/* First arg: start of memory block */
	mov	w1, #0			/* Second arg: fill value */
	ldr	x2, .LC2
	sub	x2, x2, x0		/* Third arg: length of block */
	bl	FUNCTION (memset)


	/* .init and .fini sections are used to create constructors
	   and destructors.  Here we call the _init function and arrange
	   for _fini to be called at program exit.  */
	ldr	x0, .Lfini
	bl	FUNCTION (atexit)

	/* Initialization of POSIX SVC I/F */ 
	ldr     x0, =__callinit
	ldr     x0, [x0]
	ldr     x1, =__callfini
	ldr     x1, [x1]
	bl      _init_library
    
	ldr     x0, =_startup_error
	ldr     w0, [x0]
	cmp     w0, #0x0
	beq     _pass_mcos_init
infinie_loop2:
	nop
	b infinie_loop2                 /* Spin for debug */
_pass_mcos_init:
	bl	FUNCTION (_init)

	ldr     x0, [sp, #16]           /* Recover argument */
  	bl	FUNCTION (launch_proc_main)  /* Invoke main */

	b	FUNCTION (exit)		/* Cannot return.  */

/* Function initializing exception vector table, flatmap, etc.
   Declared as weak symbol so that user can override this definition
   by linking in their own version of the function.  */
	.weak FUNCTION (_cpu_init_hook)
FUNCTION (_cpu_init_hook):
	ret

	.align 3

	/* Pionters of init/fini functions used during the initialization of POSIX SVC I/F */ 
	.global __initloading
	.global __callinit
	.global __callfini
	.extern _init
	.extern _fini
initloading:
	/* No action */
	ret
__initloading:    .quad initloading
__callinit:       .quad  _init
__callfini:       .quad  _fini

.Lstack:
	GEN_DWORD __stack

	.weak __stack

.LC1:
	GEN_DWORD __bss_start__
.LC2:
	GEN_DWORD __bss_end__
.Lfini:
	GEN_DWORD FUNCTION(_fini)
