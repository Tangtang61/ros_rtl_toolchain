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
[libmmap_svc.c] - SVC interface library (Mmap)
****************************************************************************/

#include <svc/svc_if.h>
#include <svc/svc_if_mmap.h>

void* mmap(void *addr, size_t len, int prot, int flags, int fno, off_t offs)
{
	svc_packet_mmap_mmap_t	p;
	void	*map;

	p.id	= SVCID_MMAP_MMAP;
	p.addr	= addr;
	p.len	= len;
	p.prot	= prot;
	p.flags	= flags;
	p.fno	= fno;
	p.offs	= offs;
	p.map	= &map;
	(void)call_svc((void*)&p);
	return *p.map;
}

int munmap(void *addr, size_t len)
{
	svc_packet_mmap_munmap_t	p;

	p.id	= SVCID_MMAP_MUNMAP;
	p.addr	= addr;
	p.len	= len;
	return (int)call_svc((void*)&p);
}

int msync(void *addr, size_t len, int flags)
{
	svc_packet_mmap_msync_t	p;

	p.id	= SVCID_MMAP_MSYNC;
	p.addr	= addr;
	p.len	= len;
	p.flags	= flags;
	return (int)call_svc((void*)&p);
}

int mlock(const void *addr, size_t len)
{
	svc_packet_mmap_mlock_t	p;

	p.id	= SVCID_MMAP_MLOCK;
	p.addr	= addr;
	p.len	= len;
	return (int)call_svc((void*)&p);
}

int munlock(const void *addr, size_t len)
{
	svc_packet_mmap_munlock_t	p;

	p.id	= SVCID_MMAP_MUNLOCK;
	p.addr	= addr;
	p.len	= len;
	return (int)call_svc((void*)&p);
}

int mlockall(int flags)
{
	svc_packet_mmap_mlockall_t	p;

	p.id	= SVCID_MMAP_MLOCKALL;
	p.flags	= flags;
	return (int)call_svc((void*)&p);
}

int munlockall(void)
{
	svc_packet_mmap_munlockall_t	p;

	p.id	= SVCID_MMAP_MUNLOCKALL;
	return (int)call_svc((void*)&p);
}

int mprotect(void *addr, size_t len, int prot)
{
	svc_packet_mmap_mprotect_t	p;

	p.id	= SVCID_MMAP_MPROTECT;
	p.addr	= addr;
	p.len	= len;
	p.prot	= prot;
	return (int)call_svc((void*)&p);
}

int shm_open(const char *name, int oflag, mode_t mode)
{
	svc_packet_mmap_shm_open_t	p;

	p.id	= SVCID_MMAP_SHM_OPEN;
	p.name	= name;
	p.oflag	= oflag;
	p.mode	= mode;
	return (int)call_svc((void*)&p);
}

int shm_unlink(const char *name)
{
	svc_packet_mmap_shm_unlink_t	p;

	p.id	= SVCID_MMAP_SHM_UNLINK;
	p.name	= name;
	return (int)call_svc((void*)&p);
}
