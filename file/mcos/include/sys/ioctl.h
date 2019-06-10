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
 sys/ioctl.h  Logical File System (LFS) PFS/DEV IO control definitions
============================================================================*/

#ifndef _SYS_IOCTL_H_
#define _SYS_IOCTL_H_

#ifdef  __cplusplus
extern  "C" {
#endif

/* ioctl prototype */
int ioctl(int fildes, int request, ... /* arg */);

/*
 * Device command structure:
 *  bits 30-31  direction
 *  bits 29     (reserved, SBZ)
 *  bits 16-28  cmd group
 *  bits  0-15  command
 */
#define _IOC_DIR_NONE   0x00000000
#define _IOC_DIR_IN     0x40000000
#define _IOC_DIR_OUT    0x80000000
#define _IOC_DIR_INOUT  (_IOC_DIR_IN | _IOC_DIR_OUT)
#define _IOC_GRP_MASK   0x1fff
#define _IOC_GRP_SHFT   16
#define _IOC_CMD_MASK   0xffff
#define _IOC_CMD_SHFT   0

/* Generic macro to form device command */
#define _IOC_(_dir_, _grp_, _cmd_)                              \
            (   (_dir_)                                         \
              | (((_grp_) & _IOC_GRP_MASK) << _IOC_GRP_SHFT)    \
              | ((_cmd_) & _IOC_CMD_MASK) )

/* Useful macros to form directed commands */
#define _IOC(_grp_, _cmd_)          _IOC_(_IOC_DIR_NONE,  (_grp_), (_cmd_))
#define _IOC_IN(_grp_, _cmd_)       _IOC_(_IOC_DIR_IN,    (_grp_), (_cmd_))
#define _IOC_OUT(_grp_, _cmd_)      _IOC_(_IOC_DIR_OUT,   (_grp_), (_cmd_))
#define _IOC_INOUT(_grp_, _cmd_)    _IOC_(_IOC_DIR_INOUT, (_grp_), (_cmd_))

/*
 * TK Device command structure:
 * bits 30-31  direction
 * bits 29     attribute indicator (*1)
 * bits 16-28  data size
 * bits  0-15  data number
 * (*1): 1=attribute data 0=normal device event
 */
#define  _IOC_TKDEV_DIR_MASK        0x3
#define  _IOC_TKDEV_DIR_READ        _IOC_DIR_IN
#define  _IOC_TKDEV_DIR_WRITE       _IOC_DIR_OUT
#define  _IOC_TKDEV_DIR_SHFT        30
#define  _IOC_TKDEV_IND_MASK        0x1
#define  _IOC_TKDEV_IND_SHFT        29
#define  _IOC_TKDEV_EVTTYP_MASK     0x1fffffff
#define  _IOC_TKDEV_EVTTYP_SHFT     0
# define _IOC_TKDEV_SIZE_MASK       0x1fff
# define _IOC_TKDEV_SIZE_SHFT       16
# define _IOC_TKDEV_NUM_MASK        0xffff
# define _IOC_TKDEV_NUM_SHFT        0
#define  _IOC_TKDEV_ATTR_DIR_MASK   _IOC_TKDEV_DIR_MASK
#define  _IOC_TKDEV_ATTR_DIR_READ   _IOC_TKDEV_DIR_READ
#define  _IOC_TKDEV_ATTR_DIR_WRITE  _IOC_TKDEV_DIR_WRITE
#define  _IOC_TKDEV_ATTR_DIR_SHFT   _IOC_TKDEV_DIR_SHFT
#define  _IOC_TKDEV_ATTR_IND_MASK   _IOC_TKDEV_IND_MASK
#define  _IOC_TKDEV_ATTR_IND_SHFT   _IOC_TKDEV_IND_SHFT
#define  _IOC_TKDEV_ATTR_SIZE_MASK  _IOC_TKDEV_SIZE_MASK
#define  _IOC_TKDEV_ATTR_SIZE_SHFT  _IOC_TKDEV_SIZE_SHFT
#define  _IOC_TKDEV_ATTR_NUM_MASK   _IOC_TKDEV_NUM_MASK
#define  _IOC_TKDEV_ATTR_NUM_SHFT   _IOC_TKDEV_NUM_SHFT

#define  _EVTTYP_TKDEV_UNUSED_MASK  _IOC_TKDEV_IND_MASK
#define  _EVTTYP_TKDEV_UNUSED_SHFT  31
#define  _EVTTYP_TKDEV_TYPE_MASK1   _IOC_TKDEV_EVTTYP_MASK
#define  _EVTTYP_TKDEV_TYPE_SHF1    _IOC_TKDEV_EVTTYP_SHFT
#define  _EVTTYP_TKDEV_TYPE_MASK2   _IOC_TKDEV_DIR_MASK
#define  _EVTTYP_TKDEV_TYPE_SHF2    _IOC_TKDEV_IND_SHFT

#define _IOC_TKDEV_ATTR_MAKE_IND_SIZE(_size_)                               \
            (   (_size_ & _IOC_TKDEV_ATTR_SIZE_MASK)                        \
              | (_IOC_TKDEV_ATTR_IND_MASK                                   \
                  << (_IOC_TKDEV_ATTR_IND_SHFT-_IOC_TKDEV_ATTR_SIZE_SHFT)) )

/* Useful macros to form directed commands for read/write TK device attribute data */
#define _IOC_TKDEV_ATTR_RD(_size_, _datano_)                                        \
            (   (_IOC_TKDEV_ATTR_DIR_READ)                                          \
              | (_IOC_TKDEV_ATTR_IND_MASK << _IOC_TKDEV_ATTR_IND_SHFT)              \
              | ((_size_ & _IOC_TKDEV_ATTR_SIZE_MASK) << _IOC_TKDEV_ATTR_SIZE_SHFT) \
              | ((_datano_ & _IOC_TKDEV_ATTR_NUM_MASK) << _IOC_TKDEV_ATTR_NUM_SHFT) )
#define _IOC_TKDEV_ATTR_WR(_size_, _datano_)                                        \
            (   (_IOC_TKDEV_ATTR_DIR_WRITE)                                         \
              | (_IOC_TKDEV_ATTR_IND_MASK << _IOC_TKDEV_ATTR_IND_SHFT)              \
              | ((_size_ & _IOC_TKDEV_ATTR_SIZE_MASK) << _IOC_TKDEV_ATTR_SIZE_SHFT) \
              | ((_datano_ & _IOC_TKDEV_ATTR_NUM_MASK) << _IOC_TKDEV_ATTR_NUM_SHFT) )

/* Useful macros to convert command format between POSIX and TK device */
#define _IOC_TKDEV_POSIX2EVTTYP(_request_)                                          \
            (   (_request_ & (_IOC_TKDEV_EVTTYP_MASK << _IOC_TKDEV_EVTTYP_SHFT))    \
              | (((_request_ >> _IOC_TKDEV_DIR_SHFT) & _IOC_TKDEV_DIR_MASK)         \
                  << _IOC_TKDEV_IND_SHFT) )
#define _IOC_TKDEV_EVTTYP2POSIX(_evttyp_)                                           \
            (   ((_evttyp_ & (_EVTTYP_TKDEV_TYPE_MASK1 << _EVTTYP_TKDEV_TYPE_SHF1)) \
                  << _IOC_TKDEV_EVTTYP_SHFT)                                        \
              | (((_evttyp_ >> _EVTTYP_TKDEV_TYPE_SHF2) & _EVTTYP_TKDEV_TYPE_MASK2) \
                  << _IOC_TKDEV_DIR_SHFT) )

#ifdef  __cplusplus
}
#endif

/*
 * include IOCTL request code definitions
 */
#include <sys/ioctls.h>

#endif  /* _SYS_IOCTL_H_ */
