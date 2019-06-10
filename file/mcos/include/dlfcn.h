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
 dlfcn.h    POSIX Layer     Dynamic Linking definitions
============================================================================*/

#ifndef __DLFCN_H__
#define __DLFCN_H__

#ifdef  __cplusplus
extern  "C" {
#endif

/*
 * dlopen() mode
 * NOTE: The following definitions should be
 *       same with "include/extension/dynload.h".
 */
#define RTLD_LAZY           0x0001  /* Resolve the undefined symbol sequentially at runtime */
#define RTLD_NOW            0x0002  /* Resolve the undefined symbol at the time of loading */
#define RTLD_GLOBAL         0x0100  /* the symbol shall be handled as a global scope */
#define RTLD_BINDING_MASK   (DL_LAZY | DL_NOW)  /* Mask that specifies linking  */
#define RTLD_LOCAL          0x0000

/*
 * Library function
 * NOTE: These functions are implemented in "libdl.so".
 *       dlerror() is not supported (dummy-implemented).
 */
int dlclose(void *handle);
void *dlopen(const char *filename, int flag);
void *dlsym(void *handle, const char *symbol);
char *dlerror(void);

typedef struct
{
    const char *dli_fname;
    void *dli_fbase;
    const char *dli_sname;
    void *dli_saddr;
} Dl_info;
int dladdr (const void *__address, Dl_info *__info);

#ifdef  __cplusplus
}
#endif

#endif /* __DLFCN_H__ */
