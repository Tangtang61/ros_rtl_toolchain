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
 sys/lfs.h - Logical File System Interface Definitions
============================================================================*/

#ifndef _SYS_LFS_H_
#define _SYS_LFS_H_

#include    <sys/types.h>
#include    <sys/utime.h>
#include    <sys/statvfs.h>
#include    <dirent.h>

#define MCOS_CFG_GLB_HWCL_MAX (1)

#ifdef  __cplusplus
extern  "C" {
#endif

/*
 *  Type Definitions
 */
typedef unsigned int    pfs_t;              /* PFS identifier               */
typedef unsigned int    fid_t;              /* LFS & PFS file identifier    */
typedef union lfs       lfs_t;              /* LFS request identifier       */

/*
 *  PFS flags
 */
#define PFS_READONLY     1                  /* Readonly file system         */
#define PFS_REMOVABLE    2                  /* Removable file system        */
#define PFS_MEMORY       4                  /* Memory file system           */
#define PFS_NETWORK      8                  /* Network file system          */
#define PFS_DEVICE      (16|PFS_MEMORY)     /* Device file system           */
#define PFS_CSMODEL      32             /* Client-server model file system  */
#define PFS_USEABORT     64                 /* Abort supported file system  */
#define PFS_PRIVILEGE    128                /* Privilege file system        */
#define PFS_MASK         0xff               /* PFS flags mask               */
#define PFS_SHIFT        8                  /* Right shift for PFS index    */

/*
 * Client-server model file system flags
 *
 * When PFS_PRIVILEGE and PFS_CSMODEL are effective, PFS_HWCREMOTE is used.
 */
#if MCOS_CFG_GLB_HWCL_MAX > 1
#define PFS_HWCREMOTE    256                /* Remote HWCL file system      */
#endif

/*
 *  PFS command codes
 */
#define PFS_OPEN         0
#define PFS_CLOSE        1
#define PFS_READ         2
#define PFS_WRITE        3
#define PFS_IOCTL        4
#define PFS_STAT         5
#define PFS_FSTAT        6
#define PFS_ACCESS       7
#define PFS_READDIR      8
#define PFS_CHDIR        9
#define PFS_FCHDIR      10
#define PFS_FSYNC       11
#define PFS_TRUNC       12
#define PFS_LINK        13
#define PFS_UNLINK      14
#define PFS_RENAME      15
#define PFS_CHMOD       16
#define PFS_FCHMOD      17
#define PFS_CHOWN       18
#define PFS_UTIME       19
#define PFS_MKDIR       20
#define PFS_RMDIR       21
#define PFS_STATVFS     22
#define PFS_FSTATVFS    23
#define PFS_FCHOWN      24
#define PFS_SELECT      25
#define PFS_WAITSRV     26
#define PFS_GETDONE     27
#if MCOS_CFG_GLB_HWCL_MAX > 1
 /* LFS server-specific */
#define PFS_FINDSRV     28
#endif
#define PFS_INITDONE    29

/*
 *  DEV command codes
 */
#define DEV_DEVOPEN      0
#define DEV_DEVCLOSE     1
#define DEV_DEVREAD      2
#define DEV_DEVWRITE     3
#define DEV_DEVCTL       4
#define DEV_DEVSELECT    5
#define DEV_DEVGETDONE   6

struct  lfs_open
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    const char*     name;                   /* File name                    */
    int             flags;                  /* Open flags                   */
    mode_t          mode;                   /* Open mode                    */
    fid_t*          fid;                    /* Pointer to return fid        */
};

struct  lfs_close
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    fid_t           fid;                    /* PFS file ID                  */
    int             flags;                  /* Open flags                   */
};

struct  lfs_read
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    fid_t           fid;                    /* PFS file ID                  */
    int             flags;                  /* Open flags                   */
    void*           buf;                    /* User buffer                  */
    size_t*         len;                    /* Read and return size ptr     */
    off_t*          off;                    /* File offset ptr              */
    off_t*          ret;                    /* Return offset ptr            */
};

