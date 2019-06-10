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
[svc_if.h] - SVC interface library common header
****************************************************************************/

#ifndef SVC_IF_H
#define SVC_IF_H

/* SWI number */
#define MCOS_CALL_SVC	(0x11)
#define MCOS_MSG_SVC	(0x12)

/* SVC ID */
#define SVCID_MASK              (0xFFFF0000U)
#define SVCID_SHIFT             (16)

#define SVCID_MCOS              (0x00010000)
#define SVCID_LFS               (0x00020000)
#define SVCID_PTHREAD           (0x00030000)
#define SVCID_PROCESS           (0x00040000)
#define SVCID_MMAP              (0x00050000)
#define SVCID_TIME              (0x00060000)
#define SVCID_SEM               (0x00070000)
#define SVCID_SIGNAL            (0x00080000)
#define SVCID_PIPE              (0x00090000)
#define SVCID_SOCKET            (0x000a0000)
#define SVCID_MQ                (0x000b0000)
#define SVCID_TIMER             (0x000c0000)
#define SVCID_AIO               (0x000d0000)

#ifndef _in_asm_source_

extern int call_svc(void* packet);

/* Common part of SVC packet  */
typedef union {
	int						id;
} svc_packet_t;

#endif /* _in_asm_source_ */

#endif	/* #ifndef SVC_IF_H */
