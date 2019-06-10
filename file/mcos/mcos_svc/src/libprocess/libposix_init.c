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
 libposix_init.c   POSIX Layer libposix initializer
============================================================================*/

#include <stdio.h>
#include <unistd.h>

/* FIXME!
 * These parameters should be configurable
 * and should be obtained from kernel via SVC
 */
#define DLMALLOC_TRIM_THRESHOLD     (2*1024*1024)
#define DLMALLOC_GRANULARITY        (512*1024)
#define DLMALLOC_MMAP_THRESHOLD     (256*1024)

enum {
    POSIX_SYSINFO_DLMALLOC_TRIM_THRESHOLD = 0,
    POSIX_SYSINFO_DLMALLOC_GRANULARITY,
    POSIX_SYSINFO_DLMALLOC_MMAP_THRESHOLD,
    POSIX_SYSINFO_NUM
};

int posix_sysinfo[POSIX_SYSINFO_NUM];

/* Setip configurations for dlmalloc() */
int init_posix_sysinfo(void)
{
    posix_sysinfo[POSIX_SYSINFO_DLMALLOC_TRIM_THRESHOLD] = DLMALLOC_TRIM_THRESHOLD;
    posix_sysinfo[POSIX_SYSINFO_DLMALLOC_GRANULARITY]    = DLMALLOC_GRANULARITY;
    posix_sysinfo[POSIX_SYSINFO_DLMALLOC_MMAP_THRESHOLD] = DLMALLOC_MMAP_THRESHOLD;
    return 0;
}

/* Refer configurations for dlmalloc() */
int posix_malloc_get_config_trim_threshold(void)
{
    return posix_sysinfo[POSIX_SYSINFO_DLMALLOC_TRIM_THRESHOLD];
}
int posix_malloc_get_config_granularity(void)
{
    return posix_sysinfo[POSIX_SYSINFO_DLMALLOC_GRANULARITY];
}
int posix_malloc_get_config_mmap_threshold(void)
{
    return posix_sysinfo[POSIX_SYSINFO_DLMALLOC_MMAP_THRESHOLD];
}

/* Set up dlmalloc() parameters */
int init_dlmalloc(void)
{
    /* mallopt() options, see dlmalloc.c */
    extern int mallopt(int param_number, int value) __attribute__ ((weak));
    #define M_TRIM_THRESHOLD    (-1)
    #define M_GRANULARITY       (-2)
    #define M_MMAP_THRESHOLD    (-3)

    int value;

    value = posix_malloc_get_config_trim_threshold();
    (void)mallopt(M_TRIM_THRESHOLD, value);

    value = posix_malloc_get_config_granularity();
    (void)mallopt(M_GRANULARITY, value);

    value = posix_malloc_get_config_mmap_threshold();
    (void)mallopt(M_MMAP_THRESHOLD, value);

    return 0;
}

int libposix_init(void)
{
    return 0;
}
