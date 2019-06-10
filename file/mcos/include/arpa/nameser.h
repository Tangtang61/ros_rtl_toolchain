/*  $NetBSD: nameser.h,v 1.1.1.3.4.1 2007/05/17 00:39:27 jdc Exp $  */

/*
 * Copyright (c) 1983, 1989, 1993
 *    The Regents of the University of California.  All rights reserved.
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

/*
 * Copyright (c) 2004 by Internet Systems Consortium, Inc. ("ISC")
 * Copyright (c) 1996-1999 by Internet Software Consortium.
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
 *  Id: nameser.h,v 1.7.18.1 2005/04/27 05:00:50 sra Exp
 */

#ifndef _ARPA_NAMESER_H_
#define _ARPA_NAMESER_H_

#include <sys/param.h>
#include <sys/types.h>
#include <sys/cdefs.h>

/*
 * Revision information.  This is the release date in YYYYMMDD format.
 * It can change every day so the right thing to do with it is use it
 * in preprocessor commands such as "#if (__NAMESER > 19931104)".  Do not
 * compare for equality; rather, use it to determine whether your libbind.a
 * contains a new enough lib/nameser/ to support the feature you need.
 */

#define __NAMESER   19991006    /* New interface version stamp. */
/*
 * Define constants based on RFC0883, RFC1034, RFC 1035
 */
#define NS_PACKETSZ     512     /* default UDP packet size */
#define NS_MAXDNAME     1025    /* maximum domain name */
#define NS_MAXMSG       65535   /* maximum message size */
#define NS_MAXCDNAME    255     /* maximum compressed domain name */
#define NS_MAXLABEL     63      /* maximum length of domain label */
#define NS_HFIXEDSZ     12      /* #/bytes of fixed data in header */
#define NS_QFIXEDSZ     4       /* #/bytes of fixed data in query */
#define NS_RRFIXEDSZ    10      /* #/bytes of fixed data in r record */
#define NS_INT32SZ      4       /* #/bytes of data in a u_int32_t */
#define NS_INT16SZ      2       /* #/bytes of data in a u_int16_t */
#define NS_INT8SZ       1       /* #/bytes of data in a u_int8_t */
#define NS_INADDRSZ     4       /* IPv4 T_A */
#define NS_IN6ADDRSZ    16      /* IPv6 T_AAAA */
#define NS_CMPRSFLGS    0xc0    /* Flag bits indicating name compression. */
#define NS_DEFAULTPORT  53      /* For both TCP and UDP. */

/*
 * Currently defined opcodes.
 */
typedef enum __ns_opcode {
    ns_o_query = 0,     /* Standard query. */
    ns_o_iquery = 1,    /* Inverse query (deprecated/unsupported). */
    ns_o_status = 2,    /* Name server status query (unsupported). */
                        /* Opcode 3 is undefined/reserved. */
    ns_o_notify = 4,    /* Zone change notification. */
    ns_o_update = 5,    /* Zone update message. */
    ns_o_max = 6
} ns_opcode;

/*
 * Currently defined response codes.
 */
typedef enum __ns_rcode {
    ns_r_noerror = 0,   /* No error occurred. */
    ns_r_formerr = 1,   /* Format error. */
    ns_r_servfail = 2,  /* Server failure. */
    ns_r_nxdomain = 3,  /* Name error. */
    ns_r_notimpl = 4,   /* Unimplemented. */
    ns_r_refused = 5,   /* Operation refused. */
    /* these are for BIND_UPDATE */
    ns_r_yxdomain = 6,  /* Name exists */
    ns_r_yxrrset = 7,   /* RRset exists */
    ns_r_nxrrset = 8,   /* RRset does not exist */
    ns_r_notauth = 9,   /* Not authoritative for zone */
    ns_r_notzone = 10,  /* Zone of record different from zone section */
    ns_r_max = 11,
    /* The following are EDNS extended rcodes */
    ns_r_badvers = 16,
    /* The following are TSIG errors */
    ns_r_badsig = 16,
    ns_r_badkey = 17,
    ns_r_badtime = 18
} ns_rcode;


/*
 * Currently defined type values for resources and queries.
 */
