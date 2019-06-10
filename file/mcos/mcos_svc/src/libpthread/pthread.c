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
[pthread.c] - POSIX Thread library API
****************************************************************************/
#include <pt_api_impl.h>
#include <pt_thread_if.h>
#include <pt_once_if.h>
#include <posix_atomic.h>
#include <errno.h>
#include <string.h>
#include <sched.h>

extern void pt_handle_interrupt(pttcb_t* pttcb);

static int pthread_attr_valid(const pthread_attr_t* attr)
{
    return (1
#ifdef MCOS_CFG_PT_CHECK_ARGUMENTS
            && (attr != 0)
            && (CHECK_ALIGN(attr, sizeof(attr->addr)) == 0)
#endif
    );
}

/* pthread_attr_init() API */
int pthread_attr_init(pthread_attr_t* attr)
{
    if (pthread_attr_valid((const pthread_attr_t*)attr) == 0)
    {
        return EINVAL;
    }
    attr->attr[ATIX] = (((MCOS_CFG_PT_MAX_PRI - MCOS_CFG_PT_MIN_PRI + 1) / 2)
                        | ((unsigned)MCOS_LCID_INHERIT << PTHREAD_ATTR_LCID_SHIFT));
    attr->attr[SZIX] = MCOS_CFG_THR_DEFAULT_STACKSIZE;
    attr->addr = 0;
    attr->name[0] = '\0';
    return 0;
}

/* pthread_attr_destroy() API */
int pthread_attr_destroy(pthread_attr_t* attr)
{
    if (pthread_attr_valid((const pthread_attr_t*)attr))
    {
        attr->attr[ATIX] = PTHREAD_ATTR_INVALID;
        attr->attr[SZIX] = 0;
        attr->addr = 0;
        return 0;
    }
    return EINVAL;
}

/* pthread_attr_getdetachstate() API */
int pthread_attr_getdetachstate(const pthread_attr_t* attr, int* detach)
{
    if (pthread_attr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (detach != 0)
        && (CHECK_ALIGN(detach, sizeof(*detach)) == 0)
#endif
    )
    {
        *detach = (((attr->attr[ATIX]
                     & (PTHREAD_ATTR_DETACHED_MASK
                        << PTHREAD_ATTR_DETACHED_SHIFT)) != 0)
                   ? PTHREAD_CREATE_DETACHED
                   : PTHREAD_CREATE_JOINABLE);
        return 0;
    }
    return EINVAL;
}

/* pthread_attr_setdetachstate() API */
int pthread_attr_setdetachstate(pthread_attr_t* attr, int detach)
{
    if ((detach == PTHREAD_CREATE_JOINABLE
         || detach == PTHREAD_CREATE_DETACHED)
        && pthread_attr_valid((const pthread_attr_t*)attr))
    {
        attr->attr[ATIX] = ((attr->attr[ATIX]
                             & ~(PTHREAD_ATTR_DETACHED_MASK
                                 << PTHREAD_ATTR_DETACHED_SHIFT))
                            | (detach == PTHREAD_CREATE_DETACHED
                               ? (PTHREAD_ATTR_DETACHED_MASK
                                  << PTHREAD_ATTR_DETACHED_SHIFT)
                               : 0));
        return 0;
    }
    return EINVAL;
}

/* pthread_attr_getinheritsched() API */
int pthread_attr_getinheritsched(const pthread_attr_t *restrict attr,
                                 int *restrict inherit)
{
    if (pthread_attr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (inherit != 0)
        && (CHECK_ALIGN(inherit, sizeof(*inherit)) == 0)
#endif
    )
    {
        *inherit = (((attr->attr[ATIX]
                      & (PTHREAD_ATTR_INHERIT_MASK
                         << PTHREAD_ATTR_INHERIT_SHIFT)) != 0)
                    ? PTHREAD_INHERIT_SCHED
                    : PTHREAD_EXPLICIT_SCHED);
        return 0;
    }
    return EINVAL;
}

