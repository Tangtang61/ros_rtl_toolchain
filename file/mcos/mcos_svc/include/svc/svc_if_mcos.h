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
[svc_if_mcos.h] - SVC interface library header (eMCOS Native)
****************************************************************************/

#ifndef SVC_IF_MCOS_H
#define SVC_IF_MCOS_H

#include <svc/svc_if.h>

/*
 * SVC Function ID
 */
#define SVCID_MCOS_XXX				 (SVCID_MCOS | 0x00000000) /* Do not use bit31-16 */
#define SVCID_GET_ERRNO_ADDR		 (SVCID_MCOS | 0x000000FF)	/* get_errno_addr()			*/

#ifndef _in_asm_source_

/*
 * SVC Parameter Packet
 */
#include <mcos/mcos.h>

/* get_errno_addr() */
typedef struct {
	int				id;
	int**			addr;
} svc_packet_get_errno_addr_t;

#endif /* _in_asm_source_ */
#endif	/* #ifndef SVC_IF_MCOS_H */