struct  lfs_write
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    fid_t           fid;                    /* PFS file ID                  */
    int             flags;                  /* Open flags                   */
    void*           buf;                    /* User buffer                  */
    size_t*         len;                    /* Write and return size ptr    */
    off_t*          off;                    /* File offset ptr              */
    off_t*          ret;                    /* Return offset ptr            */
};

struct  lfs_ioctl
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    fid_t           fid;                    /* PFS file ID                  */
    int             flags;                  /* Open flags                   */
    int             dcmd;                   /* Command to device            */
    void*           data;                   /* Ptr to in/out data           */
    size_t          size;                   /* Data size                    */
    int*            info;                   /* Ptr to return device info    */
};

struct  lfs_devopen
{
    int             code;                   /* Command code                 */
    int             device;                 /* Device flags & unit          */
    int             flags;                  /* Open flags                   */
    int             nopen;                  /* Number of opens              */
};

struct  lfs_devclose
{
    int             code;                   /* Command code                 */
    int             device;                 /* Device flags & unit          */
    int             flags;                  /* Open flags                   */
    int             nopen;                  /* Number of opens              */
};

struct  lfs_devread
{
    int             code;                   /* Command code                 */
    int             device;                 /* Device flags & unit          */
    int             flags;                  /* Open flags                   */
    void*           buf;                    /* User buffer                  */
    int*            len;                    /* Read size and return size    */
    off_t*          off;                    /* File offset ptr              */
    off_t*          ret;                    /* Return offset ptr            */
};

struct  lfs_devwrite
{
    int             code;                   /* Command code                 */
    int             device;                 /* Device flags & unit          */
    int             flags;                  /* Open flags                   */
    void*           buf;                    /* User buffer                  */
    int*            len;                    /* Write size and return size   */
    off_t*          off;                    /* File offset ptr              */
    off_t*          ret;                    /* Return offset ptr            */
};

struct  lfs_devctl
{
    int             code;                   /* Command code                 */
    int             device;                 /* Device flags & unit          */
    int             flags;                  /* Open flags                   */
    int             dcmd;                   /* Command to device            */
    void*           data;                   /* Ptr to in/out data           */
    size_t          size;                   /* Data size                    */
    int*            info;                   /* Ptr to return device info    */
};

struct  lfs_devgetdone
{
    int             code;                   /* Command code                 */
    int             type;                   /* Blocking/nonblocking         */
    lfs_t**         ptr;                    /* Ptr to return finished lfs_t */
};

#define GETDONE_NONBLOCK  0
#define GETDONE_BLOCK     1

#define LFS_SELECT_READ    0x01             /* Data may be read             */
#define LFS_SELECT_WRITE   0x02             /* Data may be witten           */
#define LFS_SELECT_ERROR   0x04             /* Exception/error pending      */
#define LFS_SELECT_PRI     0x08             /* Urgent data (poll/epoll)     */
#define LFS_SELECT_HUP     0x10             /* Device hangup (poll/epoll)   */
#define LFS_SELECT_RDHUP   0x20             /* Peer shutdown (poll/epoll)   */
#define LFS_SELECT_ET      0x40             /* Edge triggered (epoll)       */
#define LFS_SELECT_CONSUME 0x80             /* Consume edge event (epoll)   */

 /* For eMCOS status field should be changed
    only at call with lfs_select.flags=0 */
struct  selreq
{
    struct srlist
    {
        struct srlist* next;
        struct srlist* prev;
    }               list;                   /* For use by PFS/dev for lists */
    unsigned char   status;                 /* Select status (r | w | e)    */
    unsigned char   request;                /* Select request (r | w | e)   */
    short           fildes;                 /* File descriptor              */
    unsigned int    thrid;                  /* Thread identifier to wakeup  */
};

struct  lfs_devselect
{
    int             code;                   /* Command code                 */
    int             device;                 /* Device flags & unit          */
    int             flags;                  /* Open flags                   */
    struct selreq*  selreq;                 /* Select request block         */
};

struct  lfs_link
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    const char*     oldn;                   /* Old file name                */
    const char*     newn;                   /* New file name                */
};


struct  lfs_fsync
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    fid_t           fid;                    /* PFS file ID                  */
    int             type;                   /* Fsync or fdatasync           */
    int             flags;                  /* Open flags                   */
};
#define TYPE_FSYNC      0                   /* Fsync command                */
#define TYPE_FDATASYNC  1                   /* Fdatasync command            */