/* pthread_attr_setinheritsched() API */
int pthread_attr_setinheritsched(pthread_attr_t* attr, int inherit)
{
    if (((inherit == PTHREAD_EXPLICIT_SCHED)
         || (inherit == PTHREAD_INHERIT_SCHED))
        && pthread_attr_valid((const pthread_attr_t*)attr))
    {
        attr->attr[ATIX] = ((attr->attr[ATIX]
                             & ~(PTHREAD_ATTR_INHERIT_MASK
                                 << PTHREAD_ATTR_INHERIT_SHIFT))
                            | (inherit == PTHREAD_INHERIT_SCHED
                               ? (PTHREAD_ATTR_INHERIT_MASK
                                  << PTHREAD_ATTR_INHERIT_SHIFT)
                               : 0));
        return 0;
    }
    return EINVAL;
}

int pthread_attr_getschedparam(const pthread_attr_t *restrict attr,
                               struct sched_param *restrict param)
{
    if (pthread_attr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (param != 0)
        && (CHECK_ALIGN(param, sizeof(param->sched_priority)) == 0)
#endif
    )
    {
        param->sched_priority = ((attr->attr[ATIX] >> PTHREAD_ATTR_PRIO_SHIFT)
                                 & PTHREAD_ATTR_PRIO_MASK);
        return 0;
    }
    return EINVAL;
}