typedef enum __ns_type {
    ns_t_invalid = 0,   /* Cookie. */
    ns_t_a = 1,         /* Host address. */
    ns_t_ns = 2,        /* Authoritative server. */
    ns_t_md = 3,        /* Mail destination. */
    ns_t_mf = 4,        /* Mail forwarder. */
    ns_t_cname = 5,     /* Canonical name. */
    ns_t_soa = 6,       /* Start of authority zone. */
    ns_t_mb = 7,        /* Mailbox domain name. */
    ns_t_mg = 8,        /* Mail group member. */
    ns_t_mr = 9,        /* Mail rename name. */
    ns_t_null = 10,     /* Null resource record. */
    ns_t_wks = 11,      /* Well known service. */
    ns_t_ptr = 12,      /* Domain name pointer. */
    ns_t_hinfo = 13,    /* Host information. */
    ns_t_minfo = 14,    /* Mailbox information. */
    ns_t_mx = 15,       /* Mail routing information. */
    ns_t_txt = 16,      /* Text strings. */
    ns_t_rp = 17,       /* Responsible person. */
    ns_t_afsdb = 18,    /* AFS cell database. */
    ns_t_x25 = 19,      /* X_25 calling address. */
    ns_t_isdn = 20,     /* ISDN calling address. */
    ns_t_rt = 21,       /* Router. */
    ns_t_nsap = 22,     /* NSAP address. */
    ns_t_nsap_ptr = 23, /* Reverse NSAP lookup (deprecated). */
    ns_t_sig = 24,      /* Security signature. */
    ns_t_key = 25,      /* Security key. */
    ns_t_px = 26,       /* X.400 mail mapping. */
    ns_t_gpos = 27,     /* Geographical position (withdrawn). */
    ns_t_aaaa = 28,     /* Ip6 Address. */
    ns_t_loc = 29,      /* Location Information. */
    ns_t_nxt = 30,      /* Next domain (security). */
    ns_t_eid = 31,      /* Endpoint identifier. */
    ns_t_nimloc = 32,   /* Nimrod Locator. */
    ns_t_srv = 33,      /* Server Selection. */
    ns_t_atma = 34,     /* ATM Address */
    ns_t_naptr = 35,    /* Naming Authority PoinTeR */
    ns_t_kx = 36,       /* Key Exchange */
    ns_t_cert = 37,     /* Certification record */
    ns_t_a6 = 38,       /* IPv6 address (deprecates AAAA) */
    ns_t_dname = 39,    /* Non-terminal DNAME (for IPv6) */
    ns_t_sink = 40,     /* Kitchen sink (experimentatl) */
    ns_t_opt = 41,      /* EDNS0 option (meta-RR) */
    ns_t_apl = 42,      /* Address prefix list (RFC3123) */
    ns_t_tkey = 249,    /* Transaction key */
    ns_t_tsig = 250,    /* Transaction signature. */
    ns_t_ixfr = 251,    /* Incremental zone transfer. */
    ns_t_axfr = 252,    /* Transfer zone of authority. */
    ns_t_mailb = 253,   /* Transfer mailbox records. */
    ns_t_maila = 254,   /* Transfer mail agent records. */
    ns_t_any = 255,     /* Wildcard match. */
    ns_t_zxfr = 256,    /* BIND-specific, nonstandard. */
    ns_t_max = 65536
} ns_type;

/*
 * Values for class field
 */
typedef enum __ns_class {
    ns_c_invalid = 0,   /* Cookie. */
    ns_c_in = 1,        /* Internet. */
    ns_c_2 = 2,         /* unallocated/unsupported. */
    ns_c_chaos = 3,     /* MIT Chaos-net. */
    ns_c_hs = 4,        /* MIT Hesiod. */
    /* Query class values which do not appear in resource records */
    ns_c_none = 254,    /* for prereq. sections in update requests */
    ns_c_any = 255,     /* Wildcard match. */
    ns_c_max = 65536
} ns_class;

/*
 * EDNS0 extended flags, host order.
 */
#define NS_OPT_DNSSEC_OK    0x8000U

/*
 * Inline versions of get/put short/long.  Pointer is advanced.
 */
#define NS_GET16(s, cp) do { \
    const u_char *t_cp = (const u_char *)(cp); \
    (s) = ((uint16_t)t_cp[0] << 8) \
        | ((uint16_t)t_cp[1]) \
        ; \
    (cp) += NS_INT16SZ; \
} while (/*CONSTCOND*/0)

#define NS_GET32(l, cp) do { \
    const u_char *t_cp = (const u_char *)(cp); \
    (l) = ((uint32_t)t_cp[0] << 24) \
        | ((uint32_t)t_cp[1] << 16) \
        | ((uint32_t)t_cp[2] << 8) \
        | ((uint32_t)t_cp[3]) \
        ; \
    (cp) += NS_INT32SZ; \
} while (/*CONSTCOND*/0)

#define NS_PUT16(s, cp) do { \
    uint16_t t_s = (uint16_t)(s); \
    u_char *t_cp = (u_char *)(cp); \
    *t_cp++ = t_s >> 8; \
    *t_cp   = t_s; \
    (cp) += NS_INT16SZ; \
} while (/*CONSTCOND*/0)

#define NS_PUT32(l, cp) do { \
    uint32_t t_l = (uint32_t)(l); \
    u_char *t_cp = (u_char *)(cp); \
    *t_cp++ = t_l >> 24; \
    *t_cp++ = t_l >> 16; \
    *t_cp++ = t_l >> 8; \
    *t_cp   = t_l; \
    (cp) += NS_INT32SZ; \
} while (/*CONSTCOND*/0)

/*
 * ANSI C identifier hiding for bind's lib/nameser.
 */
#define ns_get16            __ns_get16
#define ns_get32            __ns_get32
#define ns_put16            __ns_put16
#define ns_put32            __ns_put32
#define ns_name_ntol        __ns_name_ntol
#define ns_name_ntop        __ns_name_ntop
#define ns_name_pton        __ns_name_pton
#define ns_name_unpack      __ns_name_unpack
#define ns_name_pack        __ns_name_pack
#define ns_name_compress    __ns_name_compress
#define ns_name_uncompress  __ns_name_uncompress
#define ns_name_skip        __ns_name_skip
#define ns_makecanon        __ns_makecanon
#define ns_samename         __ns_samename

u_int       ns_get16(const u_char *);
u_long      ns_get32(const u_char *);
void        ns_put16(u_int, u_char *);
void        ns_put32(u_long, u_char *);
int     ns_name_ntol(const u_char *, u_char *, size_t);
int     ns_name_ntop(const u_char *, char *, size_t);
int     ns_name_pton(const char *, u_char *, size_t);
int     ns_name_unpack(const u_char *, const u_char *,
                        const u_char *, u_char *, size_t);
int     ns_name_pack(const u_char *, u_char *, int,
                      const u_char **, const u_char **);
int     ns_name_uncompress(const u_char *, const u_char *,
                            const u_char *, char *, size_t);
int     ns_name_compress(const char *, u_char *, size_t,
                          const u_char **, const u_char **);
int     ns_name_skip(const u_char **, const u_char *);

int     ns_makecanon(const char *, char *, size_t);
int     ns_samename(const char *, const char *);

#include <arpa/nameser_compat.h>

#endif /* !_ARPA_NAMESER_H_ */
