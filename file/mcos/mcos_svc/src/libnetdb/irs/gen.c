/*  $NetBSD: gen.c,v 1.1.1.3.4.1 2007/05/17 00:39:46 jdc Exp $  */

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
/*! \file
 * \brief
 * this is the top level dispatcher
 *
 * The dispatcher is implemented as an accessor class; it is an
 * accessor class that calls other accessor classes, as controlled by a
 * configuration file.
 * 
 * A big difference between this accessor class and others is that the
 * map class initializers are NULL, and the map classes are already
 * filled in with method functions that will do the right thing.
 */

/* Imports */

/*
   Copyright (C) 2019 By eSOL Co.,Ltd. Tokyo, Japan
   Modified to work with eMCOS.
*/

#include "port_before.h"

#include "isc/assertions.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <netinet/in.h> 
#include <arpa/nameser.h>
#include "resolv.h"

#include "isc/memcluster.h"
#include "irs.h"
#include "port_after.h"

#include "irs_p.h"
#include "gen_p.h"
#include "mcos_netdb.h"

/* Definitions */

struct nameval {
    const char *    name;
    int             val;
};

static const struct nameval acc_names[irs_nacc+1] = {
    { "local", irs_lcl },
    { "dns",   irs_dns },
    { "nis",   irs_nis },
    { "irp",   irs_irp },
    { NULL,    irs_nacc }
};

typedef struct irs_acc *(*accinit)(const char *options);

static const accinit accs[irs_nacc+1] = {
    irs_lcl_acc,
    irs_dns_acc,
#ifdef WANT_IRS_NIS
    irs_nis_acc,
#else
    NULL,
#endif
#ifdef WANT_IRS_IRP
    irs_irp_acc,
#else
    NULL,
#endif
    NULL
};

static const struct nameval map_names[irs_nmap+1] = {
    { "group",     irs_gr },
    { "passwd",    irs_pw },
    { "services",  irs_sv },
    { "protocols", irs_pr },
    { "hosts",     irs_ho },
    { "networks",  irs_nw },
    { "netgroup",  irs_ng },
    { NULL,        irs_nmap }
};

static const struct nameval option_names[] = {
    { "merge",    IRS_MERGE },
    { "continue", IRS_CONTINUE },
    { NULL,       0 }
};

struct default_map_rule {
    enum irs_map_id  map_id;
    enum irs_acc_id  acc_id;
    int              opt_id;
};

/*
 * For default rule setting
 *
 * Bit definition for default map rule (_DEFAULT_RULE_xxx)
 * <1 record size is 8 bits,
 *  and 4 records(rules) can be set up to 4.>
 *  bit0~bit3:  Search mechanism kind
 *               0000:  (No search routine, no rule)
 *               0001:  local (= enum irs_lcl + 1)
 *               0010:  dns   (= enum irs_dns + 1)
 *               0011:  nis   (= enum irs_nis + 1)
 *               0100:  irp   (= enum irs_irp + 1)
 *  bit4~bit7:  Option setting
 *               0000:  (No option)
 *               0001:  "merge"    (= IRS_MERGE)
 *               0010:  "continue" (= IRS_CONTINUE)
 *               0011:  "merge" and  "continue"
 *
 * Example :
 *  _DEFAULT_RULE_HOSTS (=0x00000221) is composed with :
 *      1st rule (=0x21) : "local" with "continue" option
 *      2nd rule (=0x02) : "dns" without option
 *      3rd rule (=0x00) : none
 *      4th rule (=0x00) : none
 *  This is same meaning as following description in "irs.conf".
 *  ---
 *   hosts local continue
 *   hosts dns
 *  ---
 */
#define RULE_1      0       /* Rule 1 shift bits */
#define RULE_2      8       /* Rule 2 shift bits */
#define RULE_3      16      /* Rule 3 shift bits */
#define RULE_4      24      /* Rule 4 shitf bits */

#define ACC_MASK    0x0f    /* Mask for the acc value */
#define OPT_MASK    0x30    /* Mask for the option value */

#define OPT_SHIFT   4       /* shift bits of option value from base value */

#define OPT_NUM     2       /* Number of available options (See "option_names") */

#define RULE_MASK   0xff    /* Mask for the rule value */

#define ACC_MAX     5       /* Max acc value. Please check this macro
                             * if changed enum "irs_acc_id" in gen_p.h
                             */
