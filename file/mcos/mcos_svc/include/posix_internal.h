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
posix_internal.h   POSIX Layer   Internal definitions
============================================================================*/
#ifndef __POSIX_INTERNAL_H__
#define __POSIX_INTERNAL_H__

/*
 * Generic double-linked list.
 * List heads use the same type.
 * Empty list points to itself
 */
typedef struct posix_list posix_list_t;
struct posix_list
{
    posix_list_t* next;     /* Next list element */
    posix_list_t* prev;     /* Previous list element */
};

/* Pthread user space descriptor */
typedef struct pthread_user pthread_user_t;
struct pthread_user
{
    unsigned char*              stackbeg;
    unsigned char*              stackend;
    pthread_t                   pthread;
    struct _pthread_cleanup*    anchor;
};

/* Spawn file actions */
typedef union file_actions file_actions_t;
union file_actions
{
    struct file_close
    {
        int     type;       /* Action type */
        int     fildes;     /* File descriptor */
    } close;
    struct file_dup2
    {
        int     type;       /* Action type */
        int     fildes;     /* Original file descriptor */
        int     newdes;     /* New file descriptor */
    } dup2;
    struct file_open
    {
        int     type;       /* Action type */
        int     fildes;     /* File descriptor to use */
        int     oflags;     /* Open flags */
        mode_t  mode;       /* File mode */
     /* File path follows */
    } open;
};

/*
 * Process user space descriptor
 *  - "destr"     : &array [PTHREAD_KEYS_MAX + 1]
 *  - "data"      : &array [thread max][PTHREAD_KEYS_MAX]
 *  - "threads"   : &array [thread max]
 *  - "mutexlist" : &array [thread max]
 */
typedef struct proc_user proc_user_t;
struct proc_user
{
    void            (**destr)(void*);   /* TS data destructors      */
    void**          data;               /* All threads TS data      */
    pthread_user_t* threads;            /* User space threads array */
    posix_list_t*   mutexlist;          /* Robust mutexes list      */
};

#endif /* __POSIX_INTERNAL_H__ */
