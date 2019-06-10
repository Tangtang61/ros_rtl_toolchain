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
 sys/utsname.h
============================================================================*/

#ifndef _SYS_UTSNAME_H
#define _SYS_UTSNAME_H

#include <sys/features.h>

__BEGIN_DECLS

#define _UTSNAME_LENGTH 257
#define _UTSNAME_DOMAIN_LENGTH _UTSNAME_LENGTH
#define _UTSNAME_SYSNAME_LENGTH _UTSNAME_LENGTH
#define _UTSNAME_NODENAME_LENGTH _UTSNAME_LENGTH
#define _UTSNAME_RELEASE_LENGTH _UTSNAME_LENGTH
#define _UTSNAME_VERSION_LENGTH _UTSNAME_LENGTH
#define _UTSNAME_MACHINE_LENGTH _UTSNAME_LENGTH

struct utsname
{
    char sysname[_UTSNAME_SYSNAME_LENGTH];
    char nodename[_UTSNAME_NODENAME_LENGTH];
    char release[_UTSNAME_RELEASE_LENGTH];
    char version[_UTSNAME_VERSION_LENGTH];
    char machine[_UTSNAME_MACHINE_LENGTH];
};
extern int uname (struct utsname *__name) __THROW;

__END_DECLS

#endif /* _SYS_UTSNAME_H  */
