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
[lfs_svc.c] - SVC interface library (POSIX LFS)
****************************************************************************/

#include <svc/svc_if.h>

#define open	__open__	/* for variadic argument */
#define fcntl	__fcntl__
#define ioctl	__ioctl__
#include <svc/svc_if_lfs.h>
#include <sys/socket.h>
#include "mcos/mcos.h"
#undef open					/* for variadic argument */
#undef fcntl
#undef ioctl

#include <time.h>
#define MILLITONANO (1000000)

int open(const char *path, int oflag,  mode_t mode)
{
	svc_packet_open_t	p;

	p.id		= SVCID_LFS_OPEN;
	p.path		= path;
	p.oflag		= oflag;
	p.mode		= mode;
	return (int)call_svc((void*)&p);
}

int close(int fildes)
{
	svc_packet_close_t	p;

	p.id		= SVCID_LFS_CLOSE;
	p.fildes	= fildes;
	return (int)call_svc((void*)&p);
}

ssize_t read(int fildes, void *buf, size_t nbyte)
{
	svc_packet_read_t	p;
	size_t	len = nbyte; /* Requested/Returned length */

	p.id		= SVCID_LFS_READ;
	p.fildes	= fildes;
	p.buf		= buf;
	p.nbyte 	= &len;
	(void)call_svc((void*)&p);
	return (ssize_t)len;
}

ssize_t write(int fildes, const void *buf, size_t nbyte)
{
	svc_packet_write_t	p;
	size_t	len = nbyte; /* Requested/Returned length */

	p.id		= SVCID_LFS_WRITE;
	p.fildes	= fildes;
	p.buf		= buf;
	p.nbyte 	= &len;
	(void)call_svc((void*)&p);
	return (ssize_t)len;
}

int unlink(const char *path)
{
	svc_packet_unlink_t	p;

	p.id		= SVCID_LFS_UNLINK;
	p.path		= path;
	return (int)call_svc((void*)&p);
}

off_t lseek(int fildes, off_t offset, int whence)
{
	svc_packet_lseek_t	p;

	p.id		= SVCID_LFS_LSEEK;
	p.fildes	= fildes;
	p.offset	= offset;
	p.whence	= whence;
	return (int)call_svc((void*)&p);
}

int isatty(int fildes)
{
	svc_packet_isatty_t	p;

	p.id		= SVCID_LFS_ISATTY;
	p.fildes	= fildes;
	return (int)call_svc((void*)&p);
}

int fstat(int fildes, struct stat *buf)
{
	svc_packet_fstat_t		p;

	p.id		= SVCID_LFS_FSTAT;
	p.fildes	= fildes;
	p.buf		= buf;
	return (int)call_svc((void*)&p);
}

int ftruncate(int fildes, off_t length)
{
	svc_packet_ftruncate_t		p;

	p.id		= SVCID_LFS_FTRUNCATE;
	p.fildes	= fildes;
	p.length	= length;
	return (int)call_svc((void*)&p);
}

int access(const char *path, int amode)
{
	svc_packet_access_t		p;

	p.id		= SVCID_LFS_ACCESS;
	p.path		= path;
	p.amode		= amode;
	return (int)call_svc((void*)&p);
}

int chdir(const char *path)
{
	svc_packet_chdir_t		p;

	p.id		= SVCID_LFS_CHDIR;
	p.path		= path;
	return (int)call_svc((void*)&p);
}

int chmod(const char *path, mode_t mode)
{
	svc_packet_chmod_t		p;

	p.id		= SVCID_LFS_CHMOD;
	p.path		= path;
	p.mode		= mode;
	return (int)call_svc((void*)&p);
}

int chown(const char *path, uid_t owner, gid_t group)
{
	svc_packet_chown_t		p;

	p.id		= SVCID_LFS_CHOWN;
	p.path		= path;
	p.owner		= owner;
	p.group		= group;
	return (int)call_svc((void*)&p);
}

int dup(int fildes)
{
	svc_packet_dup_t		p;

	p.id		= SVCID_LFS_DUP;
	p.fildes	= fildes;
	return (int)call_svc((void*)&p);
}

int dup2(int fildes, int fildes2)
{
	svc_packet_dup2_t		p;

	p.id		= SVCID_LFS_DUP2;
	p.fildes	= fildes;
	p.fildes2	= fildes2;
	return (int)call_svc((void*)&p);
}

int fchdir(int fildes)
{
	svc_packet_fchdir_t		p;

	p.id		= SVCID_LFS_FCHDIR;
	p.fildes	= fildes;
	return (int)call_svc((void*)&p);
}