struct  lfs_fdsync
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    fid_t           fid;                    /* PFS file ID                  */
};

struct  lfs_access
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    const char*     name;                   /* File name                    */
    int             amode;                  /* Access mode                  */
};

struct  lfs_fstat
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    fid_t           fid;                    /* PFS file ID                  */
    struct stat*    ptr;                    /* Pointer to stat structure    */
};

struct  lfs_stat
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    const char*     name;                   /* File name                    */
    struct stat*    ptr;                    /* Pointer to stat structure    */
};

struct  lfs_chmod
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    const char*     name;                   /* File name                    */
    mode_t          mode;                   /* File mode                    */
};

struct  lfs_fchmod
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    fid_t           fid;                    /* PFS file ID                  */
    mode_t          mode;                   /* File mode                    */
};

struct  lfs_chown
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    const char*     name;                   /* File name                    */
    uid_t           owner;                  /* Owner ID                     */
    gid_t           group;                  /* Group ID                     */
};

struct  lfs_fchown
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    fid_t           fid;                    /* PFS file ID                  */
    uid_t           owner;                  /* Owner ID                     */
    gid_t           group;                  /* Group ID                     */
};

struct  lfs_utime
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    const char*     name;                   /* File name                    */
    struct utimbuf* timb;                   /* Pointer to utimbuf structure */
};

struct  lfs_trunc
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    fid_t           fid;                    /* PFS file ID                  */
    off_t           len;                    /* Target length                */
};

struct  lfs_unlink
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    const char*     name;                   /* File name                    */
};

struct  lfs_rename
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    const char*     oldn;                   /* Old file name                */
    const char*     newn;                   /* New file name                */
};

struct  lfs_rmdir
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    const char*     name;                   /* File name                    */
};

struct  lfs_mkdir
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    const char*     name;                   /* File name                    */
    mode_t          mode;                   /* File mode                    */
};

struct  lfs_chdir
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    const char*     name;                   /* File name                    */
};

struct  lfs_fchdir
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    fid_t           fid;                    /* PFS file ID                  */
    char*           buf;                    /* Name buffer                  */
    int             len;                    /* Buffer size                  */
};

struct  lfs_readdir
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    fid_t           fid;                    /* PFS file ID                  */
    int             flags;                  /* Open flags                   */
    struct dirent*  ptr;                    /* Directory entry              */
    size_t*         len;                    /* Read and return size ptr     */
    off_t*          off;                    /* File offset ptr              */
    off_t*          ret;                    /* Return offset ptr            */
};

struct  lfs_statvfs
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    const char*     name;                   /* File name                    */
    struct statvfs* ptr;                    /* Pointer to statvfs structure */
};

struct  lfs_fstatvfs
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    fid_t           fid;                    /* PFS file ID                  */
    struct statvfs* ptr;                    /* Pointer to statvfs structure */
};

struct  lfs_select
{
    int             code;                   /* Command code                 */
    int             pflags;                 /* PFS flags & index            */
    fid_t           fid;                    /* PFS file ID                  */
    int             flags;                  /* Open flags                   */
    struct selreq*  selreq;                 /* Select request block         */
};

struct  lfs_getdone
{
    int             code;                   /* Command code                 */
    int             type;                   /* Blocking/nonblocking         */
    lfs_t**         ptr;                    /* Ptr to return finished lfs_t */
};

#if (MCOS_CFG_GLB_HWCL_MAX > 1)
struct  lfs_findsrv
{
    int             code;                   /* Command code                 */
    const char*     name;                   /* File name                    */
    pfs_t*          pfsid;                  /* To return PFS ident          */
    int*            pflags;                 /* To return PFS flags          */
    dev_t*          pfile;                  /* To return DEV ident or 0     */
    int*            dflags;                 /* To return DEV flags or 0     */
    int*            srvid;                  /* Server id LFS/PFS/DEV        */
};
#endif /* (MCOS_CFG_GLB_HWCL_MAX > 1) */
/*
 *  Device flags
 */
