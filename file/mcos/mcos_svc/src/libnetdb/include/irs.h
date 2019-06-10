/*  $NetBSD: irs.h,v 1.1.1.3.4.1 2007/05/17 00:39:22 jdc Exp $      */

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
 * Id: irs.h,v 1.4.18.1 2005/04/27 05:00:49 sra Exp
 */

#ifndef _IRS_H_INCLUDED
#define _IRS_H_INCLUDED

#include <sys/types.h>

#include <arpa/nameser.h>
#include <netdb.h>
#include "resolv.h"

/*
 * This is the group map class.
 */
struct irs_gr {
#ifdef WANT_IRS_GR
    void *          private;
    void            (*close)(struct irs_gr *);
    struct group    *(*next)(struct irs_gr *);
    struct group    *(*byname)(struct irs_gr *, const char *);
    struct group    *(*bygid)(struct irs_gr *, gid_t);
    int             (*list)(struct irs_gr *, const char *,
                             gid_t, gid_t *, int *);
    void            (*rewind)(struct irs_gr *);
    void            (*minimize)(struct irs_gr *);
    struct __res_state * (*res_get)(struct irs_gr *);
    void            (*res_set)(struct irs_gr *, res_state,
                                void (*)(void *));
#else
    void *          dummy;
#endif
};

/*
 * This is the password map class.
 */
struct irs_pw {
#ifdef WANT_IRS_PW
    void *          private;
    void            (*close)(struct irs_pw *);
    struct passwd * (*next)(struct irs_pw *);
    struct passwd * (*byname)(struct irs_pw *, const char *);
    struct passwd * (*byuid)(struct irs_pw *, uid_t);
    void            (*rewind)(struct irs_pw *);
    void            (*minimize)(struct irs_pw *);
    struct __res_state * (*res_get)(struct irs_pw *);
    void            (*res_set)(struct irs_pw *, res_state,
                                void (*)(void *));
#else
    void *          dummy;
#endif
};

/*
 * This is the service map class.
 */
struct irs_sv {
    void *          private;
    void            (*close)(struct irs_sv *);
    struct servent *(*byname)(struct irs_sv *,
                               const char *, const char *);
    struct servent *(*byport)(struct irs_sv *, int, const char *);
    struct servent *(*next)(struct irs_sv *);
    void            (*rewind)(struct irs_sv *);
    void            (*minimize)(struct irs_sv *);
    struct __res_state * (*res_get)(struct irs_sv *);
    void            (*res_set)(struct irs_sv *, res_state,
                                void (*)(void *));
};

/*
 * This is the protocols map class.
 */
struct irs_pr {
#ifdef WANT_IRS_PR
    void *          private;
    void            (*close)(struct irs_pr *);
    struct protoent *(*byname)(struct irs_pr *, const char *);
    struct protoent *(*bynumber)(struct irs_pr *, int);
    struct protoent *(*next)(struct irs_pr *);
    void            (*rewind)(struct irs_pr *);
    void            (*minimize)(struct irs_pr *);
    struct __res_state * (*res_get)(struct irs_pr *);
    void            (*res_set)(struct irs_pr *, res_state,
                                void (*)(void *));
#else
    void *          dummy;
#endif
};

/*
 * This is the hosts map class.
 */
struct irs_ho {
    void *          private;
    void            (*close)(struct irs_ho *);
    struct hostent *(*byname)(struct irs_ho *, const char *);
    struct hostent *(*byname2)(struct irs_ho *, const char *, int);
    struct hostent *(*byaddr)(struct irs_ho *,
                               const void *, int, int);
    struct hostent *(*next)(struct irs_ho *);
    void            (*rewind)(struct irs_ho *);
    void            (*minimize)(struct irs_ho *);
    struct __res_state * (*res_get)(struct irs_ho *);
    void            (*res_set)(struct irs_ho *, res_state,
                                void (*)(void *));
    struct addrinfo *(*addrinfo)(struct irs_ho *, const char *,
                                  const struct addrinfo *);
};

/*
 * This is the networks map class.
 */
struct irs_nw {
#ifdef WANT_IRS_NW
    void *          private;
    void            (*close)(struct irs_nw *);
    struct nwent *  (*byname)(struct irs_nw *, const char *, int);
    struct nwent *  (*byaddr)(struct irs_nw *, void *, int, int);
    struct nwent *  (*next)(struct irs_nw *);
    void            (*rewind)(struct irs_nw *);
    void            (*minimize)(struct irs_nw *);
    struct __res_state * (*res_get)(struct irs_nw *);
    void            (*res_set)(struct irs_nw *, res_state,
                                void (*)(void *));
#else
    void *          dummy;
#endif
};

/*
 * This is the netgroups map class.
 */
struct irs_ng {
#ifdef WANT_IRS_NG
    void *          private;
    void            (*close)(struct irs_ng *);
    int             (*next)(struct irs_ng *, const char **,
                             const char **, const char **);
    int             (*test)(struct irs_ng *, const char *,
                             const char *, const char *,
                             const char *);
    void            (*rewind)(struct irs_ng *, const char *);
    void            (*minimize)(struct irs_ng *);
#else
    void *          dummy;
#endif
};

/*
 * This is the generic map class, which copies the front of all others.
 */
struct irs_map {
    void *          private;
    void            (*close)(void *);
};

/*
 * This is the accessor class.  It contains pointers to all of the
 * initializers for the map classes for a particular accessor.
 */
