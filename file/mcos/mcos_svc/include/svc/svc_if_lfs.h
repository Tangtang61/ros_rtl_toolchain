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
[svc_if_lfs.h] - SVC interface library header (POSIX LFS)
****************************************************************************/

#ifndef SVC_IF_LFS_H
#define SVC_IF_LFS_H

#include <svc/svc_if.h>

/*
 * SVC Function ID
 */
#define SVCID_LFS_OPEN          (SVCID_LFS | 0x00000000)    /* open()       */
#define SVCID_LFS_CLOSE         (SVCID_LFS | 0x00000001)    /* close()      */
#define SVCID_LFS_READ          (SVCID_LFS | 0x00000002)    /* read()       */
#define SVCID_LFS_WRITE         (SVCID_LFS | 0x00000003)    /* write()      */
#define SVCID_LFS_UNLINK        (SVCID_LFS | 0x00000004)    /* write()      */
#define SVCID_LFS_LSEEK         (SVCID_LFS | 0x00000005)    /* lseek()      */
#define SVCID_LFS_ISATTY        (SVCID_LFS | 0x00000006)    /* isatty()     */
#define SVCID_LFS_FSTAT         (SVCID_LFS | 0x00000007)    /* fstat()      */
#define SVCID_LFS_FTRUNCATE     (SVCID_LFS | 0x00000008)    /* ftruncate()  */
#define SVCID_LFS_ACCESS        (SVCID_LFS | 0x00000009)    /* access()     */
#define SVCID_LFS_CHDIR         (SVCID_LFS | 0x0000000a)    /* chdir()      */
#define SVCID_LFS_CHMOD         (SVCID_LFS | 0x0000000b)    /* chmod()      */
#define SVCID_LFS_CHOWN         (SVCID_LFS | 0x0000000c)    /* chown()      */
#define SVCID_LFS_DUP           (SVCID_LFS | 0x0000000d)    /* dup()        */
#define SVCID_LFS_DUP2          (SVCID_LFS | 0x0000000e)    /* dup2()       */
#define SVCID_LFS_FCHDIR        (SVCID_LFS | 0x0000000f)    /* fchdir()     */
#define SVCID_LFS_FCHMOD        (SVCID_LFS | 0x00000010)    /* fchmod()     */
#define SVCID_LFS_FCHOWN        (SVCID_LFS | 0x00000011)    /* fchown()     */
#define SVCID_LFS_FCNTL         (SVCID_LFS | 0x00000012)    /* fcntl()      */
#define SVCID_LFS_FDATASYNC     (SVCID_LFS | 0x00000013)    /* fdatasync()  */
#define SVCID_LFS_FSTATVFS      (SVCID_LFS | 0x00000014)    /* fstatvfs()   */
#define SVCID_LFS_FSYNC         (SVCID_LFS | 0x00000015)    /* fsync()      */
#define SVCID_LFS_GETCWD        (SVCID_LFS | 0x00000016)    /* getcwd()     */
#define SVCID_LFS_IOCTL         (SVCID_LFS | 0x00000017)    /* ioctl()      */
#define SVCID_LFS_LINK          (SVCID_LFS | 0x00000018)    /* link()       */
#define SVCID_LFS_STAT          (SVCID_LFS | 0x00000019)    /* stat()       */
#define SVCID_LFS_STATVFS       (SVCID_LFS | 0x0000001a)    /* statvfs()    */
#define SVCID_LFS_TRUNCATE      (SVCID_LFS | 0x0000001b)    /* truncate()   */
#define SVCID_LFS_REALPATH      (SVCID_LFS | 0x0000001c)    /* realpath()   */
#define SVCID_LFS_UMASK         (SVCID_LFS | 0x0000001d)    /* umask()      */
#define SVCID_LFS_UTIME         (SVCID_LFS | 0x0000001e)    /* utime()      */
#define SVCID_LFS_PREAD         (SVCID_LFS | 0x0000001f)    /* pread()      */
#define SVCID_LFS_PWRITE        (SVCID_LFS | 0x00000020)    /* pwrite()     */
#define SVCID_LFS_READV         (SVCID_LFS | 0x00000021)    /* readv()      */
#define SVCID_LFS_WRITEV        (SVCID_LFS | 0x00000022)    /* writev()     */
#define SVCID_LFS_RMDIR         (SVCID_LFS | 0x00000023)    /* rmdir()      */
#define SVCID_LFS_SELECT        (SVCID_LFS | 0x00000024)    /* select()     */
#define SVCID_LFS_PSELECT       (SVCID_LFS | 0x00000025)    /* pselect()    */
#define SVCID_LFS_READDIR       (SVCID_LFS | 0x00000026)    /* __readdir()  */
#define SVCID_LFS_MKDIR         (SVCID_LFS | 0x00000027)    /* mkdir()      */
#define SVCID_LFS_RENAME        (SVCID_LFS | 0x00000028)    /* rename()     */