#define OPT_MAX     4       /* Max option value */

#define RULE_CHECK(map, rule) (\
       ((((map) >> (rule)) & ACC_MASK) < ACC_MAX) \
    && ((((map) >> (rule)) & ACC_MASK) > 0) \
    && (((((map) >> (rule)) & OPT_MASK) >> OPT_SHIFT) < OPT_MAX) \
    && (((((map) >> (rule)) & OPT_MASK) >> OPT_SHIFT) >= 0) \
    )

#define RULE_CHECK_SKIP(map, rule) (((map) >> (rule)) & RULE_MASK)

/*
 * Default rule table (interpreted _DEFAULT_RULE_xxx macro.)
 */
static struct default_map_rule default_map_rule_table[] = 
{
    /*
     * service search mechanism
     */
#if (_DEFAULT_RULE_SERVICES == 0)
#error _DEFAULT_RULE_SERVICES is invalid
#endif
        /* 1st rule */
#if (RULE_CHECK(_DEFAULT_RULE_SERVICES, RULE_1) != 0)
        {
            irs_sv,
            (enum irs_acc_id)(((_DEFAULT_RULE_SERVICES >> RULE_1) & ACC_MASK) - 1),
            ((_DEFAULT_RULE_SERVICES >> RULE_1) & OPT_MASK) >> OPT_SHIFT
        },
#else
#if (RULE_CHECK_SKIP(_DEFAULT_RULE_SERVICES, RULE_1) != 0)
#error _DEFAULT_RULE_SERVICES is invalid
#endif
#endif
        /* 2nd rule */
#if (RULE_CHECK(_DEFAULT_RULE_SERVICES, RULE_2) != 0)
        {
            irs_sv,
            (enum irs_acc_id)(((_DEFAULT_RULE_SERVICES >> RULE_2) & ACC_MASK) - 1),
            ((_DEFAULT_RULE_SERVICES >> RULE_2) & OPT_MASK) >> OPT_SHIFT
        },
#else
#if (RULE_CHECK_SKIP(_DEFAULT_RULE_SERVICES, RULE_2) != 0)
#error _DEFAULT_RULE_SERVICES is invalid
#endif
#endif
        /* 3rd rule */
#if (RULE_CHECK(_DEFAULT_RULE_SERVICES, RULE_3) != 0)
        {
            irs_sv,
            (enum irs_acc_id)(((_DEFAULT_RULE_SERVICES >> RULE_3) & ACC_MASK) - 1),
            ((_DEFAULT_RULE_SERVICES >> RULE_3) & OPT_MASK) >> OPT_SHIFT
        },
#else
#if (RULE_CHECK_SKIP(_DEFAULT_RULE_SERVICES, RULE_3) != 0)
#error _DEFAULT_RULE_SERVICES is invalid
#endif
#endif
        /* 4th rule */
#if (RULE_CHECK(_DEFAULT_RULE_SERVICES, RULE_4) != 0)
        {
            irs_sv,
            (enum irs_acc_id)(((_DEFAULT_RULE_SERVICES >> RULE_4) & ACC_MASK) - 1),
            ((_DEFAULT_RULE_SERVICES >> RULE_4) & OPT_MASK) >> OPT_SHIFT
        },
#else
#if (RULE_CHECK_SKIP(_DEFAULT_RULE_SERVICES, RULE_4) != 0)
#error _DEFAULT_RULE_SERVICES is invalid
#endif
#endif