int fchmod(int fildes, mode_t mode)
{
	svc_packet_fchmod_t		p;

	p.id		= SVCID_LFS_FCHMOD;
	p.fildes	= fildes;
	p.mode		= mode;
	return (int)call_svc((void*)&p);
}

int fchown(int fildes, uid_t owner, gid_t group)
{
	svc_packet_fchown_t		p;

	p.id		= SVCID_LFS_FCHOWN;
	p.fildes	= fildes;
	p.owner		= owner;
	p.group		= group;
	return (int)call_svc((void*)&p);
}

int _fcntl(int fildes, int cmd, unsigned long arg)
{
	svc_packet_fcntl_t		p;

	p.id		= SVCID_LFS_FCNTL;
	p.fildes	= fildes;
	p.cmd		= cmd;
	p.arg		= (int)arg;
	return (int)call_svc((void*)&p);
}

int fdatasync(int fildes)
{
	svc_packet_fdatasync_t		p;

	p.id		= SVCID_LFS_FDATASYNC;
	p.fildes	= fildes;
	return (int)call_svc((void*)&p);
}

int fstatvfs(int fildes, struct statvfs *buf)
{
	svc_packet_fstatvfs_t		p;

	p.id		= SVCID_LFS_FSTATVFS;
	p.fildes	= fildes;
	p.buf		= buf;
	return (int)call_svc((void*)&p);
}

int fsync(int fildes)
{
	svc_packet_fsync_t		p;

	p.id		= SVCID_LFS_FSYNC;
	p.fildes	= fildes;
	return (int)call_svc((void*)&p);
}

char* getcwd(char *buf, size_t size)
{
	svc_packet_getcwd_t		p;
	char	*cwd;

	p.id		= SVCID_LFS_GETCWD;
	p.buf		= buf;
	p.size		= size;
	p.cwd		= &cwd;
	(void)call_svc((void*)&p);
	return *p.cwd;
}

int ioctl(int fildes, int request, void *arg)
{
	svc_packet_ioctl_t		p;

	p.id		= SVCID_LFS_IOCTL;
	p.fildes	= fildes;
	p.request	= request;
	p.arg		= arg;
	return (int)call_svc((void*)&p);
}

int link(const char *path1, const char *path2)
{
	svc_packet_link_t		p;

	p.id		= SVCID_LFS_LINK;
	p.path1		= path1;
	p.path2		= path2;
	return (int)call_svc((void*)&p);
}

int stat(const char *path, struct stat *buf)
{
	svc_packet_stat_t		p;

	p.id		= SVCID_LFS_STAT;
	p.path		= path;
	p.buf		= buf;
	return (int)call_svc((void*)&p);
}

int statvfs(const char *path, struct statvfs *buf)
{
	svc_packet_statvfs_t		p;

	p.id		= SVCID_LFS_STATVFS;
	p.path		= path;
	p.buf		= buf;
	return (int)call_svc((void*)&p);
}

int truncate(const char *path, off_t length)
{
	svc_packet_truncate_t		p;

	p.id		= SVCID_LFS_TRUNCATE;
	p.path		= path;
	p.length	= length;
	return (int)call_svc((void*)&p);
}

char* realpath(const char *file_name, char *resolved_name)
{
	svc_packet_realpath_t		p;
	char	*name;
	char	*temp = NULL;

	/* Allocate memory for resolved path */
	if (resolved_name == NULL)
	{
		temp = malloc(PATH_MAX);
		resolved_name = temp;
	}

	p.id			= SVCID_LFS_REALPATH;
	p.file_name		= file_name;
	p.resolved_name	= resolved_name;
	p.name			= &name;
	(void)call_svc((void*)&p);

	/* Release memory on failure */
	if ((name == NULL) && (temp != NULL))
	{
		free(temp);
	}

	return *p.name;
}

mode_t umask(mode_t cmask)
{
	svc_packet_umask_t		p;

	p.id		= SVCID_LFS_UMASK;
	p.cmask		= cmask;
	return (int)call_svc((void*)&p);
}

int utime(const char *path, const struct utimbuf *times)
{
	svc_packet_utime_t		p;

	p.id		= SVCID_LFS_UTIME;
	p.path		= path;
	p.times		= times;
	return (int)call_svc((void*)&p);
}

ssize_t pread(int fildes, void *buf, size_t nbyte, off_t offset)
{
	svc_packet_pread_t	p;
	size_t	len = nbyte; /* Requested/Returned length */

	p.id		= SVCID_LFS_PREAD;
	p.fildes	= fildes;
	p.buf		= buf;
	p.nbyte 	= &len;
	p.offset 	= offset;
	(void)call_svc((void*)&p);
	return (ssize_t)len;
}