#ifndef _in_asm_source_

/*
 * SVC Parameter Packet
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <utime.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <sys/uio.h>

/* open() */
typedef struct {
    int         id;
    const char* path;
    int         oflag;
    mode_t      mode;
} svc_packet_open_t;

/* close() */
typedef struct {
    int         id;
    int         fildes;
} svc_packet_close_t;

/* read() */
typedef struct {
    int         id;
    int         fildes;
    void        *buf;
    size_t      *nbyte;
} svc_packet_read_t;

/* write() */
typedef struct {
    int         id;
    int         fildes;
    const void  *buf;
    size_t      *nbyte;
} svc_packet_write_t;

/* unlink() */
typedef struct {
    int         id;
    const char* path;
} svc_packet_unlink_t;

/* lseek() */
typedef struct {
    int         id;
    int         fildes;
    off_t       offset;
    int         whence;
} svc_packet_lseek_t;

/* isatty() */
typedef struct {
    int         id;
    int         fildes;
} svc_packet_isatty_t;

/* fstat() */
typedef struct {
    int         id;
    int         fildes;
    struct stat *buf;
} svc_packet_fstat_t;

/* ftruncate() */
typedef struct {
    int         id;
    int         fildes;
    off_t       length;
} svc_packet_ftruncate_t;

/* access() */
typedef struct {
    int         id;
    const char  *path;
    int         amode;
} svc_packet_access_t;

/* chdir() */
typedef struct {
    int         id;
    const char  *path;
} svc_packet_chdir_t;

/* chmod() */
typedef struct {
    int         id;
    const char  *path;
    mode_t      mode;
} svc_packet_chmod_t;

/* chown() */
typedef struct {
    int         id;
    const char  *path;
    uid_t       owner;
    gid_t       group;
} svc_packet_chown_t;

/* dup() */
typedef struct {
    int         id;
    int         fildes;
} svc_packet_dup_t;

/* dup2() */
typedef struct {
    int         id;
    int         fildes;
    int         fildes2;
} svc_packet_dup2_t;

/* fchdir() */
typedef struct {
    int         id;
    int         fildes;
} svc_packet_fchdir_t;

/* fchmod() */
typedef struct {
    int         id;
    int         fildes;
    mode_t      mode;
} svc_packet_fchmod_t;

/* fchown() */
typedef struct {
    int         id;
    int         fildes;
    uid_t       owner;
    gid_t       group;
} svc_packet_fchown_t;

/* fcntl() */
typedef struct {
    int         id;
    int         fildes;
    int         cmd;
    int         arg;
} svc_packet_fcntl_t;

/* fdatasync() */
typedef struct {
    int         id;
    int         fildes;
} svc_packet_fdatasync_t;

/* fstatvfs() */
typedef struct {
    int             id;
    int             fildes;
    struct statvfs  *buf;
} svc_packet_fstatvfs_t;

/* fsync() */
typedef struct {
    int         id;
    int         fildes;
} svc_packet_fsync_t;

/* getcwd() */
typedef struct {
    int         id;
    char        *buf;
    size_t      size;
    char        **cwd;
} svc_packet_getcwd_t;

/* ioctl() */
typedef struct {
    int         id;
    int         fildes;
    int         request;
    void        *arg;
} svc_packet_ioctl_t;

/* link() */
typedef struct {
    int         id;
    const char  *path1;
    const char  *path2;
} svc_packet_link_t;

/* stat() */
typedef struct {
    int         id;
    const char  *path;
    struct stat *buf;
} svc_packet_stat_t;

/* statvfs() */
typedef struct {
    int             id;
    const char      *path;
    struct statvfs  *buf;
} svc_packet_statvfs_t;

/* truncate() */
typedef struct {
    int         id;
    const char  *path;
    off_t       length;
} svc_packet_truncate_t;

/* realpath() */
typedef struct {
    int         id;
    const char  *file_name;
    char        *resolved_name;
    char        **name;
} svc_packet_realpath_t;