    /*
     * hosts search mechanism
     */
#if (_DEFAULT_RULE_HOSTS == 0)
#error _DEFAULT_RULE_HOSTS is invalid
#endif
        /* 1st rule */
#if (RULE_CHECK(_DEFAULT_RULE_HOSTS, RULE_1) != 0)
        {
            irs_ho,
            (enum irs_acc_id)(((_DEFAULT_RULE_HOSTS >> RULE_1) & ACC_MASK) - 1),
            ((_DEFAULT_RULE_HOSTS >> RULE_1) & OPT_MASK) >> OPT_SHIFT
        },
#else
#if (RULE_CHECK_SKIP(_DEFAULT_RULE_HOSTS, RULE_1) != 0)
#error _DEFAULT_RULE_HOSTS is invalid
#endif
#endif
        /* 2nd rule */
#if (RULE_CHECK(_DEFAULT_RULE_HOSTS, RULE_2) != 0)
        {
            irs_ho,
            (enum irs_acc_id)(((_DEFAULT_RULE_HOSTS >> RULE_2) & ACC_MASK) - 1),
            ((_DEFAULT_RULE_HOSTS >> RULE_2) & OPT_MASK) >> OPT_SHIFT
        },
#else
#if (RULE_CHECK_SKIP(_DEFAULT_RULE_HOSTS, RULE_2) != 0)
#error _DEFAULT_RULE_HOSTS is invalid
#endif
#endif
        /* 3rd rule */
#if (RULE_CHECK(_DEFAULT_RULE_HOSTS, RULE_3) != 0)
        {
            irs_ho,
            (enum irs_acc_id)(((_DEFAULT_RULE_HOSTS >> RULE_3) & ACC_MASK) - 1),
            ((_DEFAULT_RULE_HOSTS >> RULE_3) & OPT_MASK) >> OPT_SHIFT
        },
#else
#if (RULE_CHECK_SKIP(_DEFAULT_RULE_HOSTS, RULE_3) != 0)
#error _DEFAULT_RULE_HOSTS is invalid
#endif
#endif
        /* 4th rule */
#if (RULE_CHECK(_DEFAULT_RULE_HOSTS, RULE_4) != 0)
        {
            irs_ho,
            (enum irs_acc_id)(((_DEFAULT_RULE_HOSTS >> RULE_4) & ACC_MASK) - 1),
            ((_DEFAULT_RULE_HOSTS >> RULE_4) & OPT_MASK) >> OPT_SHIFT
        },
#else
#if (RULE_CHECK_SKIP(_DEFAULT_RULE_HOSTS, RULE_4) != 0)
#error _DEFAULT_RULE_HOSTS is invalid
#endif
#endif

    /* When other search mechanisms (like "group", "passwd" ..)
     * are supported, please add their rule here. */

    /* Terminator of the default map_rule */
        {
            irs_nmap,
            irs_nacc,
            0
        }
};

/* Forward */

static void     gen_close(struct irs_acc * this);
static struct __res_state * gen_res_get(struct irs_acc * this);
static void     gen_res_set(struct irs_acc * this, struct __res_state * res,
                            void (*free_res)(void *));
static int      find_name(const char *name, const struct nameval nv[]);
static void     init_map_rules(struct gen_p *irs, const char *conf_file);
static struct irs_rule *release_rule(struct irs_rule * rule);
static int      add_rule(struct gen_p * irs,
                         enum irs_map_id map, enum irs_acc_id acc,
                         const char * options);

/* Public */

struct irs_acc *
irs_gen_acc(const char *options, const char *conf_file) {
    struct irs_acc *acc;
    struct gen_p *irs;

    if ((acc = memget(sizeof *acc)) == NULL) {
        errno = ENOMEM;
        return (NULL);
    }
    memset(acc, 0x5e, sizeof *acc);
    if ((irs = memget(sizeof *irs)) == NULL) {
        errno = ENOMEM;
        memput(acc, sizeof *acc);
        return (NULL);
    }
    memset(irs, 0x5e, sizeof *irs);
    irs->options = strdup(options);
    irs->res = NULL;
    irs->free_res = NULL;
    memset(irs->accessors, 0, sizeof irs->accessors);
    memset(irs->map_rules, 0, sizeof irs->map_rules);
    init_map_rules(irs, conf_file);
    acc->private = irs;
#ifdef WANT_IRS_GR
    acc->gr_map = irs_gen_gr;
#else
    acc->gr_map = NULL;
#endif
#ifdef WANT_IRS_PW
    acc->pw_map = irs_gen_pw;
#else
    acc->pw_map = NULL;
#endif
    acc->sv_map = irs_gen_sv;
#ifdef WANT_IRS_PR
    acc->pr_map = irs_gen_pr;
#else
    acc->pr_map = NULL;
#endif  
    acc->ho_map = irs_gen_ho;
#ifdef WANT_IRS_NW
    acc->nw_map = irs_gen_nw;
#else
    acc->nw_map = NULL;
#endif  
#ifdef WANT_IRS_NG
    acc->ng_map = irs_gen_ng;
#else
    acc->ng_map = NULL;
#endif  
    acc->res_get = gen_res_get;
    acc->res_set = gen_res_set;
    acc->close = gen_close;
    return (acc);
}

