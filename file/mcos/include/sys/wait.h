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
 sys/wait.h   POSIX Layer  Process wait definitions
============================================================================*/
#ifndef __SYS_WAIT_H__
#define __SYS_WAIT_H__

#include <sys/types.h>

#ifdef	__cplusplus
extern	"C"	{
#endif

 /* waitpid() Options */
#define WNOHANG      1    /* Do not hang if no status is available */
#define WCONTINUED   2    /* Report status of continued child process */
#define WUNTRACED    4    /* Report status of stopped child process */

 /* Return exit status */
#define WEXITSTATUS(_sta_)  ((_sta_) & 0xff) 
 /* True if child exited normally */
#define WIFEXITED(_sta_)    ((((_sta_) >> 8) & 0xe0) == 0)
 /* True if child exited due to uncaught signal */
#define WIFSIGNALED(_sta_)  ((((_sta_) >> 8) & 0x80) != 0)
 /* True if child has been continued */
#define WIFCONTINUED(_sta_) ((((_sta_) >> 8) & 0x40) != 0)
 /* True if child is currently stopped */
#define WIFSTOPPED(_sta_)   ((((_sta_) >> 8) & 0x20) != 0)
 /* Return signal number that caused process to stop */
#define WSTOPSIG(_sta_)     ((((_sta_) >> 8) & 0x1f) + 1)
 /* Return signal number that caused process to terminate */
#define WTERMSIG(_sta_)     ((((_sta_) >> 8) & 0x1f) + 1)

 /* Prototyps */
pid_t wait(int *);
pid_t waitpid(pid_t, int *, int);

#ifdef	__cplusplus
}
#endif

#endif
