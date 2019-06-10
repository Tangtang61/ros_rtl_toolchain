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
 sys/mman.h - Logical File System (LFS) Memory management definitions
============================================================================*/

#ifndef _SYS_MMAN_H_
#define _SYS_MMAN_H_

#include <sys/types.h>
#include <stddef.h>

#ifdef  __cplusplus
extern  "C" {
#endif

/*
 *  Memory protection values
 */
#define PROT_NONE       0               /* Data cannot be accessed          */
#define PROT_READ       1               /* Data can be read                 */
#define PROT_WRITE      2               /* Data can be written              */
#define PROT_EXEC       4               /* Data can be executed             */

/*
 *  Mmap flags
 */
#define MAP_SHARED      1               /* Shared memory changes            */
#define MAP_PRIVATE     2               /* Private memory changes           */
#define MAP_FIXED       4               /* Interpret address exactly        */
#define MAP_ANONYMOUS   8               /* Unnamed memory region            */
#define MAP_ANON        MAP_ANONYMOUS
#define MAP_FILE        0               /* Named memory region (ignored)    */

/*
 *  Mmap error return
 */
#define MAP_FAILED      (void*)-1       /* Memory mapping failure           */

/*
 *  Memory lock flags
 */
#define MCL_CURRENT     1               /* Lock pages mapped now            */
#define MCL_FUTURE      2               /* Lock pages mapped in future      */

/*
 *  Msync flags
 */
#define MS_ASYNC        1               /* Perform asynchronous writes      */
#define MS_SYNC         2               /* Perform synchronous writes       */
#define MS_INVALIDATE   4               /* Invalidate cached data           */

/*
 *  Mapping services
 */
void*   mmap(void* addr, size_t len, int prot, int flags, int fdes, off_t off);
int     munmap(void* addr, size_t len);
int     mprotect(void* addr, size_t len, int prot);
int     msync(void* addr, size_t len, int flags);

/*
 *  Locking services
 */
int     mlockall(int flags);
int     munlockall(void);
int     mlock(const void* addr, size_t len);
int     munlock(const void* addr, size_t len);

/*
 *  Shared memory object services
 */
int     shm_open(const char *name, int oflag, mode_t mode);
int     shm_unlink(const char *name);

#ifdef  __cplusplus
}
#endif

#endif  /* _SYS_MMAN_H_ */