/* Methods */

static struct __res_state *
gen_res_get(struct irs_acc *this) {
    struct gen_p *irs = (struct gen_p *)this->private;

    if (irs->res == NULL) {
        struct __res_state *res;
        res = (struct __res_state *)malloc(sizeof *res);
        if (res == NULL)
            return (NULL);
        memset(res, 0, sizeof *res);
        gen_res_set(this, res, free);
    }

    if (((irs->res->options & RES_INIT) == 0U) && res_ninit(irs->res) < 0)
        return (NULL);

    return (irs->res);
}

static void
gen_res_set(struct irs_acc *this, struct __res_state *res,
            void (*free_res)(void *)) {
    struct gen_p *irs = (struct gen_p *)this->private;

    if (irs->res && irs->free_res) {
        res_nclose(irs->res);
        (*irs->free_res)(irs->res);
    }

    irs->res = res;
    irs->free_res = free_res;
}

static void
gen_close(struct irs_acc *this) {
    struct gen_p *irs = (struct gen_p *)this->private;
    int n;

    /* Search rules. */
    for (n = 0; n < irs_nmap; n++)
        while (irs->map_rules[n] != NULL)
            irs->map_rules[n] = release_rule(irs->map_rules[n]);

    /* Access methods. */
    for (n = 0; n < irs_nacc; n++) {
        /* Map objects. */
#ifdef WANT_IRS_GR
        if (irs->accessors[n].gr != NULL)
            (*irs->accessors[n].gr->close)(irs->accessors[n].gr);
#endif

#ifdef WANT_IRS_PW
        if (irs->accessors[n].pw != NULL)
            (*irs->accessors[n].pw->close)(irs->accessors[n].pw);
#endif

        if (irs->accessors[n].sv != NULL)
            (*irs->accessors[n].sv->close)(irs->accessors[n].sv);

#ifdef WANT_IRS_PR
        if (irs->accessors[n].pr != NULL)
            (*irs->accessors[n].pr->close)(irs->accessors[n].pr);
#endif

        if (irs->accessors[n].ho != NULL)
            (*irs->accessors[n].ho->close)(irs->accessors[n].ho);

#ifdef WANT_IRS_NW
        if (irs->accessors[n].nw != NULL)
            (*irs->accessors[n].nw->close)(irs->accessors[n].nw);
#endif

#ifdef WANT_IRS_NG
        if (irs->accessors[n].ng != NULL)
            (*irs->accessors[n].ng->close)(irs->accessors[n].ng);
#endif
        /* Enclosing accessor. */
        if (irs->accessors[n].acc != NULL)
            (*irs->accessors[n].acc->close)(irs->accessors[n].acc);
    }

    /* The options string was strdup'd. */
    free((void*)irs->options);

    if (irs->res && irs->free_res)
        (*irs->free_res)(irs->res);

    /* The private data container. */
    memput(irs, sizeof *irs);

    /* The object. */
    memput(this, sizeof *this);
}

/* Private */

static int
find_name(const char *name, const struct nameval names[]) {
    int n;

    for (n = 0; names[n].name != NULL; n++)
        if (strcmp(name, names[n].name) == 0)
            return (names[n].val);
    return (-1);
}

static struct irs_rule *
release_rule(struct irs_rule *rule) {
    struct irs_rule *next = rule->next;

    memput(rule, sizeof *rule);
    return (next);
}