ssize_t pwrite(int fildes, const void *buf, size_t nbyte, off_t offset)
{
	svc_packet_pwrite_t	p;
	size_t	len = nbyte; /* Requested/Returned length */

	p.id		= SVCID_LFS_PWRITE;
	p.fildes	= fildes;
	p.buf		= buf;
	p.nbyte 	= &len;
	p.offset 	= offset;
	(void)call_svc((void*)&p);
	return (ssize_t)len;
}

ssize_t readv(int fildes, const struct iovec *iov, int iovcnt)
{
	svc_packet_readv_t	p;
	ssize_t	len; /* Returned length */

	p.id		= SVCID_LFS_READV;
	p.fildes	= fildes;
	p.iov		= iov;
	p.iovcnt	= iovcnt;
	p.rbyte		= &len;
	(void)call_svc((void*)&p);
	return (ssize_t)len;
}

ssize_t writev(int fildes, const struct iovec *iov, int iovcnt)
{
	svc_packet_writev_t	p;
	ssize_t	len; /* Returned length */

	p.id		= SVCID_LFS_WRITEV;
	p.fildes	= fildes;
	p.iov		= iov;
	p.iovcnt	= iovcnt;
	p.rbyte		= &len;
	(void)call_svc((void*)&p);
	return (ssize_t)len;
}

int rmdir(const char *path)
{
	svc_packet_rmdir_t		p;

	p.id		= SVCID_LFS_RMDIR;
	p.path		= path;
	return (int)call_svc((void*)&p);
}

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout)
{
	svc_packet_select_t		p;

	p.id		= SVCID_LFS_SELECT;
	p.nfds		= nfds;
	p.readfds	= readfds;
	p.writefds	= writefds;
	p.errorfds	= errorfds;
	p.timeout	= timeout;

	sched_yield();
	struct timespec ts_req = {0, 20 * MILLITONANO};
	nanosleep(&ts_req, NULL);

	return (int)call_svc((void*)&p);
}

int pselect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, const struct timespec *timeout, const sigset_t *sigmask)
{
	svc_packet_pselect_t		p;

	p.id		= SVCID_LFS_PSELECT;
	p.nfds		= nfds;
	p.readfds	= readfds;
	p.writefds	= writefds;
	p.errorfds	= errorfds;
	p.timeout	= timeout;
	p.sigmask	= sigmask;
	return (int)call_svc((void*)&p);
}

struct dirent* __readdir(DIR* dir, struct dirent* ent)
{
	svc_packet_readdir_t		p;
	struct dirent	*dirent;

	p.id		= SVCID_LFS_READDIR;
	p.dir		= dir;
	p.ent		= ent;
	p.dirent	= &dirent;
	(void)call_svc((void*)&p);
	return *p.dirent;
}

int mkdir(const char *path, mode_t mode)
{
	svc_packet_mkdir_t	p;

	p.id		= SVCID_LFS_MKDIR;
	p.path		= path;
	p.mode		= mode;
	return (int)call_svc((void*)&p);
}

int rename(const char *old, const char *new)
{
	svc_packet_rename_t	p;

	p.id		= SVCID_LFS_RENAME;
	p.old		= old;
	p.new		= new;
	return (int)call_svc((void*)&p);
}

#include <stdarg.h>
#include <errno.h>
int fcntl(int fd, int cmd, ...) 
{
    int ret = 0;
    va_list	list;
    unsigned long	param;

    switch (cmd) {
    case F_DUPFD:
    case F_GETFD:
    case F_SETFD:
    case F_GETFL:
    case F_SETFL:
    case F_GETOWN:
    case F_SETOWN:
    case F_GETLK:
    case F_SETLK:
    case F_SETLKW:
    case F_DUPFD_CLOEXEC:
        break;
    default:
        errno = EINVAL;
        return -1;
    }

    switch (cmd) {
    case F_DUPFD:
    case F_DUPFD_CLOEXEC:
    case F_SETFD:
    case F_SETFL:
    case F_SETOWN:
        va_start(list, cmd);
        param = (unsigned long)(va_arg(list, int));
        va_end(list);
        break;

    case F_SETLK:
    case F_SETLKW:
    case F_GETLK:
        {
            void	*p;
            va_start(list, cmd);
            p = va_arg(list, void*);
            va_end(list);

            param = (unsigned long) p;
        }

        if (param > (uint)-1) {
            errno = EACCES;
            return -1;
        }
        break;

    default:
        param = 0;
    }

    ret = _fcntl(fd, cmd, param);

    switch (cmd)
    {
    case F_DUPFD:
    case F_GETFD:
    case F_GETFL:
    case F_GETOWN:
    case F_DUPFD_CLOEXEC:
        break;
    default:
    if (-1 != ret)
    {
        ret = 0;
    } 
    else
    {
    }	
    break;
    }

    return ret;
}

