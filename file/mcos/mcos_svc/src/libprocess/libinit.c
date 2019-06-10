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
[libinit.c] - Initialization of library
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

extern int _init_liblock(void);
extern int _init_memalloc(void);
extern int libposix_init(void);
extern int _libc_lock_error;
extern void call_atexit_func(void);

int _startup_error __attribute__ ((weak));

void _init_library(
    void (*init)(void),
    void (*fini)(void))
{
    int err;

    err = _init_liblock();
    if (err < 0) {
        _startup_error = err;
    } else {
        err = _init_memalloc();
        if (err < 0) {
            _startup_error = err;
        }

        err = libposix_init();
        if (err < 0) {
            _startup_error = err;
        } else {
            _libc_lock_error = 0;
            atexit(fini);
            if (_libc_lock_error != 0) {
                _startup_error = _libc_lock_error;
                call_atexit_func();
            }
        }
    }
}
