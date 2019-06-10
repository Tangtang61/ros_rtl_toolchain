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
 sys/dirent.h
============================================================================*/

#ifndef _SYS_DIRENT_H_
#define _SYS_DIRENT_H_

#include <limits.h>
#include <unistd.h>

#ifdef  __cplusplus
extern  "C" {
#endif

/*
 *  Directory read structure
 */
typedef struct
{
    int             dd_fd;                  /* File descriptor              */
    int             dd_loc;                 /* Location within directory    */
    int             dd_size;                /* Size to read                 */
    char            *dd_buf;                /* Read buffer                  */
} DIR;

struct dirent
{
    ino_t           d_ino;                  /* Directory inode              */
    unsigned short  d_reclen;               /* Length of this dir record    */
    char            d_name[NAME_MAX+1];     /* Directory entry name         */
};

/*
 *  Functions prototypes
 */
DIR*            opendir(const char* name);
struct dirent*  readdir(DIR* dir);
int             readdir_r(DIR* dir, struct dirent *ent, struct dirent** res);
void            rewinddir(DIR* dir);
int             closedir(DIR* dir);
long            telldir(DIR* dir);
void            seekdir(DIR* dir, long loc);
DIR*            fdopendir(int fd);
int             dirfd(DIR *dirp);

#ifdef  __cplusplus
}
#endif

#endif  /* _SYS_DIRENT_H_ */

