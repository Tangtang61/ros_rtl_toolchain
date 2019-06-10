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
 sys/ioctls.h  IOCTL request code definitions (system common commands)
============================================================================*/

#ifndef _SYS_IOCTLS_H_
#define _SYS_IOCTLS_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

/* File ioctls */
#define FIONBIO     _IOC((unsigned)-1, 0)
#define FIONREAD    _IOC((unsigned)-1, 1)

/* Terminal ioctls */
#define TIOCINQ     FIONREAD
#define TIOCOUTQ    _IOC((unsigned)-1, 2)

/* Socket ioctls */
#define SIOCINQ     TIOCINQ
#define SIOCOUTQ    TIOCOUTQ

#define SIOCGIFCONF   _IOC_INOUT((unsigned)-1, 36)
#define SIOCGIFHWADDR _IOC_INOUT((unsigned)-1, 38)

__END_DECLS

#endif  /* _SYS_IOCTLS_H_ */
