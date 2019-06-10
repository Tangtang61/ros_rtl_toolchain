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
[ termios.c ]
****************************************************************************/
#include <unistd.h>
#include <termios.h>
#include <stdio.h>

speed_t cfgetospeed (const struct termios *__termios_p)
{
    printf("cfgetospeed(): eMCOS does not support this POSIX API.\n");
    return B115200;
}

speed_t cfgetispeed (const struct termios *__termios_p)
{
    printf("cfgetispeed(): eMCOS does not support this POSIX API.\n");
    return B115200;
}

int cfsetospeed (struct termios *__termios_p, speed_t __speed)
{
    printf("cfsetospeed(): eMCOS does not support this POSIX API.\n");
    return -1;
}

int cfsetispeed (struct termios *__termios_p, speed_t __speed)
{
    printf("cfsetispeed(): eMCOS does not support this POSIX API.\n");
    return -1;
}

int cfsetspeed (struct termios *__termios_p, speed_t __speed)
{
    printf("cfsetspeed(): eMCOS does not support this POSIX API.\n");
    return -1;
}

int tcgetattr (int __fd, struct termios *__termios_p)
{
    printf("tcgetattr(): eMCOS does not support this POSIX API.\n");
    return -1;
}

int tcsetattr (int __fd, int __optional_actions, const struct termios *__termios_p)
{
    printf("tcsetattr(): eMCOS does not support this POSIX API.\n");
    return -1;
}

int tcsendbreak (int __fd, int __duration)
{
    printf("tcsendbreak(): eMCOS does not support this POSIX API.\n");
    return -1;
}
