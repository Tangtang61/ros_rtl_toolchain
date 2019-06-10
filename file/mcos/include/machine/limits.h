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
 machine/limits.h
============================================================================*/

#ifndef _MACHINE_LIMITS_H_
#define _MACHINE_LIMITS_H_

#define SCHAR_MIN  (-128)
#define SCHAR_MAX  127
#define UCHAR_MAX  255

#define CHAR_MIN   0
#define CHAR_MAX   255

#define MB_LEN_MAX 6

#define SHRT_MIN   (-0x8000)
#define SHRT_MAX   (0x7fff)
#define USHRT_MAX  (0xffff)
#define INT_MIN    (~0x7fffffff)
#define INT_MAX    (0x7fffffff)
#define UINT_MAX   (0xffffffffU)
#define LONG_MIN   (~0x7fffffffffffffffL)
#define LONG_MAX   (0x7fffffffffffffffL)
#define ULONG_MAX  (0xffffffffffffffffUL)

#define LLONG_MIN  (~0x7fffffffffffffffLL)
#define LLONG_MAX  (0x7fffffffffffffffLL)
#define ULLONG_MAX (0xffffffffffffffffULL)

#define LDBL_MAX   (1.79769313486231571e+308L)
#define LDBL_MIN   (2.22507385850720138e-308L)

#define SSIZE_MAX  INT_MAX
#define SIZE_T_MAX UINT_MAX

#define CHAR_BIT   8
#define LONG_BIT   64
#define WORD_BIT   32

#endif  /* _MACHINE_LIMITS_H_ */