#define DEV_BLOCK           1               /* Block device                 */
#define DEV_CHARACTER       2               /* Character device             */
#define DEV_TTY             4               /* TTY device                   */
#define DEV_CONSOLE         8               /* Console device               */
#define DEV_MEMORY          16              /* Memory device                */
#define DEV_CSMODEL         32              /* Client-server model device   */
#define DEV_USEABORT        64              /* Abort supported device       */
#define DEV_PRIVILEGE       128             /* Privilege device             */
#define DEV_MASK            0xff            /* Device flags mask            */
#define DEV_SHIFT           8               /* Right shift for device unit  */


/*
 *  Request union
 */
union   lfs
{
    int                     r_code;
    struct  lfs_open        r_open;
    struct  lfs_close       r_close;
    struct  lfs_read        r_read;
    struct  lfs_write       r_write;
    struct  lfs_ioctl       r_ioctl;
    struct  lfs_link        r_link;
    struct  lfs_fsync       r_fsync;
    struct  lfs_access      r_access;
    struct  lfs_fstat       r_fstat;
    struct  lfs_stat        r_stat;
    struct  lfs_chmod       r_chmod;
    struct  lfs_fchmod      r_fchmod;
    struct  lfs_chown       r_chown;
    struct  lfs_fchown      r_fchown;
    struct  lfs_utime       r_utime;
    struct  lfs_trunc       r_trunc;
    struct  lfs_unlink      r_unlink;
    struct  lfs_rename      r_rename;
    struct  lfs_rmdir       r_rmdir;
    struct  lfs_mkdir       r_mkdir;
    struct  lfs_chdir       r_chdir;
    struct  lfs_fchdir      r_fchdir;
    struct  lfs_readdir     r_readdir;
    struct  lfs_statvfs     r_statvfs;
    struct  lfs_fstatvfs    r_fstatvfs;
    struct  lfs_select      r_select;
    struct  lfs_devopen     r_devopen;
    struct  lfs_devclose    r_devclose;
    struct  lfs_devread     r_devread;
    struct  lfs_devwrite    r_devwrite;
    struct  lfs_devctl      r_devctl;
    struct  lfs_devselect   r_devselect;
    struct  lfs_getdone     r_getdone;
    struct  lfs_devgetdone  r_devgetdone;
#if MCOS_CFG_GLB_HWCL_MAX > 1
    struct  lfs_findsrv     r_findsrv;
#endif
};

/*
 *  LFS extended information (OS dependent feature)
 */
/* For supporting abort feature */
struct lfs_abort
{
    void    (*brkfn)(int);      /* Break function       */
    void    (*stafn)(int);      /* Startup function     */
    void    (*clnfn)(int);      /* Cleanup function     */
    int     prio;               /* Priority of PFS(DEV) */
};
typedef struct lfs_abort lfs_abort_t;

/*
 *  LFS services prototypes
 */
pfs_t   mkfs(const char* name, int flags, ...);
dev_t   mkdev(const char* name, int flags, ...);
int     rmfs(const char* name);
int     rmdev(const char* name);
int     lfs_get_taskgroup(int taskid);

/*
 *  Device access services
 */
dev_t   dev_open(const char *name);
int     dev_close(dev_t dev);
int     dev_read(dev_t dev, void *buf, int len);
int     dev_write(dev_t dev, void *buf, int len);
int     dev_devctl(dev_t dev, int cmd, void *buf, size_t size, int *inf);

#include <stdint.h>
/* Common message processing routines. Return error code.
   Application PFS and DEV server threads should call corresponding
   routine and terminate when it returns (DEV/PFS removed) */
int lfs_pfs_csm_entry(uint32_t bufs, int (*pfsfunc)(lfs_t* req));
int lfs_dev_csm_entry(uint32_t bufs, int (*devfunc)(lfs_t* req));
/* Report PFS/DEV request done to driver thread.
   Note: to be called from driver/server thread context */
void lfs_pfs_reqdone(void);
void lfs_dev_reqdone(void);

/*
 * indicate I/O did not completed yet
 */
#define POSIX_EIOINCOMPLETE         (-65536)

#ifdef  __cplusplus
}
#endif

#endif  /* _SYS_LFS_H_ */
