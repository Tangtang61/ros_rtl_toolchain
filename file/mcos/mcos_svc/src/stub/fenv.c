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
[ fenv.c ]
****************************************************************************/
#include <fenv.h>
#include <stdio.h>

int feclearexcept(int excepts)
{
    printf("feclearexcept(): eMCOS does not support this POSIX API.\n");
    return -1;
}

int fegetexceptflag(fexcept_t *flagp, int excepts)
{
    printf("fegetexceptflag(): eMCOS does not support this POSIX API.\n");
    return -1;
}

int feraiseexcept(int excepts)
{
    printf("feraiseexcept(): eMCOS does not support this POSIX API.\n");
    return -1;
}

int fesetexceptflag(const fexcept_t *flagp, int excepts)
{
    printf("fesetexceptflag(): eMCOS does not support this POSIX API.\n");
    return -1;
}

int fetestexcept(int excepts)
{
    printf("fetestexcept(): eMCOS does not support this POSIX API.\n");
    return -1;
}

int fegetround(void)
{
    printf("fegetround(): eMCOS does not support this POSIX API.\n");
    return -1;
}

int fesetround(int rounding_mode)
{
    printf("fesetround(): eMCOS does not support this POSIX API.\n");
    return -1;
}

int fegetenv(fenv_t *envp)
{
    printf("fegetenv(): eMCOS does not support this POSIX API.\n");
    return -1;
}

int feholdexcept(fenv_t *envp)
{
    printf("feholdexcept(): eMCOS does not support this POSIX API.\n");
    return -1;
}

int fesetenv(const fenv_t *envp)
{
    printf("fesetenv(): eMCOS does not support this POSIX API.\n");
    return -1;
}

int feupdateenv(const fenv_t *envp)
{
    printf("feupdateenv(): eMCOS does not support this POSIX API.\n");
    return -1;
}