/* umask() */
typedef struct {
    int         id;
    mode_t      cmask;
} svc_packet_umask_t;

/* utime() */
typedef struct {
    int                  id;
    const char           *path;
    const struct utimbuf *times;
} svc_packet_utime_t;

/* pread() */
typedef struct {
    int         id;
    int         fildes;
    void        *buf;
    size_t      *nbyte;
    off_t       offset;
} svc_packet_pread_t;

/* pwrite() */
typedef struct {
    int         id;
    int         fildes;
    const void  *buf;
    size_t      *nbyte;
    off_t       offset;
} svc_packet_pwrite_t;

/* readv() */
typedef struct {
    int                 id;
    int                 fildes;
    const struct iovec  *iov;
    int                 iovcnt;
    ssize_t             *rbyte;
} svc_packet_readv_t;

/* writev() */
typedef struct {
    int                 id;
    int                 fildes;
    const struct iovec  *iov;
    int                 iovcnt;
    ssize_t             *rbyte;
} svc_packet_writev_t;

/* rmdir() */
typedef struct {
    int         id;
    const char  *path;
} svc_packet_rmdir_t;

/* select() */
typedef struct {
    int                     id;
    int                     nfds;
    fd_set                  *readfds;
    fd_set                  *writefds;
    fd_set                  *errorfds;
    struct timeval          *timeout;
} svc_packet_select_t;

/* pselect() */
typedef struct {
    int                     id;
    int                     nfds;
    fd_set                  *readfds;
    fd_set                  *writefds;
    fd_set                  *errorfds;
    const struct timespec   *timeout;
    const sigset_t          *sigmask;
} svc_packet_pselect_t;

/* __readdir() */
typedef struct {
    int             id;
    DIR             *dir;
    struct dirent   *ent;
    struct dirent   **dirent;
} svc_packet_readdir_t;

/* mkdir() */
typedef struct {
    int         id;
    const char  *path;
    mode_t      mode;
} svc_packet_mkdir_t;

/* rename() */
typedef struct {
    int         id;
    const char  *old;
    const char  *new;
} svc_packet_rename_t;


/* List of POSIX LFS APIs */
typedef union {
    int                     id;
    svc_packet_open_t       param_open_;
    svc_packet_close_t      param_close_;
    svc_packet_read_t       param_read_;
    svc_packet_write_t      param_write_;
    svc_packet_unlink_t     param_unlink_;
    svc_packet_lseek_t      param_lseek_;
    svc_packet_isatty_t     param_isatty_;
    svc_packet_fstat_t      param_fstat_;
    svc_packet_ftruncate_t  param_ftruncate_;

    svc_packet_access_t     param_access_;
    svc_packet_chdir_t      param_chdir_;
    svc_packet_chmod_t      param_chmod_;
    svc_packet_chown_t      param_chown_;
    svc_packet_dup_t        param_dup_;
    svc_packet_dup2_t       param_dup2_;
    svc_packet_fchdir_t     param_fchdir_;
    svc_packet_fchmod_t     param_fchmod_;
    svc_packet_fchown_t     param_fchown_;
    svc_packet_fcntl_t      param_fcntl_;
    svc_packet_fdatasync_t  param_fdatasync_;
    svc_packet_fstatvfs_t   param_fstatvfs_;
    svc_packet_fsync_t      param_fsync_;
    svc_packet_getcwd_t     param_getcwd_;
    svc_packet_ioctl_t      param_ioctl_;
    svc_packet_link_t       param_link_;

    svc_packet_stat_t       param_stat_;
    svc_packet_statvfs_t    param_statvfs_;
    svc_packet_truncate_t   param_truncate_;
    svc_packet_realpath_t   param_realpath_;
    svc_packet_umask_t      param_umask_;
    svc_packet_utime_t      param_utime_;
    svc_packet_pread_t      param_pread_;
    svc_packet_pwrite_t     param_pwrite_;
    svc_packet_readv_t      param_readv_;
    svc_packet_writev_t     param_writev_;
    svc_packet_rmdir_t      param_rmdir_;
    svc_packet_select_t     param_select_;
    svc_packet_pselect_t    param_pselect_;

    svc_packet_readdir_t    param_readdir_;
    svc_packet_mkdir_t      param_mkdir_;

    svc_packet_rename_t     param_rename_;

} svc_packet_lfs_t;

#endif /* _in_asm_source_ */

#endif  /* #ifndef SVC_IF_LFS_H */
