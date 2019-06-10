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
[signal.c] - MCOS POSIX signal API
****************************************************************************/
#include <signal.h>

/* signal() API */
#if defined (__ghs__)
void (*_signal(int sig, void (*hdl)(int)))(int)
#else
void (*signal(int sig, void (*hdl)(int)))(int)
#endif
{
	struct sigaction act;
	struct sigaction old;

 /* Prepare signal action */
	act.sa_handler = hdl;
	act.sa_flags = 0;
	act.sa_mask = 0;

 /* Try to set signal action */
	if (sigaction(sig, &act, &old) != 0)
	{
     /* Return special value; errno already set */
		return SIG_ERR;
	}

 /* Return previous signal handler */
	return old.sa_handler;
}
