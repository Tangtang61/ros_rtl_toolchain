/*  $NetBSD: stat.h,v 1.40 2000/04/17 14:31:23 mrg Exp $    */

/*-
 * Copyright (c) 1982, 1986, 1989, 1993
 *  The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *  This product includes software developed by the University of
 *  California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *  @(#)stat.h  8.12 (Berkeley) 8/17/94
 */

/*
   Copyright (C) 2019 By eSOL Co.,Ltd. Tokyo, Japan
   Modified to work with eMCOS.
*/

#ifndef _SYS_STAT_H_
#define _SYS_STAT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/features.h>
#include <sys/types.h>      /* XXX */
#include <sys/time.h>

struct stat {
    dev_t     st_dev;       /* inode's device */
    ino_t     st_ino;       /* inode's number */
    mode_t    st_mode;      /* inode protection mode */
    nlink_t   st_nlink;     /* number of hard links */
    uid_t     st_uid;       /* user ID of the file's owner */
    gid_t     st_gid;       /* group ID of the file's group */
    off_t     st_size;      /* file size, in bytes */
    time_t    st_atime;     /* time of last access */
    time_t    st_mtime;     /* time of last data modification */
    time_t    st_ctime;     /* time of last file status change */
};

#define S_ISUID 0x0800          /* set user id on execution */
#define S_ISGID 0x0400          /* set group id on execution */
/*
 * #define S_ISUID 0004000
 * #define S_ISGID 0002000
 */
#define S_ISTXT 0x0200          /* sticky bit */
/*
 * #define S_ISTXT 0001000
 */

#ifndef __ghs__
#define S_IRWXU 0x01c0          /* RWX mask for owner */
#define S_IRUSR 0x0100          /* R for owner */
#define S_IWUSR 0x0080          /* W for owner */
#define S_IXUSR 0x0040          /* X for owner */
#else
#define S_IRWXU 0x0700          /* RWX mask for owner */
#define S_IRUSR 0x0400          /* R for owner */
#define S_IWUSR 0x0200          /* W for owner */
#define S_IXUSR 0x0100          /* X for owner */
#endif

/*
 * #define S_IRWXU 0000700
 * #define S_IRUSR 0000400
 * #define S_IWUSR 0000200
 * #define S_IXUSR 0000100
*/

#define S_IREAD     S_IRUSR
#define S_IWRITE    S_IWUSR
#define S_IEXEC     S_IXUSR

#ifndef __ghs__
#define S_IRWXG 0x0038          /* RWX mask for group */
#define S_IRGRP 0x0020          /* R for group */
#define S_IWGRP 0x0010          /* W for group */
#define S_IXGRP 0x0008          /* X for group */
#else
#define S_IRWXG 0x0070          /* RWX mask for group */
#define S_IRGRP 0x0040          /* R for group */
#define S_IWGRP 0x0020          /* W for group */
#define S_IXGRP 0x0010          /* X for group */
#endif

/*
 * #define S_IRWXG 0000070
 * #define S_IRGRP 0000040
 * #define S_IWGRP 0000020
 * #define S_IXGRP 0000010
 */

#define S_IRWXO 0x0007          /* RWX mask for other */
#define S_IROTH 0x0004          /* R for other */
#define S_IWOTH 0x0002          /* W for other */
#define S_IXOTH 0x0001          /* X for other */
/*
 * #define S_IRWXO 0000007
 * #define S_IROTH 0000004
 * #define S_IWOTH 0000002
 * #define S_IXOTH 0000001
 */

#define _S_IFMT   0xf000        /* type of file mask */
#define _S_IFIFO  0x1000        /* named pipe (fifo) */
#define _S_IFCHR  0x2000        /* character special */
#define _S_IFDIR  0x4000        /* directory */
#define _S_IFBLK  0x6000        /* block special */
#define _S_IFREG  0x8000        /* regular */
#define _S_IFMQ   0x9000        /* message queue (POSIX Layer) */
#define _S_IFLNK  0xa000        /* symbolic link */
#define _S_IFSEM  0xb000        /* semaphore (POSIX Layer) */
#define _S_ISVTX  0x0200        /* save swapped text even after use */
#define _S_IFSOCK 0xc000        /* socket */
#define _S_IFSHM  0xd000        /* shared memory object (POSIX Layer) */
#define _S_IFWHT  0xe000        /* whiteout */
#define _S_ARCH1  0x10000       /* Archive state 1, ls -l shows 'a' */
#define _S_ARCH2  0x20000       /* Archive state 2, ls -l shows 'A' */
/*
 * #define _S_IFMT   0170000
 * #define _S_IFIFO  0010000
 * #define _S_IFCHR  0020000
 * #define _S_IFDIR  0040000
 * #define _S_IFBLK  0060000
 * #define _S_IFREG  0100000
 * #define _S_IFMQ   0110000
 * #define _S_IFLNK  0120000
 * #define _S_IFSEM  0130000
 * #define _S_ISVTX  0001000
 * #define _S_IFSOCK 0140000
 * #define _S_IFSHM  0150000
 * #define _S_IFWHT  0160000
 * #define _S_ARCH1  0200000
 * #define _S_ARCH2  0400000
 */

