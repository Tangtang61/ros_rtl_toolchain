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
[mcos_svc.c] - SVC interface library (eMCOS Native)
****************************************************************************/

#include <svc/svc_if.h>
#include <svc/svc_if_mcos.h>

int *get_errno_addr(void)
{
	svc_packet_get_errno_addr_t	p;
	int		*addr;

	p.id	= SVCID_GET_ERRNO_ADDR;
	p.addr	= &addr;

	(void)call_svc((void*)&p);
	return *p.addr;
}


extern const int	___mcos_cfg_hclid;
extern const int	___mcos_cfg_cp_hcl_max;
extern const int	___mcos_cfg_cc_count;
mcos_bool_t mcos_is_validlcid(const mcos_id_t lcid)
{
    int mcos_base_lcid = (((___mcos_cfg_hclid - 1) * ___mcos_cfg_cp_hcl_max) + 1);
    return (mcos_bool_t)((lcid >= mcos_base_lcid) && (lcid < (mcos_base_lcid + ___mcos_cfg_cc_count)));
}

