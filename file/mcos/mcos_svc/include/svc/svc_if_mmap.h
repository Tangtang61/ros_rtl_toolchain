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
[svc_if_mmap.h] - SVC interface library header (Mmap)
****************************************************************************/

#ifndef SVC_IF_MMAP_H
#define SVC_IF_MMAP_H

#include <svc/svc_if.h>
#include <sys/mman.h>

/*
 * SVC Function ID
 */
#define SVCID_MMAP_XXX			(SVCID_MMAP | 0x00000000) /* Do not use bit31-16 */
#define SVCID_MMAP_MMAP			(SVCID_MMAP | 0x00000001)	/* mmap()			*/
#define SVCID_MMAP_MUNMAP		(SVCID_MMAP | 0x00000002)	/* munmap()			*/
#define SVCID_MMAP_MSYNC		(SVCID_MMAP | 0x00000003)	/* msync()			*/
#define SVCID_MMAP_MLOCK		(SVCID_MMAP | 0x00000004)	/* mlock()			*/
#define SVCID_MMAP_MUNLOCK		(SVCID_MMAP | 0x00000005)	/* munlock()		*/
#define SVCID_MMAP_MLOCKALL		(SVCID_MMAP | 0x00000006)	/* mlockall()		*/
#define SVCID_MMAP_MUNLOCKALL	(SVCID_MMAP | 0x00000007)	/* munlockall()		*/
#define SVCID_MMAP_MPROTECT		(SVCID_MMAP | 0x00000008)	/* mprotect()		*/

#define SVCID_MMAP_SHM_OPEN		(SVCID_MMAP | 0x00000010)	/* shm_open()		*/
#define SVCID_MMAP_SHM_UNLINK	(SVCID_MMAP | 0x00000011)	/* shm_unlink()		*/

/*
 * SVC Parameter Packet
 */
/* mmap() */
typedef struct {
	int		id;
	void	*addr;
	size_t	len;
	int		prot;
	int		flags;
	int		fno;
	off_t	offs;
	void	**map;
} svc_packet_mmap_mmap_t;

/* munmap() */
typedef struct {
	int		id;
	void	*addr;
	size_t	len;
} svc_packet_mmap_munmap_t;

/* msync() */
typedef struct {
	int		id;
	void	*addr;
	size_t	len;
	int		flags;
} svc_packet_mmap_msync_t;

/* mlock() */
typedef struct {
	int			id;
	const void	*addr;
	size_t		len;
} svc_packet_mmap_mlock_t;

/* munlock() */
typedef struct {
	int			id;
	const void	*addr;
	size_t		len;
} svc_packet_mmap_munlock_t;

/* mlockall() */
typedef struct {
	int			id;
	int			flags;
} svc_packet_mmap_mlockall_t;

/* munlockall() */
typedef struct {
	int			id;
} svc_packet_mmap_munlockall_t;

/* mprotect() */
typedef struct {
	int			id;
	void		*addr;
	size_t		len;
	int			prot;
} svc_packet_mmap_mprotect_t;

/* shm_open() */
typedef struct {
	int			id;
	const char	*name;
	int			oflag;
	mode_t		mode;
} svc_packet_mmap_shm_open_t;

/* shm_unlink() */
typedef struct {
	int			id;
	const char	*name;
} svc_packet_mmap_shm_unlink_t;

/* List of Process APIs */
typedef union {
	int			id;
	svc_packet_mmap_mmap_t			param_mmap_mmap_;
	svc_packet_mmap_munmap_t		param_mmap_munmap_;
	svc_packet_mmap_msync_t			param_mmap_msync_;
	svc_packet_mmap_mlock_t			param_mmap_mlock_;
	svc_packet_mmap_munlock_t		param_mmap_munlock_;
	svc_packet_mmap_mlockall_t		param_mmap_mlockall_;
	svc_packet_mmap_munlockall_t	param_mmap_munlockall_;
	svc_packet_mmap_mprotect_t		param_mmap_mprotect_;
	svc_packet_mmap_shm_open_t		param_mmap_shm_open_;
	svc_packet_mmap_shm_unlink_t	param_mmap_shm_unlink_;
} svc_packet_mmap_t;

#endif	/* #ifndef SVC_IF_MMAP_H */
