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
dirops.c         POSIX Layer   POSIX libraries
============================================================================*/
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* API implementation */
struct dirent* __readdir(DIR* dir, struct dirent* ent);

/* path!=NULL && fd==-1 : called from opendir()
 * path==NULL && fd!=-1 : called from fdopendir() */
static DIR* _open_dir(const char* path, int fd)
{
    DIR*        dir;
    int         fno;
    int         sta;
    struct stat fst;

    dir = (DIR*)malloc(sizeof(*dir));
    if (dir == NULL)
    {
        errno = ENOMEM;
    }
    else
    {
     /* Open file internally, if necessary */
        if (path != NULL)
        {
            fno = open(path, O_RDONLY);
        }
        else
        {
            fno = fd;
        }

        sta = -1;
        if (fno >= 0)
        {
            sta = fstat(fno, &fst);
            if (sta == 0)
            {
             /* Check if file is a directory */
                if (S_ISDIR(fst.st_mode))
                {
                 /* If file is opened internally,
                  * the file descriptor closed on exec */
                    if (path != NULL)
                    {
                        sta = fcntl(fno, F_GETFD, 0);
                        if (sta >= 0)
                        {
                            sta = fcntl(fno, F_SETFD, sta | FD_CLOEXEC);
                        }
                    }

                    if (sta >= 0)
                    {
                     /* Initialize dir buffer */
                        dir->dd_buf  = 0;
                        dir->dd_loc  = 0;
                        dir->dd_size = 0;
                        dir->dd_fd   = fno;
                    }
                }
                else
                {
                    sta = -1;
                    errno = ENOTDIR;
                }
            }
        }

     /* Cleanup on error */
        if (sta < 0)
        {
            sta = errno;
            if ((path != NULL) && (fno != -1))
            {
             /* Close file */
                (void)close(fno);
            }
            free(dir);
            errno = sta;
            dir = NULL;
        }
    }
    return dir;
}

DIR* opendir(const char* path)
{
    DIR*    dir;

    if (path != NULL)
    {
        dir = _open_dir(path, -1);
    }
    else
    {
        dir = NULL;
        errno = EINVAL;
    }
    return dir;
}

DIR* fdopendir(int fd)
{
    DIR*    dir;

    if (fd != -1)
    {
        dir = _open_dir(NULL, fd);
    }
    else
    {
        dir = NULL;
        errno = EBADF;
    }
    return dir;
}

int closedir(DIR* dir)
{
    int err;
    int sta;

    sta = close(dir->dd_fd);
    if (sta == 0)
    {
        err = errno;
        dir->dd_fd = -1;
        if (dir->dd_buf != 0)
        {
            free(dir->dd_buf);
            dir->dd_buf = 0;
        }
        free(dir);
        errno = err;
    }
    return sta;
}

long telldir(DIR* dir)
{
    return (long)dir->dd_loc;
}


void seekdir(DIR* dir, long loc)
{
    dir->dd_loc = (int)loc;
}

void rewinddir(DIR* dir)
{
    dir->dd_loc = 0;
}

/* Directory read utility routine */
static struct dirent* _readdir(DIR* dir, struct dirent* ent)
{
    if ((unsigned)dir->dd_fd >= OPEN_MAX)
    {
        errno = EBADF;
        return 0;
    }
    if (ent == 0)
    {
        ent = (struct dirent*)dir->dd_buf;
        if (ent == 0)
        {
            ent = (struct dirent*)malloc(sizeof(*ent));
            if (ent == 0)
            {
                errno = ENOMEM;
                return 0;
            }
            (void)memset(ent, 0, sizeof(*ent));
            dir->dd_buf = (char*)ent;
        }
    }
    return __readdir(dir, ent);
}

/* readdir() service */
struct dirent* readdir(DIR* dir)
{
    return _readdir(dir, 0);
}

/* readdir_r() service */
int readdir_r(DIR* dir, struct dirent* ent, struct dirent** res)
{
    int            old;
    int            sta;
    struct dirent* ret;

    sta = 0;
    old = errno;
    errno = 0;
    ret = _readdir(dir, ent);
    sta = errno;
    errno = old;
    if (ret == 0)
    {
        if (sta != 0)
        {
            return sta;
        }
    }
    *res = ret;
    return    0;
}

/* Extract dir fd */
int dirfd(DIR* dirp)
{
    return dirp->dd_fd;
}
