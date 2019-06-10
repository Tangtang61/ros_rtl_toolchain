/*
   Copyright (C) 2019 By eSOL Co.,Ltd. Tokyo, Japan
   Modified to work with eMCOS.
*/

#ifndef	_SYS__DEFAULT_FCNTL_H_
#ifdef __cplusplus
extern "C" {
#endif
#define	_SYS__DEFAULT_FCNTL_H_
#include <_ansi.h>
#include <sys/cdefs.h>
#define	_FOPEN		(-1)	/* from sys/file.h, kernel use only */
#define	_FREAD		0x0001	/* read enabled */
#define	_FWRITE		0x0002	/* write enabled */
#define	_FAPPEND	0x0008	/* append (writes guaranteed at the end) */
#define	_FMARK		0x0010	/* internal; mark during gc() */
#define	_FDEFER		0x0020	/* internal; defer for next gc pass */
#define	_FASYNC		0x0040	/* signal pgrp when data ready */
#define	_FSHLOCK	0x0080	/* BSD flock() shared lock present */
#define	_FEXLOCK	0x0100	/* BSD flock() exclusive lock present */
#define	_FCREAT		0x0200	/* open with file create */
#define	_FTRUNC		0x0400	/* open with truncation */
#define	_FEXCL		0x0800	/* error on open if file exists */
#define	_FNBIO		0x1000	/* non blocking I/O (sys5 style) */
#define	_FSYNC		0x2000	/* do all writes synchronously */
#define	_FNONBLOCK	0x4000	/* non blocking I/O (POSIX style) */
#define	_FNDELAY	_FNONBLOCK	/* non blocking I/O (4.2 style) */
#define	_FNOCTTY	0x8000	/* don't assign a ctty on this open */

/*
 * Flag values for open(2) and fcntl(2)
 * The kernel adds 1 to the open modes to turn it into some
 * combination of FREAD and FWRITE.
 */
#define O_RDONLY    0x00000001  /* open for reading only */
#define O_WRONLY    0x00000002  /* open for writing only */
#define O_RDWR      0x00000003  /* open for reading and writing */

#define O_ACCMODE   0x00000003  /* mask for above modes */

/*
 * Kernel encoding of open mode; separate read and write bits that are
 * independently testable: 1 greater than the above.
 *
 * XXX
 * FREAD and FWRITE are excluded from the #ifdef _KERNEL so that TIOCFLUSH,
 * which was documented to use FREAD/FWRITE, continues to work.
 */
#define FREAD       0x00000001
#define FWRITE      0x00000002

#define O_NONBLOCK  0x00000004  /* no delay */
#define O_APPEND    0x00000008  /* set append mode */
#define O_SHLOCK    0x00000010  /* open with shared file lock */
#define O_EXLOCK    0x00000020  /* open with exclusive file lock */
#define O_ASYNC     0x00000040  /* signal pgrp when data ready */

#define O_SYNC      0x00000080  /* synchronous writes */

#define O_CREAT     0x00000200  /* create if nonexistent */
#define O_TRUNC     0x00000400  /* truncate to zero length */
#define O_EXCL      0x00000800  /* error if already exists */

#define O_DSYNC     0x00001000  /* write: I/O data completion */
#define O_RSYNC     0x00002000  /* read: I/O completion as for write */

/* defined by POSIX 1003.1; BSD default, but required to be bitwise distinct */
#define O_NOCTTY    0x00008000  /* don't assign controlling terminal */

/* New open flags in POSIX Issue 7 */
#define O_CLOEXEC   0x00010000  /* set close-on-exec flag */

#define O_ALT_IO    0x00040000  /* use alternate i/o semantics */

#define FAPPEND     O_APPEND    /* kernel/compat */
#define FASYNC      O_ASYNC     /* kernel/compat */
#define O_FSYNC     O_SYNC      /* compat */
#define FNDELAY     O_NONBLOCK  /* compat */
#define O_NDELAY    O_NONBLOCK  /* compat */

#define F_DUPFD         0       /* duplicate file descriptor */
#define F_GETFD         1       /* get file descriptor flags */
#define F_SETFD         2       /* set file descriptor flags */
#define F_GETFL         3       /* get file status flags */
#define F_SETFL         4       /* set file status flags */

#define F_GETOWN        5       /* get SIGIO/SIGURG proc/pgrp */
#define F_SETOWN        6       /* set SIGIO/SIGURG proc/pgrp */

#define F_GETLK         7       /* get record locking information */
#define F_SETLK         8       /* set record locking information */
#define F_SETLKW        9       /* F_SETLK; wait if blocked */
#define F_DUPFD_CLOEXEC 10      /* duplicate file descriptor with FD_CLOEXEC */

/* file descriptor flags (F_GETFD, F_SETFD) */
#define FD_CLOEXEC      1       /* close-on-exec flag */

/* record locking flags (F_GETLK, F_SETLK, F_SETLKW) */
#define F_RDLCK         1       /* shared or read lock */
#define F_UNLCK         2       /* unlock */
#define F_WRLCK         3       /* exclusive or write lock */

/* Constants for fcntl's passed to the underlying fs - like ioctl's. */
#define F_PARAM_MASK    0xfff
#define F_PARAM_LEN(x)  (((x) >> 16) & F_PARAM_MASK)
#define F_PARAM_MAX     4095
#define F_FSCTL         (int)0x80000000 /* This fcntl goes to the fs */
#define F_FSVOID        (int)0x40000000 /* no parameters */
#define F_FSOUT         (int)0x20000000 /* copy out parameter */
#define F_FSIN          (int)0x10000000 /* copy in parameter */
#define F_FSINOUT       (F_FSIN | F_FSOUT)
#define F_FSDIRMASK     (int)0x70000000 /* mask for IN/OUT/VOID */
#define F_FSPRIV        (int)0x00008000 /* command is fs-specific */

/*
 * Define command macros for operations which, if implemented, must be
 * the same for all fs's.
 */
#define _FCNO(c)        _FCN(F_FSVOID,  (c), 0)
#define _FCNR(c, t)     _FCN(F_FSIN,    (c), (int)sizeof(t))
#define _FCNW(c, t)     _FCN(F_FSOUT,   (c), (int)sizeof(t))
#define _FCNRW(c, t)    _FCN(F_FSINOUT, (c), (int)sizeof(t))

#define _FCNO_FSPRIV(c)     _FCN_FSPRIV(F_FSVOID,   (c), 0)
#define _FCNR_FSPRIV(c, t)  _FCN_FSPRIV(F_FSIN,     (c), (int)sizeof(t))
#define _FCNW_FSPRIV(c, t)  _FCN_FSPRIV(F_FSOUT,    (c), (int)sizeof(t))
#define _FCNRW_FSPRIV(c, t) _FCN_FSPRIV(F_FSINOUT,  (c), (int)sizeof(t))

#if __BSD_VISIBLE
/* lock operations for flock(2) */
#define LOCK_SH     0x01        /* shared file lock */
#define LOCK_EX     0x02        /* exclusive file lock */
#define LOCK_NB     0x04        /* don't block when locking */
#define LOCK_UN     0x08        /* unlock file */
#endif

/*#include <sys/stdtypes.h>*/

#include <pthread.h>
/*
 * Advisory file segment locking data type -
 * information passed to system by user
 */
struct flock {
  off_t   l_start;    /* starting offset */
  off_t   l_len;      /* len = 0 means until end of file */
  pid_t   l_pid;      /* lock owner */
  pthread_t l_tid;    /* lock owner thread */
  short   l_type;     /* lock type: read/write, etc. */
  short   l_whence;   /* type of l_start */
};

#if __MISC_VISIBLE
/* extended file segment locking set data type */
struct eflock {
	short	l_type;		/* F_RDLCK, F_WRLCK, or F_UNLCK */
	short	l_whence;	/* flag to choose starting offset */
	long	l_start;	/* relative offset, in bytes */
	long	l_len;		/* length, in bytes; 0 means lock to EOF */
	short	l_pid;		/* returned with F_GETLK */
	short	l_xxx;		/* reserved for future use */
	long	l_rpid;		/* Remote process id wanting this lock */
	long	l_rsys;		/* Remote system id wanting this lock */
};
#endif	/* __MISC_VISIBLE */

#include <sys/types.h>
#include <sys/stat.h>		/* sigh. for the mode bits for open/creat */

extern int open _PARAMS ((const char *, int, ...));
#if __ATFILE_VISIBLE
extern int openat _PARAMS ((int, const char *, int, ...));
#endif
extern int creat _PARAMS ((const char *, mode_t));
extern int fcntl _PARAMS ((int, int, ...));
#if __BSD_VISIBLE
extern int flock _PARAMS ((int, int));
#endif
#if __GNU_VISIBLE
#include <sys/time.h>
extern int futimesat _PARAMS ((int, const char *, const struct timeval *));
#endif

/* Provide _<systemcall> prototypes for functions provided by some versions
   of newlib.  */
#ifdef _COMPILING_NEWLIB
extern int _open _PARAMS ((const char *, int, ...));
extern int _fcntl _PARAMS ((int, int, ...));
#ifdef __LARGE64_FILES
extern int _open64 _PARAMS ((const char *, int, ...));
#endif
#endif

#ifdef __cplusplus
}
#endif
#endif	/* !_SYS__DEFAULT_FCNTL_H_ */
