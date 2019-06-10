## Process this file with automake to generate Makefile.in

AUTOMAKE_OPTIONS = cygnus

INCLUDES = \
	-I$(srcdir)/include \
	-I$(srcdir)/mcos_svc/include \
	-I$(srcdir)/mcos_svc/include/mcos \
	-I$(srcdir)/mcos_svc/include/pt_api \
	-I$(srcdir)/mcos_svc/include/svc \
	-I$(srcdir)/mcos_svc/src/libcgcc \
	-I$(srcdir)/mcos_svc/src/libcgcc/time \
	-I$(srcdir)/mcos_svc/src/libprocess \
	-I$(srcdir)/mcos_svc/src/libnetdb/include \
	-I$(srcdir)/mcos_svc/src/libnetdb/include/irs \
	-I$(srcdir)/mcos_svc/src/libnetdb/include/isc \
	-I$(srcdir)/mcos_svc/src/libnetdb/include/resolv \
	-I$(srcdir)/mcos_svc/src/crt \
	$(NEWLIB_CFLAGS) \
	$(CROSS_CFLAGS) \
	$(TARGET_CFLAGS)

AM_CCASFLAGS = $(INCLUDES)

SUBDIRS = 

SOURCES = \
	mcos_svc/src/crt/get_threadid.S \
	mcos_svc/src/crt/svc_armgcc.S \
	mcos_svc/src/crt/libspace.c \
	mcos_svc/src/crt/lock.c \
	mcos_svc/src/libaio/aio_svc.c \
	mcos_svc/src/libcgcc/libgen/basename.c \
	mcos_svc/src/libcgcc/libgen/dirname.c \
	mcos_svc/src/libcgcc/libgen/errlist.c \
	mcos_svc/src/libcgcc/stdlib/random.c \
	mcos_svc/src/libcgcc/string/strerror.c \
	mcos_svc/src/libcgcc/string/__strerror.c \
	mcos_svc/src/libcgcc/time/asctime.c \
	mcos_svc/src/libcgcc/time/localtime.c \
	mcos_svc/src/libcgcc/time/strftime.c \
	mcos_svc/src/libcgcc/time/strptime.c \
	mcos_svc/src/libcgcc/time/time.c \
	mcos_svc/src/liblfs/lfs_svc.c \
	mcos_svc/src/liblfs/poll.c \
	mcos_svc/src/libmcos/mcos_svc.c \
	mcos_svc/src/libmmap/dlmalloc.c \
	mcos_svc/src/libmmap/libmmap_svc.c \
	mcos_svc/src/libmmap/memalloc.c \
	mcos_svc/src/libmq/mq_svc.c \
	mcos_svc/src/libnetdb/inet/inet_data.c \
	mcos_svc/src/libnetdb/inet/inet_makeaddr.c \
	mcos_svc/src/libnetdb/inet/inet_makeaddr.c \
	mcos_svc/src/libnetdb/irs/dns.c \
	mcos_svc/src/libnetdb/irs/dns_ho.c \
	mcos_svc/src/libnetdb/irs/dns_sv.c \
	mcos_svc/src/libnetdb/irs/gen.c \
	mcos_svc/src/libnetdb/irs/gen_ho.c \
	mcos_svc/src/libnetdb/irs/gen_sv.c \
	mcos_svc/src/libnetdb/irs/getaddrinfo.c \
	mcos_svc/src/libnetdb/irs/gethostent.c \
	mcos_svc/src/libnetdb/irs/getnameinfo.c \
	mcos_svc/src/libnetdb/irs/getservent.c \
	mcos_svc/src/libnetdb/irs/irs_data.c \
	mcos_svc/src/libnetdb/irs/lcl.c \
	mcos_svc/src/libnetdb/irs/lcl_ho.c \
	mcos_svc/src/libnetdb/irs/lcl_sv.c \
	mcos_svc/src/libnetdb/irs/util.c \
	mcos_svc/src/libnetdb/isc/assertions.c \
	mcos_svc/src/libnetdb/isc/ev_streams.c \
	mcos_svc/src/libnetdb/isc/ev_timers.c \
	mcos_svc/src/libnetdb/nameser/ns_name.c \
	mcos_svc/src/libnetdb/nameser/ns_netint.c \
	mcos_svc/src/libnetdb/nameser/ns_samedomain.c \
	mcos_svc/src/libnetdb/resolv/res_comp.c \
	mcos_svc/src/libnetdb/resolv/res_init.c \
	mcos_svc/src/libnetdb/resolv/res_mkquery.c \
	mcos_svc/src/libnetdb/resolv/res_query.c \
	mcos_svc/src/libnetdb/resolv/res_send.c \
	mcos_svc/src/libpipe/pipe_svc.c \
	mcos_svc/src/libposix/src/clib_mutex.c \
	mcos_svc/src/libposix/src/creat.c \
	mcos_svc/src/libposix/src/dirops.c \
	mcos_svc/src/libposix/src/liblock.c \
	mcos_svc/src/libposix/src/environ.c \
	mcos_svc/src/libposix/src/pthread_spinlock.c \
	mcos_svc/src/libposix/src/sysdepend/arm/libposix_atomic.c \
	mcos_svc/src/libposix/src/sysdepend/arm/libposix_atomic_gcc.S \
	mcos_svc/src/libprocess/exit.c \
	mcos_svc/src/libprocess/libinit.c \
	mcos_svc/src/libprocess/libposix_init.c \
	mcos_svc/src/libprocess/libprocess.c \
	mcos_svc/src/libprocess/libprocess_svc.c \
	mcos_svc/src/libprocess/posix_spawnp.c \
	mcos_svc/src/libprocess/launch_proc_main.c \
	mcos_svc/src/libprocess/fork.c \
	mcos_svc/src/libprocess/exec.c \
	mcos_svc/src/libprocess/sys/arch/arm/__fork_armgcc.S \
	mcos_svc/src/libpthread/pthread_barrier_svc.c \
	mcos_svc/src/libpthread/pthread_barrier.c \
	mcos_svc/src/libpthread/pthread.c \
	mcos_svc/src/libpthread/pthread_cond.c \
	mcos_svc/src/libpthread/pthread_cond_svc.c \
	mcos_svc/src/libpthread/pthread_mutex.c \
	mcos_svc/src/libpthread/pthread_mutex_svc.c \
	mcos_svc/src/libpthread/pthread_rwlock.c \
	mcos_svc/src/libpthread/pthread_rwlock_svc.c \
	mcos_svc/src/libpthread/pthread_svc.c \
	mcos_svc/src/libsem/sem_svc.c \
	mcos_svc/src/libsignal/pause.c \
	mcos_svc/src/libsignal/raise.c \
	mcos_svc/src/libsignal/signal.c \
	mcos_svc/src/libsignal/siglongjmp.c \
	mcos_svc/src/libsignal/signal_svc.c \
	mcos_svc/src/libsignal/sigprocmask.c \
	mcos_svc/src/libsignal/sigsetjmp.c \
	mcos_svc/src/libsignal/sigsetops.c \
	mcos_svc/src/libsignal/sigwaitinfo.c \
	mcos_svc/src/libsignal/signal_handler.c \
	mcos_svc/src/libsignal/sys/arch/arm/signal_arm_gcc.S \
	mcos_svc/src/libsocket/htonl.c \
	mcos_svc/src/libsocket/htons.c \
	mcos_svc/src/libsocket/inet_addr.c \
	mcos_svc/src/libsocket/inet_ntoa.c \
	mcos_svc/src/libsocket/inet_ntop.c \
	mcos_svc/src/libsocket/inet_pton.c \
	mcos_svc/src/libsocket/ntohl.c \
	mcos_svc/src/libsocket/ntohs.c \
	mcos_svc/src/libsocket/socket_svc.c \
	mcos_svc/src/libtime/ftime.c \
	mcos_svc/src/libtime/time_svc.c \
	mcos_svc/src/libtime/usleep.c \
	mcos_svc/src/libtimer/timer_svc.c \
	mcos_svc/src/dummy/_Exit.c \
	mcos_svc/src/dummy/asctime_r.c \
	mcos_svc/src/dummy/clock.c \
	mcos_svc/src/dummy/ctime.c \
	mcos_svc/src/dummy/ctime_r.c \
	mcos_svc/src/dummy/execl.c \
	mcos_svc/src/dummy/execle.c \
	mcos_svc/src/dummy/execlp.c \
	mcos_svc/src/dummy/execv.c \
	mcos_svc/src/dummy/execve.c \
	mcos_svc/src/dummy/execvp.c \
	mcos_svc/src/dummy/gmtime.c \
	mcos_svc/src/dummy/gmtime_r.c \
	mcos_svc/src/dummy/isatty.c \
	mcos_svc/src/dummy/lcltime.c \
	mcos_svc/src/dummy/lcltime_r.c \
	mcos_svc/src/dummy/mktime.c \
	mcos_svc/src/dummy/rename.c \
	mcos_svc/src/dummy/tzset.c \
	mcos_svc/src/dummy/mcos_dummy.c \
	mcos_svc/src/stub/alarm.c \
	mcos_svc/src/stub/dlclose.c \
	mcos_svc/src/stub/dlerror.c \
	mcos_svc/src/stub/dlopen.c \
	mcos_svc/src/stub/dlsym.c \
	mcos_svc/src/stub/fenv.c \
	mcos_svc/src/stub/gethostname.c \
	mcos_svc/src/stub/getpagesize.c \
	mcos_svc/src/stub/ifaddrs.c \
	mcos_svc/src/stub/ifname.c \
	mcos_svc/src/stub/lstat.c \
	mcos_svc/src/stub/pathconf.c \
	mcos_svc/src/stub/sbrk.c \
	mcos_svc/src/stub/sigaltstack.c \
	mcos_svc/src/stub/strerror_r.c \
	mcos_svc/src/stub/symlink.c \
	mcos_svc/src/stub/sysconf.c \
	mcos_svc/src/stub/termios.c \
	mcos_svc/src/stub/utimes.c \
	mcos_svc/src/stub/wcsftime.c

