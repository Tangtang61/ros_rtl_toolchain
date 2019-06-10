#!/bin/bash
set -e

BUILD_PROC_NUM=$1
GCC_PREFIX=/opt/aarch64_mcos
SCRIPT_PATH=`readlink -f $0`
SCRIPT_BASE=`dirname ${SCRIPT_PATH}`
GCC_BUILD_BASE=${SCRIPT_BASE}/build
GCC_SRC_BASE=${SCRIPT_BASE}

rm -rf ${GCC_PREFIX}

patch -u -p1 -d newlib-2.5.0.20170922 < patch_newlib-2.5.0.20170922_emcos.patch
patch -u -p1 -d binutils-2.29 < patch_binutil-2.29_emcos.patch
patch -u -p1 -d gcc-5.5.0 < patch_gcc-5.5.0_emcos.patch
patch -u -p1 -d mpfr-3.1.6 < patch_mpfr-3.1.6_v2_emcos.patch

function start_echo ()
{
    echo "***** building the ${1}. *****"
}
function end_echo ()
{
    echo "***** building the ${1} was completed. toolchain is installed in ${GCC_PREFIX} *****"
}
function exec_with_errproc ()
{
    set +e
    $1
    if [ $? -ne 0 ]; then
        echo "ERROR(${?}) : ${1}"
        exit 1
    fi
    set -e
}

start_echo "binutils"
mkdir -p ${GCC_BUILD_BASE}/binutils
cd ${GCC_BUILD_BASE}/binutils
${GCC_SRC_BASE}/binutils-2.29/configure --target=arm-elf --prefix=${GCC_PREFIX} \
    --target=aarch64-elf-mcos --enable-interwork \
    --disable-multilib 2>&1 | tee configure.out
exec_with_errproc "make -j${BUILD_PROC_NUM} all"
exec_with_errproc "make install"
end_echo "binutils"

export PATH=${GCC_PREFIX}/bin:$PATH

start_echo "gmp"
mkdir -p ${GCC_BUILD_BASE}/gmp
cd ${GCC_BUILD_BASE}/gmp
${GCC_SRC_BASE}/gmp-6.1.2/configure --prefix=${GCC_PREFIX} 2>&1 | \
    tee configure.out
exec_with_errproc "make -j${BUILD_PROC_NUM} all"
exec_with_errproc "make install"
exec_with_errproc "make check"
end_echo "gmp"

start_echo "mpfr"
mkdir -p ${GCC_BUILD_BASE}/mpfr
cd ${GCC_BUILD_BASE}/mpfr
${GCC_SRC_BASE}/mpfr-3.1.6/configure --prefix=${GCC_PREFIX} \
	       --with-gmp=${GCC_PREFIX} 2>&1 | tee configure.out
exec_with_errproc "make -j${BUILD_PROC_NUM} all"
exec_with_errproc "make install"
end_echo "mpfr"

start_echo "mpc"
mkdir -p ${GCC_BUILD_BASE}/mpc
cd ${GCC_BUILD_BASE}/mpc
${GCC_SRC_BASE}/mpc-1.0.3/configure --prefix=${GCC_PREFIX} \
    --with-gmp=${GCC_PREFIX} \
    --with-mpfr=${GCC_PREFIX} 2>&1 | tee configure.out
exec_with_errproc "make -j${BUILD_PROC_NUM} all"
exec_with_errproc "make install"
end_echo "mpc"

export CFLAGS_FOR_TARGET="-v -g"
export CXXFLAGS_FOR_TARGET="-v -g"
export CXXFLAGS=-DNO_IMPLICIT_EXTERN_C=1

start_echo "aarch64-elf-mcos"
mkdir -p ${GCC_BUILD_BASE}/gcc
cd ${GCC_BUILD_BASE}/gcc
${GCC_SRC_BASE}/gcc-5.5.0/configure --prefix=${GCC_PREFIX} --target=aarch64-elf-mcos --enable-interwork \
    --disable-multilib --enable-languages="c,c++" --with-newlib --disable-shared \
    --enable-threads=posix --enable-libstdcxx-threads --enable-libstdcxx-time \
    --with-headers=${GCC_SRC_BASE}/newlib-2.5.0.20170922/newlib/libc/include \
    --with-gmp=${GCC_PREFIX} --with-mpfr=${GCC_PREFIX} \
    --with-mpc=${GCC_PREFIX} 2>&1 | tee configure.out
exec_with_errproc "make -j${BUILD_PROC_NUM} all-gcc"
exec_with_errproc "make install-gcc"

mkdir -p ${GCC_BUILD_BASE}/newlib
cd ${GCC_BUILD_BASE}/newlib
${GCC_SRC_BASE}/newlib-2.5.0.20170922/configure --target=aarch64-elf-mcos \
    --prefix=${GCC_PREFIX} --enable-threads --enable-newlib-io-c99-formats \
    --disable-newlib-supplied-syscalls \
    --enable-interwork --disable-multilib --enable-newlib-mb 2>&1  | tee  configure.out
exec_with_errproc "make -j${BUILD_PROC_NUM} all"
exec_with_errproc "make install"

cp ${SCRIPT_BASE}/build/newlib/aarch64-elf-mcos/newlib/libc/sys/mcos/mcos_config.o ${GCC_PREFIX}/aarch64-elf-mcos/lib/mcos_config.o

cd ${GCC_BUILD_BASE}/gcc
exec_with_errproc "make -j${BUILD_PROC_NUM} all"
exec_with_errproc "make install --"
end_echo "aarch64-elf-mcos"

cp ${SCRIPT_BASE}/build/newlib/aarch64-elf-mcos/newlib/crt0.o ${GCC_PREFIX}/lib/gcc/aarch64-elf-mcos/5.5.0/crt0.o
cp -f ${SCRIPT_BASE}/build/newlib/aarch64-elf-mcos/newlib/crt0.o ${GCC_PREFIX}/aarch64-elf-mcos/lib/crt0.o

rm -rf ${GCC_PREFIX}/aarch64-elf-mcos/sys-include

# Create empty libraries required by the options -lpthread and/or -ld.
${GCC_PREFIX}/bin/aarch64-elf-mcos-ar rsc ${GCC_PREFIX}/aarch64-elf-mcos/lib/libpthread.a ${SCRIPT_BASE}/build/newlib/aarch64-elf-mcos/newlib/libc/sys/mcos/lib_a-mcos_dummy.o
${GCC_PREFIX}/bin/aarch64-elf-mcos-ar rsc ${GCC_PREFIX}/aarch64-elf-mcos/lib/libdl.a ${SCRIPT_BASE}/build/newlib/aarch64-elf-mcos/newlib/libc/sys/mcos/lib_a-mcos_dummy.o
${GCC_PREFIX}/bin/aarch64-elf-mcos-ar rsc ${GCC_PREFIX}/aarch64-elf-mcos/lib/librt.a ${SCRIPT_BASE}/build/newlib/aarch64-elf-mcos/newlib/libc/sys/mcos/lib_a-mcos_dummy.o
