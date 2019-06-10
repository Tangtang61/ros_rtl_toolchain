/*  $NetBSD: lcl_p.h,v 1.1.1.3.4.1 2007/05/17 00:39:57 jdc Exp $    */

/*
 * Copyright (c) 2004 by Internet Systems Consortium, Inc. ("ISC")
 * Copyright (c) 1996,1999 by Internet Software Consortium.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * Id: lcl_p.h,v 1.2.18.1 2005/04/27 05:01:02 sra Exp
 */

/*! \file
 * \brief
 * lcl_p.h - private include file for the local accessor functions.
 */

#ifndef _LCL_P_H_INCLUDED
#define _LCL_P_H_INCLUDED

/*
 * Object state.
 */
struct lcl_p {
    struct __res_state *    res;
    void                    (*free_res)(void *);
};

/*
 * Externs.
 */

extern struct irs_acc * irs_lcl_acc(const char * options);
extern struct irs_gr *  irs_lcl_gr(struct irs_acc * this);
extern struct irs_pw *  irs_lcl_pw(struct irs_acc * this);
extern struct irs_sv *  irs_lcl_sv(struct irs_acc * this);
extern struct irs_pr *  irs_lcl_pr(struct irs_acc * this);
extern struct irs_ho *  irs_lcl_ho(struct irs_acc * this);
extern struct irs_nw *  irs_lcl_nw(struct irs_acc * this);
extern struct irs_ng *  irs_lcl_ng(struct irs_acc * this);

#endif /*_LCL_P_H_INCLUDED*/