static int
add_rule(struct gen_p *irs,
     enum irs_map_id map, enum irs_acc_id acc,
     const char *options)
{
    struct irs_rule **rules, *last, *tmp, *new;
    struct irs_inst *inst;
    const char *cp;
    int n;

#ifndef WANT_IRS_GR
    if (map == irs_gr)
        return (-1);
#endif
#ifndef WANT_IRS_PW
    if (map == irs_pw)
        return (-1);
#endif
#ifndef WANT_IRS_NIS
    if (acc == irs_nis)
        return (-1);
#endif
    new = memget(sizeof *new);
    if (new == NULL)
        return (-1);
    memset(new, 0x5e, sizeof *new);
    new->next = NULL;

    new->inst = &irs->accessors[acc];

    new->flags = 0;
    cp = options;
    while (cp && *cp) {
        char option[50], *next;

        next = strchr(cp, ',');
        if (next)
            n = next++ - cp;
        else
            n = strlen(cp);
        if ((size_t)n > sizeof option - 1)
            n = sizeof option - 1;
        strncpy(option, cp, n);
        option[n] = '\0';

        n = find_name(option, option_names);
        if (n >= 0)
            new->flags |= n;

        cp = next;
    }

    rules = &irs->map_rules[map];
    for (last = NULL, tmp = *rules;
         tmp != NULL;
         last = tmp, tmp = tmp->next)
        (void)NULL;
    if (last == NULL)
        *rules = new;
    else
        last->next = new;

    /* Try to instantiate map accessors for this if necessary & approp. */
    inst = &irs->accessors[acc];
    if (inst->acc == NULL && accs[acc] != NULL)
        inst->acc = (*accs[acc])(irs->options);
    if (inst->acc != NULL) {
        if (inst->gr == NULL && inst->acc->gr_map != NULL)
            inst->gr = (*inst->acc->gr_map)(inst->acc);
        if (inst->pw == NULL && inst->acc->pw_map != NULL)
            inst->pw = (*inst->acc->pw_map)(inst->acc);
        if (inst->sv == NULL && inst->acc->sv_map != NULL)
            inst->sv = (*inst->acc->sv_map)(inst->acc);
        if (inst->pr == NULL && inst->acc->pr_map != NULL)
            inst->pr = (*inst->acc->pr_map)(inst->acc);
        if (inst->ho == NULL && inst->acc->ho_map != NULL)
            inst->ho = (*inst->acc->ho_map)(inst->acc);
        if (inst->nw == NULL && inst->acc->nw_map != NULL)
            inst->nw = (*inst->acc->nw_map)(inst->acc);
        if (inst->ng == NULL && inst->acc->ng_map != NULL)
            inst->ng = (*inst->acc->ng_map)(inst->acc);
    }

    return (0);
}

/* change the option id to the option name */
static void option_idtoname(int id, char *options)
{
    int index;
    for (index = 0; index < OPT_NUM; index++) 
    {
        if (((id >> index) & 0x01) != 0)
        {
            strcat(options, option_names[index].name);
            if (((id >> (index + 1)) & 0x01) != 0)
                strcat(options, ",");
        }
    }
}

static void
default_map_rules(struct gen_p *irs) {
    /* Install time honoured and proved BSD style rules as default. */
    char options[100];
    int i = 0;
    
    while(default_map_rule_table[i].map_id != irs_nmap) {
        memset(options, 0, sizeof(options));
        option_idtoname(default_map_rule_table[i].opt_id, options);
        add_rule(irs, default_map_rule_table[i].map_id, 
                default_map_rule_table[i].acc_id, options);
        i++;
    }
}

static void
init_map_rules(struct gen_p *irs, const char *conf_file) {
    char line[1024], pattern[40], mapname[20], accname[20], options[100];
    FILE *conf;

    if (conf_file == NULL) {
        conf_file = getenv("ENV_NET_IRSCONF");
        if (conf_file == NULL) {
            conf_file = _PATH_IRS_CONF;
        }
    }
    if (conf_file[0] == '\0' || (conf = fopen(conf_file, "r")) == NULL){
        default_map_rules(irs);
        return;
    }
    (void) sprintf(pattern, "%%%lus %%%lus %%%lus\n",
               (unsigned long)sizeof mapname,
               (unsigned long)sizeof accname,
               (unsigned long)sizeof options);
    while (fgets(line, sizeof line, conf)) {
        enum irs_map_id map;
        enum irs_acc_id acc;
        char *tmp;
        int n;

        for (tmp = line;
             isascii((unsigned char)*tmp) &&
             isspace((unsigned char)*tmp);
             tmp++)
            (void)NULL;
        if (*tmp == '#' || *tmp == '\n' || *tmp == '\0')
            continue;
        n = sscanf(tmp, pattern, mapname, accname, options);
        if (n < 2)
            continue;
        if (n < 3)
            options[0] = '\0';

        n = find_name(mapname, map_names);
        INSIST(n < irs_nmap);
        if (n < 0)
            continue;
        map = (enum irs_map_id) n;

        n = find_name(accname, acc_names);
        INSIST(n < irs_nacc);
        if (n < 0)
            continue;
        acc = (enum irs_acc_id) n;

        add_rule(irs, map, acc, options);
    }
    fclose(conf);
}