ADD_OBJ = 

noinst_LIBRARIES = lib.a
lib_a_SOURCES = $(SOURCES)
lib_a_LIBADD = $(ADD_OBJ)
lib_a_DEPENDENCIES = $(ADD_OBJ)
lib_a_CCASFLAGS = $(AM_CCASFLAGS)
lib_a_CFLAGS = \
	-DALL_STATE \
	-DUSG_COMPAT \
	-DHAVE_SYS_WAIT_H=0 \
	-DTZDIR=0 \
	-DTZDEFAULT=0 \
	-DTZDEFRULES=0 \
	-D__TM_ZONE=tm_zone \
	-D__TM_GMTOFF=tm_gmtoff \
	-DHAVE_INITFINI_ARRAY \
	$(AM_CFLAGS)

all-local: crt0.o mcos_config.o

ACLOCAL_AMFLAGS = -I ../../.. -I ../../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(tooldir)/include/arpa; \
	for i in $(srcdir)/include/arpa/*.h; do \
	  $(INSTALL_DATA) $$i $(DESTDIR)$(tooldir)/include/arpa/`basename $$i`; \
	done; \
	$(mkinstalldirs) $(DESTDIR)$(tooldir)/include/bits; \
	for i in $(srcdir)/include/bits/*.h; do \
	  $(INSTALL_DATA) $$i $(DESTDIR)$(tooldir)/include/bits/`basename $$i`; \
	done; \
	$(mkinstalldirs) $(DESTDIR)$(tooldir)/include/linux; \
	for i in $(srcdir)/include/linux/*.h; do \
	  $(INSTALL_DATA) $$i $(DESTDIR)$(tooldir)/include/linux/`basename $$i`; \
	done; \
	$(mkinstalldirs) $(DESTDIR)$(tooldir)/include/machine; \
	for i in $(srcdir)/include/machine/*.h; do \
	  $(INSTALL_DATA) $$i $(DESTDIR)$(tooldir)/include/machine/`basename $$i`; \
	done; \
	$(mkinstalldirs) $(DESTDIR)$(tooldir)/include/net; \
	for i in $(srcdir)/include/net/*.h; do \
	  $(INSTALL_DATA) $$i $(DESTDIR)$(tooldir)/include/net/`basename $$i`; \
	done; \
	$(mkinstalldirs) $(DESTDIR)$(tooldir)/include/netinet; \
	for i in $(srcdir)/include/netinet/*.h; do \
	  $(INSTALL_DATA) $$i $(DESTDIR)$(tooldir)/include/netinet/`basename $$i`; \
	done; \
	$(mkinstalldirs) $(DESTDIR)$(tooldir)/include/sys; \
	for i in $(srcdir)/include/sys/*.h; do \
	  $(INSTALL_DATA) $$i $(DESTDIR)$(tooldir)/include/sys/`basename $$i`; \
	done
