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
 sys/statvfs.h  Logical File System (LFS) PFS status interface definitions
============================================================================*/

#ifndef _SYS_STATVFS_H_
#define _SYS_STATVFS_H_

#include <sys/types.h>

#ifdef  __cplusplus
extern  "C" {
#endif

 /* PFS status structure */
struct statvfs
{
    unsigned long   f_bsize;    /* File system block size */
    unsigned long   f_frsize;   /* Fundamental file system block size */
    fsblkcnt_t      f_blocks;   /* Total number of blocks on file system in units of f_frsize */
    fsblkcnt_t      f_bfree;    /* Total number of free blocks */
    fsblkcnt_t      f_bavail;   /* Number of free blocks available to non-privileged process */
    fsfilcnt_t      f_files;    /* Total number of file serial numbers */
    fsfilcnt_t      f_ffree;    /* Total number of free file serial numbers */
    fsfilcnt_t      f_favail;   /* Number of file serial numbers available to non-privileged process */
    unsigned long   f_fsid;     /* File system ID */
    unsigned long   f_flag;     /* Bit mask of f_flag values */
    unsigned long   f_namemax;  /* Maximum filename length */
};

 /* Values of f_flag (keep in sync with lfs.h) */
#define ST_RDONLY       1            /* Readonly file system */
#define ST_READONLY     ST_RDONLY
#define ST_REMOVABLE    2            /* Removable file system */
#define ST_MEMORY       4            /* Memory file system */
#define ST_NETWORK      8            /* Network file system */
#define ST_DEVICE     (16|ST_MEMORY) /* Device file system */
#define ST_NOSUID     128            /* Does not support setuid()/ setgid() semantics */

 /* Prorotypes */
int statvfs(const char *, struct statvfs *);
int fstatvfs(int, struct statvfs *);

#ifdef  __cplusplus
}
#endif

#endif /* _SYS_STATVFS_H_ */
