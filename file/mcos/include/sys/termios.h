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
 sys/termios.h
****************************************************************************/

#ifndef _SYS_TERMIOS_H_
#define _SYS_TERMIOS_H_

#include <sys/features.h>

__BEGIN_DECLS
typedef unsigned int    speed_t;
typedef unsigned int    tcflag_t;
typedef unsigned char   cc_t;

#define _HAVE_STRUCT_TERMIOS_C_ISPEED 1
#define _HAVE_STRUCT_TERMIOS_C_OSPEED 1
#define NCCS 32
struct termios
{
    tcflag_t c_iflag;
    tcflag_t c_oflag;
    tcflag_t c_cflag;
    tcflag_t c_lflag;
    cc_t     c_line;
    cc_t     c_cc[NCCS];
    speed_t  c_ispeed;
    speed_t  c_ospeed;
};

#define VTIME 5
#define VMIN 6

#define IGNBRK   0000001
#define BRKINT   0000002
#define IGNPAR   0000004
#define PARMRK   0000010
#define INPCK    0000020
#define ISTRIP   0000040
#define INLCR    0000100
#define IGNCR    0000200
#define ICRNL    0000400
#define IUCLC    0001000
#define IXON     0002000
#define IXANY    0004000
#define IXOFF    0010000
#define IMAXBEL  0020000
#define IUTF8    0040000

#define B0       0000000
#define B50      0000001
#define B75      0000002
#define B110     0000003
#define B134     0000004
#define B150     0000005
#define B200     0000006
#define B300     0000007
#define B600     0000010
#define B1200    0000011
#define B1800    0000012
#define B2400    0000013
#define B4800    0000014
#define B9600    0000015
#define B19200   0000016
#define B38400   0000017
#define B57600   0010001
#define B115200  0010002
#define B230400  0010003

#define CSIZE    0000060
#define CS5      0000000
#define CS6      0000020
#define CS7      0000040
#define CS8      0000060
#define CSTOPB   0000100
#define CREAD    0000200
#define PARENB   0000400
#define PARODD   0001000
#define HUPCL    0002000
#define CLOCAL   0004000

#define ISIG     0000001
#define ICANON   0000002
#define IEXTEN   0100000

#define OPOST    0000001

#define ECHO     0000010
#define ECHONL   0000100

#define TCSANOW  0

extern speed_t cfgetospeed (const struct termios *__termios_p);
extern speed_t cfgetispeed (const struct termios *__termios_p);
extern int cfsetospeed (struct termios *__termios_p, speed_t __speed);
extern int cfsetispeed (struct termios *__termios_p, speed_t __speed);

#ifdef _BSD_SOURCE
extern int cfsetspeed (struct termios *__termios_p, speed_t __speed);
#endif

extern int tcgetattr (int __fd, struct termios *__termios_p);
extern int tcsetattr (int __fd, int __optional_actions, const struct termios *__termios_p);
extern int tcsendbreak (int __fd, int __duration);

__END_DECLS

#endif /* _SYS_TERMIOS_H_ */

