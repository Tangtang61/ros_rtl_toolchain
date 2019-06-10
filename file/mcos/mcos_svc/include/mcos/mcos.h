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
[mcos.h] - MCOS interface header
****************************************************************************/
#ifndef MCOS_H
#define MCOS_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define MCOS_LCID_SELF                          (0)
#define MCOS_LCID_ANY                           (-1)
#define MCOS_LCID_INHERIT                       (-2)
#define MCOS_LCID_INVALID                       (-3)

typedef uint8_t mcos_bool_t;
#define mcos_false  0
#define mcos_true   1

typedef int16_t mcos_id_t;
typedef int16_t mcos_er_t;

typedef struct
{
    int32_t         upper;      /* Upper 32 bits of system time */
    uint32_t        lower;      /* Lower 32 bits of system time */
} mcos_systime_t;

#ifdef __cplusplus
}
#endif

#endif /* #ifndef MCOS_H */