struct irs_acc {
    void *          private;
    void            (*close)(struct irs_acc *);
    struct irs_gr * (*gr_map)(struct irs_acc *);
    struct irs_pw * (*pw_map)(struct irs_acc *);
    struct irs_sv * (*sv_map)(struct irs_acc *);
    struct irs_pr * (*pr_map)(struct irs_acc *);
    struct irs_ho * (*ho_map)(struct irs_acc *);
    struct irs_nw * (*nw_map)(struct irs_acc *);
    struct irs_ng * (*ng_map)(struct irs_acc *);
    struct __res_state * (*res_get)(struct irs_acc *);
    void            (*res_set)(struct irs_acc *, res_state,
                                void (*)(void *));
};

#ifdef WANT_IRS_NW
/*
 * This is because the official definition of "struct netent" has no
 * concept of CIDR even though it allows variant address families (on
 * output but not input).  The compatibility stubs convert the structs
 * below into "struct netent"'s.
 */
struct nwent {
    char            *n_name;        /* official name of net */
    char            **n_aliases;    /* alias list */
    int             n_addrtype;     /* net address type */
    void            *n_addr;        /* network address */
    int             n_length;       /* address length, in bits */
};
#endif

/*
 * Hide external function names from POSIX.
 */
#define irs_gen_acc                 __irs_gen_acc
#define irs_lcl_acc                 __irs_lcl_acc
#define irs_dns_acc                 __irs_dns_acc
#define irs_nis_acc                 __irs_nis_acc
#define irs_irp_acc                 __irs_irp_acc
#define irs_destroy                 __irs_destroy
#define irs_dns_gr                  __irs_dns_gr
#define irs_dns_ho                  __irs_dns_ho
#define irs_dns_nw                  __irs_dns_nw
#define irs_dns_pr                  __irs_dns_pr
#define irs_dns_pw                  __irs_dns_pw
#define irs_dns_sv                  __irs_dns_sv
#define irs_gen_gr                  __irs_gen_gr
#define irs_gen_ho                  __irs_gen_ho
#define irs_gen_ng                  __irs_gen_ng
#define irs_gen_nw                  __irs_gen_nw
#define irs_gen_pr                  __irs_gen_pr
#define irs_gen_pw                  __irs_gen_pw
#define irs_gen_sv                  __irs_gen_sv
#define irs_irp_get_full_response   __irs_irp_get_full_response
#define irs_irp_gr                  __irs_irp_gr
#define irs_irp_ho                  __irs_irp_ho
#define irs_irp_is_connected        __irs_irp_is_connected
#define irs_irp_ng                  __irs_irp_ng
#define irs_irp_nw                  __irs_irp_nw
#define irs_irp_pr                  __irs_irp_pr
#define irs_irp_pw                  __irs_irp_pw
#define irs_irp_read_line           __irs_irp_read_line
#define irs_irp_sv                  __irs_irp_sv
#define irs_lcl_gr                  __irs_lcl_gr
#define irs_lcl_ho                  __irs_lcl_ho
#define irs_lcl_ng                  __irs_lcl_ng
#define irs_lcl_nw                  __irs_lcl_nw
#define irs_lcl_pr                  __irs_lcl_pr
#define irs_lcl_pw                  __irs_lcl_pw
#define irs_lcl_sv                  __irs_lcl_sv
#define irs_nis_gr                  __irs_nis_gr
#define irs_nis_ho                  __irs_nis_ho
#define irs_nis_ng                  __irs_nis_ng
#define irs_nis_nw                  __irs_nis_nw
#define irs_nis_pr                  __irs_nis_pr
#define irs_nis_pw                  __irs_nis_pw
#define irs_nis_sv                  __irs_nis_sv
#define net_data_create             __net_data_create
#define net_data_destroy            __net_data_destroy
#define net_data_minimize           __net_data_minimize

/*
 * Externs.
 */
extern struct irs_acc * irs_gen_acc(const char * options, const char * conf_file);
extern struct irs_acc * irs_lcl_acc(const char * options);
extern struct irs_acc * irs_dns_acc(const char * options);
extern struct irs_acc * irs_nis_acc(const char * options);
extern struct irs_acc * irs_irp_acc(const char * options);

extern void irs_destroy(void);
/*
 * These forward declarations are for the semi-private functions in
 * the get*.c files. Each of these funcs implements the real get*
 * functionality and the standard versions are just wrappers that
 * call these. Apart from the wrappers, only irpd is expected to
 * call these directly, hence these decls are put here and not in
 * the /usr/include replacements.
 */

struct net_data;    /* forward */
/*
 * net_data_create gets a singleton net_data object.  net_data_init
 * creates as many net_data objects as times it is called.  Clients using
 * the default interface will use net_data_create by default.  Servers will
 * probably want net_data_init (one call per client)
 */
struct net_data *net_data_create(const char * conf_file);
struct net_data *net_data_init(const char * conf_file);
void            net_data_destroy(void *);

extern struct hostent   *gethostbyname_p(const char * name,
                                          struct net_data * net_data);
extern struct hostent   *gethostbyname2_p(const char * name, int af,
                                           struct net_data * net_data);
extern struct hostent   *gethostbyaddr_p(const char * addr, socklen_t len, int af,
                                          struct net_data * net_data);
extern struct hostent   *gethostent_p(struct net_data * net_data);
extern void             sethostent_p(int stayopen, struct net_data * net_data);
extern void             endhostent_p(struct net_data * net_data);

extern struct servent   *getservent_p(struct net_data * net_data);
extern struct servent   *getservbyname_p(const char * name, const char * proto,
                                          struct net_data * net_data);
extern struct servent   *getservbyport_p(int port, const char * proto,
                                          struct net_data * net_data);
extern void             setservent_p(int stayopen, struct net_data * net_data);
extern void             endservent_p(struct net_data * net_data);

#endif /*_IRS_H_INCLUDED*/