#if !defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE)
#define S_IFMT   _S_IFMT
#define S_IFIFO  _S_IFIFO
#define S_IFCHR  _S_IFCHR
#define S_IFDIR  _S_IFDIR
#define S_IFBLK  _S_IFBLK
#define S_IFREG  _S_IFREG
#define S_IFLNK  _S_IFLNK
#define S_ISVTX  _S_ISVTX
/* POSIX Layer */
#define S_IFMQ   _S_IFMQ
#define S_IFSEM  _S_IFSEM
#define S_IFSHM  _S_IFSHM
#endif
#define S_IFSOCK _S_IFSOCK
#define S_IFWHT  _S_IFWHT

#define S_ARCH1 _S_ARCH1
#define S_ARCH2 _S_ARCH2

#define S_ISDIR(m)  ((m & (mode_t)_S_IFMT) == (mode_t)_S_IFDIR) /* directory */
#define S_ISCHR(m)  ((m & (mode_t)_S_IFMT) == (mode_t)_S_IFCHR) /* char special */
#define S_ISBLK(m)  ((m & (mode_t)_S_IFMT) == (mode_t)_S_IFBLK) /* block special */
#define S_ISREG(m)  ((m & (mode_t)_S_IFMT) == (mode_t)_S_IFREG) /* regular file */
#define S_ISFIFO(m) ((m & (mode_t)_S_IFMT) == (mode_t)_S_IFIFO) /* fifo */
#if !defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE)
#define S_ISLNK(m)  ((m & (mode_t)_S_IFMT) == (mode_t)_S_IFLNK) /* symbolic link */
#endif
#define S_ISSOCK(m) ((m & (mode_t)_S_IFMT) == (mode_t)_S_IFSOCK)    /* socket */
#define S_ISWHT(m)  ((m & (mode_t)_S_IFMT) == (mode_t)_S_IFWHT) /* whiteout */
/* POSIX Layer */
#define S_TYPEISMQ(s)  (((s)->st_mode & (mode_t)_S_IFMT) == (mode_t)_S_IFMQ) /* mq */
#define S_TYPEISSEM(s) (((s)->st_mode & (mode_t)_S_IFMT) == (mode_t)_S_IFSEM) /* sem */
#define S_TYPEISSHM(s) (((s)->st_mode & (mode_t)_S_IFMT) == (mode_t)_S_IFSHM) /* shm */

#define ACCESSPERMS (S_IRWXU|S_IRWXG|S_IRWXO)   /* 0777 */
                            /* 7777 */
#define ALLPERMS    (S_ISUID|S_ISGID|S_ISTXT|S_IRWXU|S_IRWXG|S_IRWXO)
                            /* 0666 */
#define DEFFILEMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

#define S_BLKSIZE   512     /* block size used in the stat struct */

/*
 * Definitions of flags stored in file flags word.
 *
 * Super-user and owner changeable flags.
 */
#define UF_SETTABLE 0x0000ffff  /* mask of owner changeable flags */
#define UF_NODUMP   0x00000001  /* do not dump file */
#define UF_IMMUTABLE    0x00000002  /* file may not be changed */
#define UF_APPEND   0x00000004  /* writes to file may only append */
#define UF_OPAQUE   0x00000008  /* directory is opaque wrt. union */
/*
 * Super-user changeable flags.
 */
#define SF_SETTABLE 0xffff0000  /* mask of superuser changeable flags */
#define SF_ARCHIVED 0x00010000  /* file is archived */
#define SF_IMMUTABLE    0x00020000  /* file may not be changed */
#define SF_APPEND   0x00040000  /* writes to file may only append */

#ifdef _KERNEL
/*
 * Shorthand abbreviations of above.
 */
#define OPAQUE      (UF_OPAQUE)
#define APPEND      (UF_APPEND | SF_APPEND)
#define IMMUTABLE   (UF_IMMUTABLE | SF_IMMUTABLE)
#endif /* _KERNEL */

#if !defined(_KERNEL) && !defined(_STANDALONE)
#include <sys/cdefs.h>

__BEGIN_DECLS
int chmod (const char *, mode_t);
int mkdir (const char *, mode_t);
int mkfifo (const char *, mode_t);
#ifdef __LIBC12_SOURCE__
int stat (const char *, struct stat12 *);
int fstat (int, struct stat12 *);
int __stat13 (const char *, struct stat *);
int __fstat13 (int, struct stat *);
#else
int stat (const char *, struct stat *) __RENAME(__stat13);
int fstat (int, struct stat *)     __RENAME(__fstat13);
#endif
mode_t  umask (mode_t);
#if !defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE)
int fchmod (int, mode_t);
#ifdef __LIBC12_SOURCE__
int lstat (const char *, struct stat12 *);
int __lstat13 (const char *, struct stat *);
#else
int lstat (const char *, struct stat *)    __RENAME(__lstat13);
#endif
int mknod (const char *, mode_t, dev_t);
#endif /* !defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) */

int chflags (const char *, unsigned long);
int fchflags (int, unsigned long);
int lchflags (const char *, unsigned long);
int lchmod (const char *, mode_t);
__END_DECLS

#endif /* !_KERNEL && !_STANDALONE */
#ifdef __cplusplus
}
#endif
#endif /* !_SYS_STAT_H_ */