/* pthread_attr_setschedparam() API */
int pthread_attr_setschedparam(pthread_attr_t *restrict attr,
                               const struct sched_param *restrict param)
{
    if (pthread_attr_valid((const pthread_attr_t*)attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (param != 0)
        && (CHECK_ALIGN(param, sizeof(param->sched_priority)) == 0)
#endif
        && (param->sched_priority >= MCOS_CFG_PT_MIN_PRI)
        && (param->sched_priority <= MCOS_CFG_PT_MAX_PRI)
    )
    {
        attr->attr[ATIX] = ((attr->attr[ATIX]
                             & ~(PTHREAD_ATTR_PRIO_MASK << PTHREAD_ATTR_PRIO_SHIFT))
                            | (param->sched_priority << PTHREAD_ATTR_PRIO_SHIFT));
        return 0;
    }
    return EINVAL;
}

/* pthread_attr_getschedpolicy() API */
int pthread_attr_getschedpolicy(const pthread_attr_t *restrict attr,
                                int *restrict policy)
{
    if (pthread_attr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (policy != 0)
        && (CHECK_ALIGN(policy, sizeof(*policy)) == 0)
#endif
    )
    {
        *policy = ((attr->attr[ATIX] >> PTHREAD_ATTR_POLICY_SHIFT)
                   & PTHREAD_ATTR_POLICY_MASK);
        return 0;
    }
    return EINVAL;
}

/* pthread_attr_setschedpolicy() API */
int pthread_attr_setschedpolicy(pthread_attr_t* attr, int policy)
{
    if (((policy == SCHED_FIFO)
         || (policy == SCHED_RR)
         || (policy == SCHED_SPORADIC)
         || (policy == SCHED_OTHER))
        && pthread_attr_valid((const pthread_attr_t*)attr))
    {
        if (policy == SCHED_SPORADIC)
        {
            return ENOTSUP;
        }
        attr->attr[ATIX] = ((attr->attr[ATIX]
                             & ~(PTHREAD_ATTR_POLICY_MASK
                                 << PTHREAD_ATTR_POLICY_SHIFT))
                            | (policy << PTHREAD_ATTR_POLICY_SHIFT));
        return 0;
    }
    return EINVAL;
}

/* pthread_attr_getscope() API */
int pthread_attr_getscope(const pthread_attr_t *restrict attr,
                          int *restrict scope)
{
    if (pthread_attr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (scope != 0)
        && (CHECK_ALIGN(scope, sizeof(*scope)) == 0)
#endif
    )
    {
        *scope = PTHREAD_SCOPE_SYSTEM;
        return 0;
    }
    return EINVAL;
}

/* pthread_attr_setscope() API */
int pthread_attr_setscope(pthread_attr_t* attr, int scope)
{
    if (((scope == PTHREAD_SCOPE_SYSTEM)
         || (scope == PTHREAD_SCOPE_PROCESS))
        && pthread_attr_valid((const pthread_attr_t*)attr))
    {
     /* Process scope scheduling not supported */
        if (scope == PTHREAD_SCOPE_PROCESS)
        {
            return ENOTSUP;
        }
        return 0;
    }
    return EINVAL;
}

/* pthread_attr_getstacksize() API */
int pthread_attr_getstacksize(const pthread_attr_t *restrict attr,
                              size_t *restrict ssize)
{
    if (pthread_attr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (ssize != 0)
        && (CHECK_ALIGN(ssize, sizeof(*ssize)) == 0)
#endif
    )
    {
        *ssize = (size_t)attr->attr[SZIX];
        return 0;
    }
    return EINVAL;
}

/* pthread_attr_setstacksize() API */
int pthread_attr_setstacksize(pthread_attr_t* attr, size_t ssize)
{
    if (pthread_attr_valid((const pthread_attr_t*)attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (CHECK_ALIGN(ssize, STACK_ALIGN) == 0)
#endif
        && (ssize >= MCOS_CFG_PT_SSIZE_MIN)
        && (ssize <= MCOS_CFG_PT_SSIZE_MAX)
    )
    {
        attr->attr[SZIX] = ssize;
        return 0;
    }
    return EINVAL;
}

/* pthread_attr_getstackaddr() API */
int pthread_attr_getstackaddr(const pthread_attr_t *restrict attr,
                              void **restrict stack)
{
    if (pthread_attr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (stack != 0)
        && (CHECK_ALIGN(stack, sizeof(*stack)) == 0)
#endif
    )
    {
        *stack = attr->addr;
        return 0;
    }
    return EINVAL;
}

/* pthread_attr_setstackaddr() API */
int pthread_attr_setstackaddr(pthread_attr_t* attr, void* stack)
{
    if (pthread_attr_valid((const pthread_attr_t*)attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (stack != 0)
        && (CHECK_ALIGN(stack, STACK_ALIGN) == 0)
#endif
    )
    {
        attr->attr[ATIX] |= PTHREAD_ATTR_USERSTACK_MASK << PTHREAD_ATTR_USERSTACK_SHIFT;
        attr->addr = stack;
        return 0;
    }
    return EINVAL;
}

/* pthread_attr_getstack() API */
int pthread_attr_getstack(const pthread_attr_t *restrict attr,
                          void **restrict stack, size_t *restrict ssize)
{
    if (pthread_attr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (stack != 0)
        && (CHECK_ALIGN(stack, sizeof(*stack)) == 0)
        && (ssize != 0)
        && (CHECK_ALIGN(ssize, sizeof(*ssize)) == 0)
#endif
    )
    {
        *ssize = (size_t)attr->attr[SZIX];
        *stack = attr->addr;
        return 0;
    }
    return EINVAL;
}

/* pthread_attr_setstack() API */
int pthread_attr_setstack(pthread_attr_t* attr, void* stack, size_t ssize)
{
    if (pthread_attr_valid((const pthread_attr_t*)attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (stack != 0)
        && (CHECK_ALIGN(stack, STACK_ALIGN) == 0)
        && (CHECK_ALIGN(ssize, STACK_ALIGN) == 0)
#endif
        && (ssize >= MCOS_CFG_PT_SSIZE_MIN)
        && (ssize <= MCOS_CFG_PT_SSIZE_MAX)
    )
    {
        attr->attr[ATIX] |= PTHREAD_ATTR_USERSTACK_MASK << PTHREAD_ATTR_USERSTACK_SHIFT;
        attr->attr[SZIX] = ssize;
        attr->addr = stack;
        return 0;
    }
    return EINVAL;
}

/* Not supported: pthread_attr_getguardsize() API */
int pthread_attr_getguardsize(const pthread_attr_t *restrict attr,
                              size_t *restrict guard)
{
    return ENOTSUP;
}

/* Not supported: pthread_attr_setguardsize() */
int pthread_attr_setguardsize(pthread_attr_t* attr, size_t guard)
{
    return ENOTSUP;
}

/* non-portable */
int pthread_attr_getlcid_np(const pthread_attr_t *restrict attr,
                            int *restrict lcid)
{
    if (pthread_attr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (lcid != 0)
        && (CHECK_ALIGN(lcid, sizeof(*lcid)) == 0)
#endif
    )
    {
        *lcid = (int)attr->attr[ATIX] >> PTHREAD_ATTR_LCID_SHIFT;
        return 0;
    }
    return EINVAL;
}

extern mcos_bool_t mcos_is_validlcid(const mcos_id_t lcid);
/* non-portable */
int pthread_attr_setlcid_np(pthread_attr_t* attr, int lcid)
{
    if (pthread_attr_valid((const pthread_attr_t*)attr)
        && ((lcid == MCOS_LCID_ANY)
            || (lcid == MCOS_LCID_SELF)
            || (lcid == MCOS_LCID_INHERIT)
            || mcos_is_validlcid(lcid)))
    {
        attr->attr[ATIX] = ((attr->attr[ATIX] &
                             ~(-1U << PTHREAD_ATTR_LCID_SHIFT))
                            | (lcid << PTHREAD_ATTR_LCID_SHIFT));
        return 0;
    }
    return EINVAL;
}

/* non-portable */
int pthread_attr_getname_np(const pthread_attr_t* attr, char* name)
{
    size_t  len;

    if (pthread_attr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
         && (name != 0)
         && (CHECK_ALIGN(name, sizeof(*name)) == 0)
#endif
    )
    {
        len = sizeof(attr->name);
        (void)strncpy(name, attr->name, len);
        return 0;
    }
    return EINVAL;
}

/* non-portable */
int pthread_attr_setname_np(pthread_attr_t* attr, const char* name)
{
    size_t  len;

    if (    (pthread_attr_valid((const pthread_attr_t*)attr))
         && (name != NULL)
         && ((len = strlen(name)) < sizeof(attr->name)) )
    {
        (void)strncpy(attr->name, name, len+1);
        return 0;
    }
    return EINVAL;
}

/* non-portable */
int pthread_attr_getstdmsg_np(const pthread_attr_t *restrict attr, mcos_bool_t *restrict stdmsg)
{
    if (pthread_attr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (stdmsg != 0)
        && (CHECK_ALIGN(stdmsg, sizeof(*stdmsg)) == 0)
#endif
    )
    {
        *stdmsg = ((attr->attr[ATIX] >> PTHREAD_ATTR_STDMSG_SHIFT) & PTHREAD_ATTR_STDMSG_MASK) ? mcos_true : mcos_false;

        return 0;
    }
    return EINVAL;
}

/* non-portable */
int pthread_attr_setstdmsg_np( pthread_attr_t *attr, mcos_bool_t stdmsg)
{
    if (pthread_attr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (stdmsg == mcos_true || stdmsg == mcos_false)
#endif
    )
    {
        unsigned int flag;

        flag = (stdmsg == mcos_false) ? 0U : 1U;
        attr->attr[ATIX] = ((attr->attr[ATIX]
                             & ~(PTHREAD_ATTR_STDMSG_MASK
                                 << PTHREAD_ATTR_STDMSG_SHIFT))
                            | (flag << PTHREAD_ATTR_STDMSG_SHIFT));

        return 0;
    }
    return EINVAL;
}

/* non-portable */
int pthread_attr_getpriorityinheritance_np(const pthread_attr_t *restrict attr, mcos_bool_t *restrict inherit)
{
    if (pthread_attr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (inherit != 0)
        && (CHECK_ALIGN(inherit, sizeof(*inherit)) == 0)
#endif
    )
    {
        *inherit = ((attr->attr[ATIX] >> PTHREAD_ATTR_MSGINHERIT_SHIFT) & PTHREAD_ATTR_MSGINHERIT_MASK) ? mcos_true : mcos_false;

        return 0;
    }
    return EINVAL;
}

/* non-portable */
int pthread_attr_setpriorityinheritance_np( pthread_attr_t *attr, mcos_bool_t inherit)
{
    if (pthread_attr_valid(attr)
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        && (inherit == mcos_true || inherit == mcos_false)
#endif
    )
    {
        unsigned int flag;

        flag = (inherit == mcos_false) ? 0U : 1U;
        attr->attr[ATIX] = ((attr->attr[ATIX]
                             & ~(PTHREAD_ATTR_MSGINHERIT_MASK
                                 << PTHREAD_ATTR_MSGINHERIT_SHIFT))
                            | (flag << PTHREAD_ATTR_MSGINHERIT_SHIFT));

        return 0;
    }
    return EINVAL;
}

/* pthread_testcancel() API */
void pthread_testcancel(void)
{
 /* Get own pttcb */
    pttcb_t* pttcb = pt_get_pttcb();
    if (pttcb != 0)
    {
     /* Check cancel enabled and pending */
        if ((pttcb->flags & (PTHREAD_CANCELOK
                             | PTHREAD_CANENAB
                             | PTHREAD_CANPEND))
            == (PTHREAD_CANCELOK
                | PTHREAD_CANENAB
                | PTHREAD_CANPEND))
        {
            pthread_exit(PTHREAD_CANCELED);
        }
    }
}

/* pthread_setcancelstate() API */
int pthread_setcancelstate(int state, int* old)
{
 /* Check argument */
    if (0
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        || (CHECK_ALIGN(old, sizeof(*old)) != 0)
#endif
        || (state != PTHREAD_CANCEL_ENABLE
            && state != PTHREAD_CANCEL_DISABLE))
    {
        return EINVAL;
    }

 /* Get own pttcb */
    pttcb_t* pttcb = pt_get_pttcb();
    if (pttcb == 0)
    {
        return EPERM;
    }

 /* Get current state */
    int cur = (((pttcb->flags & PTHREAD_CANENAB) != 0)
               ? PTHREAD_CANCEL_ENABLE
               : PTHREAD_CANCEL_DISABLE);

 /* If must change state */
    if (cur != state)
    {
        if (state == PTHREAD_CANCEL_ENABLE)
        {
            posix_atomic_or(&pttcb->flags, PTHREAD_CANENAB);
        }
        else
        {
            posix_atomic_and(&pttcb->flags, ~PTHREAD_CANENAB);
        }
    }
 /* Return old state and success */
    if (old != 0)
    {
        *old = cur;
    }
    return 0;
}

/* pthread_setcanceltype() API */
int pthread_setcanceltype(int type, int* old)
{
 /* Check argument */
    if (0
#if MCOS_CFG_PT_CHECK_ARGUMENTS
        || (CHECK_ALIGN(old, sizeof(*old)) != 0)
#endif
        || (type != PTHREAD_CANCEL_DEFERRED
            && type != PTHREAD_CANCEL_ASYNCHRONOUS))
    {
        return EINVAL;
    }

 /* Get own pttcb */
    pttcb_t* pttcb = pt_get_pttcb();
    if (pttcb == 0)
    {
        return EPERM;
    }

 /* Get current type */
    int cur = (((pttcb->flags & PTHREAD_CANASYNC) != 0)
               ? PTHREAD_CANCEL_ASYNCHRONOUS
               : PTHREAD_CANCEL_DEFERRED);

 /* If must change type */
    if (cur != type)
    {
        if (type == PTHREAD_CANCEL_ASYNCHRONOUS)
        {
            posix_atomic_or(&pttcb->flags, PTHREAD_CANASYNC);
        }
        else
        {
            posix_atomic_and(&pttcb->flags, ~PTHREAD_CANASYNC);
        }
    }
 /* Return old type and success */
    if (old != 0)
    {
        *old = cur;
    }
    return 0;
}

void _pthread_cleanup_push(struct _pthread_cleanup* data, void (*func)(void*), void* para)
{
    pttcb_t* pttcb = pt_get_pttcb();

    if (pttcb != 0)
    {
        data->_func_ = func;
        data->_para_ = para;
        data->_prev_ = pttcb->cleanup;
        posix_atomic_purge((void*)data);

        pttcb->cleanup = data;
    }
}

void _pthread_cleanup_pop(struct _pthread_cleanup* data, int exec)
{
    pttcb_t* pttcb = pt_get_pttcb();

    if (pttcb != 0)
    {
        pttcb->cleanup = data->_prev_;
        if ((exec != 0) && (data->_func_ != 0))
        {
            (*data->_func_)(data->_para_);
        }
    }
}

/* sched_get_priority_max() API */
int sched_get_priority_max(int policy)
{
    int status;

    status = EINVAL;
    if (policy == SCHED_FIFO
        || policy == SCHED_RR
        || policy == SCHED_SPORADIC
        || policy == SCHED_OTHER)
    {
        status = ENOTSUP;
        if (policy != SCHED_SPORADIC)
        {
            return MCOS_CFG_PT_MAX_PRI;
        }
    }
    errno = status;
    return -1;
}

/* sched_get_priority_min() API */
int sched_get_priority_min(int policy)
{
    int status;

    status = EINVAL;
    if (policy == SCHED_FIFO
        || policy == SCHED_RR
        || policy == SCHED_SPORADIC
        || policy == SCHED_OTHER)
    {
        status = ENOTSUP;
        if (policy != SCHED_SPORADIC)
        {
            return MCOS_CFG_PT_MIN_PRI;
        }
    }
    errno = status;
    return -1;
}

/* Initialization thread cleanup handler */
static void pt_once_cleanup(void* arg)
{
    pthread_once_t* once = (pthread_once_t*)arg;
    uint32_t        val;
    uint32_t        tmp;

 /* Mark once not locked and wakeup all waiters */
    val = (uint32_t)posix_atomic_get((void*)&(once->value));
    do
    {
        tmp = val;
        val = posix_atomic_cmpset(&once->value, tmp,
                                  val & ~(ONCE_LOCKED_MASK << ONCE_LOCKED_SHIFT));
    } while (val != tmp);

 /* LS bits 01 - resume a waiter or keep this bit until resume */
    if ((val >> ONCE_WAITING_SHIFT) != 0)
    {
        pt_once_finish((uint32_t)(uintptr_t)arg | (ONCE_LOCKED_MASK << ONCE_LOCKED_SHIFT));
    }
}

/* a part of pthread_once */
MCOS_INLINE int
pthread_once_not_locked(pthread_once_t* once, void (*func)(void), int32_t val)
{
    int32_t     tmp;

 /* If once not locked */
 /* Try change once state to initializing */
    tmp = val;
    val = posix_atomic_cmpset(&once->value, tmp,
                              val | (ONCE_LOCKED_MASK << ONCE_LOCKED_SHIFT));
    if (val == tmp)
    {
     /* POSIX Std: The pthread_once() function is not a cancellation point.
      * However, if init_routine is a cancellation point and is canceled,
      * the effect on once_var shall be as if pthread_once() was never called. */

     /* Guard from cancellation while initializing */
        pthread_cleanup_push(pt_once_cleanup, once);

     /* Execute once function */
        (*func)();

     /* Discard cleanup handler record */
        pthread_cleanup_pop(0);

     /* Mark once finished */
        val = (int32_t)posix_atomic_get((void*)&(once->value));
        do
        {
            tmp = val;
            val = posix_atomic_cmpset(&once->value, tmp,
                                      val | (ONCE_FINISH_MASK << ONCE_FINISH_SHIFT));
        } while (val != tmp);

     /* If server was accessed send finish request */
        if ((val & (ONCE_SERVER_MASK << ONCE_SERVER_SHIFT)) != 0)
        {
         /* LS bits are
            10 - finish (server willl remember this value)
            11 - remove once object (no waiters are present) */
            (void)pt_once_finish((uint32_t)(uintptr_t)once
                                 | (ONCE_FINISH_MASK << ONCE_FINISH_SHIFT)
                                 | (((val >> ONCE_WAITING_SHIFT) == 0)
                                    << ONCE_LOCKED_SHIFT));
        }
    }
    return 0;
}

/* a part of pthread_once */
MCOS_INLINE int
pthread_once_locked(pthread_once_t* once, int32_t val, pttcb_t* pttcb)
{
    int32_t     tmp;
    unsigned    flags;
    int         sta;

 /* Once now initializing and we must wait */
 /* Try set server accessed and increment waiting count */
    tmp = val;
    val = posix_atomic_cmpset(&once->value, tmp,
                              (val + (1 << ONCE_WAITING_SHIFT))
                              | (ONCE_SERVER_MASK << ONCE_SERVER_SHIFT));

 /* Block to wait until woken by initializer thread */
    if (val == tmp)
    {
     /* pthread_once() is not cancellation point */
        flags = posix_atomic_and(&pttcb->flags, ~PTHREAD_CANCELOK) & PTHREAD_CANCELOK;
        sta = pt_once_locked((uint32_t)(uintptr_t)once);
        if (sta == 0)
        {
         /* Decrement waiting count */
            val = (int32_t)posix_atomic_get((void*)&(once->value));
            do
            {
                tmp = val;
                val = posix_atomic_cmpset(&once->value, tmp,
                                          val - (1 << ONCE_WAITING_SHIFT));
            } while (val != tmp);

         /* Handle signals */
            if (sta == EINTR)
            {
                (void)pt_handle_interrupt(pttcb);
            }

         /* Leave nocancel state */
            posix_atomic_or(&pttcb->flags, flags);

         /* If finished and caller was last waiter remove once object */
            if ( ((val & (ONCE_FINISH_MASK << ONCE_FINISH_SHIFT)) != 0)
                 && ((val >> ONCE_WAITING_SHIFT) == 1) )
            {
             /* LS bits value 11 instructs server to remove once object */
                (void)pt_once_finish((uint32_t)(uintptr_t)once
                                     | ((ONCE_FINISH_MASK << ONCE_FINISH_SHIFT)
                                        | (ONCE_LOCKED_MASK << ONCE_LOCKED_SHIFT)));
            }
        }
    }
    return 0;
}

/* pthread_once() API */
int pthread_once(pthread_once_t* once, void (*func)(void))
{
    int32_t     val;
    pttcb_t*    pttcb;
    int         sta = 0;

#if MCOS_CFG_PT_CHECK_ARGUMENTS
 /* Check arguments */
    if ((once == 0)
        || (func == 0)
        || (CHECK_ALIGN(once, sizeof(once->value)) != 0))
    {
        return EINVAL;
    }
#endif

 /* Get own pttcb */
    pttcb = pt_get_pttcb();
    if (pttcb == 0)
    {
        return EPERM;
    }

 /* Loop here until found once finished */
    posix_atomic_purge((void*)once);
    while (((val = (int32_t)posix_atomic_get((void*)&(once->value))) &
        (ONCE_FINISH_MASK << ONCE_FINISH_SHIFT)) == 0)
    {
     /* If once not locked */
        if ((val & (ONCE_LOCKED_MASK << ONCE_LOCKED_SHIFT)) == 0)
        {
            sta = pthread_once_not_locked(once, func, val);
        }

     /* Once now initializing and we must wait */
        else
        {
            sta = pthread_once_locked(once, val, pttcb);
        }
    }

    return sta;
}

int (pthread_equal)(pthread_t t1, pthread_t t2) {
    return t1 == t2;
}
