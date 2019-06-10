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
 setjmp.h
============================================================================*/

#ifndef __setjmp_h
#define __setjmp_h

#include <machine/setjmp.h>
#include <sys/cdefs.h>

#ifdef    __cplusplus
extern "C" {
#endif

#define _MCOS_ARM64_ABI __attribute__((__nothrow__))
#define _MCOS_ARM64_ABI_NORETURN __attribute__((__nothrow__)) __attribute__((__noreturn__))

#ifndef __SETJMP_DECLS
#define __SETJMP_DECLS
__BEGIN_DECLS
__BEGIN_NAMESPACE_STD
typedef _JBTYPE jmp_buf[_JBLEN];
__END_NAMESPACE_STD

typedef _JBTYPE sigjmp_buf[_JBLEN + 1];

__BEGIN_NAMESPACE_STD
/* Store the calling environment in BUF.  Return 0.  */
extern _MCOS_ARM64_ABI int setjmp(jmp_buf buf);

/*
 * Jump to the environment saved in BUF, making the `setjmp' call
 * there return VAL, or 1 if VAL is 0.
 */
extern _MCOS_ARM64_ABI_NORETURN void longjmp(jmp_buf buf, int val);
__END_NAMESPACE_STD

/* Store the calling environment in BUF.  Return 0.  */
extern _MCOS_ARM64_ABI int sigsetjmp (sigjmp_buf buf, int save);

/*
 * Jump to the environment saved in BUF, making the `sigsetjmp' call
 * there return VAL, or 1 if VAL is 0.
 */
extern _MCOS_ARM64_ABI_NORETURN void siglongjmp (sigjmp_buf buf, int val);
__END_DECLS
#endif /* __SETJMP_DECLS */

#ifndef __SETJMP_NO_EXPORTS  /* defined in ARM RVCT <csetjmp> */
__USING_NAMESPACE_STD(jmp_buf)
__USING_NAMESPACE_STD(setjmp)
__USING_NAMESPACE_STD(longjmp)
#endif  /* #ifndef __SETJMP_NO_EXPORTS */

#ifdef    __cplusplus
     /* Do as ARM libcxx header does */
#ifndef setjmp
#define setjmp(env) setjmp(env)
#endif
}
#endif

#endif  /* __setjmp_h */
