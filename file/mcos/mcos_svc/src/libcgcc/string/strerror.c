/*  $NetBSD: strerror.c,v 1.11 1998/11/15 17:21:49 christos Exp $   */

/*
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *  This product includes software developed by the University of
 *  California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */



#include <sys/cdefs.h>
#if defined(LIBC_SCCS) && !defined(lint)
#if 0
static char *sccsid = "@(#)strerror.c   5.6 (Berkeley) 5/4/91";
#else
__RCSID("$NetBSD: strerror.c,v 1.11 1998/11/15 17:21:49 christos Exp $");
#endif
#endif /* LIBC_SCCS and not lint */

#include <string.h>
#include <limits.h>
#include "extern.h"
#include <errno.h>

/*
 * Since perror() is not allowed to change the contents of strerror()'s
 * static buffer, both functions supply their own buffers to the
 * internal function __strerror().
 */

__aconst char *
strerror(
    int num)
{
    static char buf[NL_TEXTMAX];

    /* LINTED const castaway */
    return (__aconst char *)__strerror(num, buf, sizeof(buf));
}

int 
strerror_r(
    int num,
    char *strerrbuf,
    size_t buflen)
{
    int          ret;
    const char*  msg;

    ret = ERANGE;
    if ((strerrbuf != NULL) && (buflen != 0))
    {
        /* If "num" is not valid error number (say, unknown error),
         * __strerror() will update buffer and return its pointer */
        msg = __strerror(num, strerrbuf, buflen);
        if (strlen(msg) < buflen)
        {
            if ((char*)msg != strerrbuf)
            {
                (void)strncpy(strerrbuf, msg, buflen);
                ret = 0;
            }
            else
            {
                /* This should be unknown error message */
                if (buflen > __strerror_erange_unknown(num))
                {
                    ret = 0;
                }
            }
        }
    }
    return ret;
}

