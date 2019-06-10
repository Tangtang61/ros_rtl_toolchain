#!/bin/bash

set -e

ARC_DIR=/work/share/archives
TOOL_DIR=${ARC_DIR}/toolchain

BINUTIL_MD5SUM='87978750715952fbb9f870940e9dcbeb'
GCC_MD5SUM='0f70424213b4a1113c04ba66ddda0c1f'
GMP_MD5SUM='f58fa8001d60c4c77595fbbb62b63c1d'
MPC_MD5SUM='d6a1d5f8ddea3abd2cc3e98f58352d26'
MPFR_MD5SUM='51bfdbf81553966c8d43808122cc81b3'
NEWLIB_MD5SUM='499fb1239b44faf2e4a0873f17fe61ff'


function get_archive() {
    DL_URL=${1}
    MD5_VALUE=${2}

    file_name=${DL_URL##*/}
    wget ${DL_URL} -P ${TOOL_DIR}
    get_md5_value=$(md5sum ${TOOL_DIR}/${file_name} | cut -d " " -f 1)

    if [ ${get_md5_value} = ${MD5_VALUE} ]; then
        echo "${file_name} :verify success" >&1
    else
        echo "${file_name} :verify error" >&2
        exit
    fi
}


rm -rf ${TOOL_DIR}
mkdir -p ${TOOL_DIR}

get_archive https://ftp.gnu.org/gnu/binutils/binutils-2.29.tar.xz ${BINUTIL_MD5SUM}
get_archive http://ftp.tsukuba.wide.ad.jp/software/gcc/releases/gcc-5.5.0/gcc-5.5.0.tar.xz ${GCC_MD5SUM}
get_archive https://ftp.gnu.org/gnu/gmp/gmp-6.1.2.tar.xz ${GMP_MD5SUM}
get_archive https://ftp.gnu.org/gnu/mpc/mpc-1.0.3.tar.gz ${MPC_MD5SUM}
get_archive https://www.mpfr.org/mpfr-3.1.6/mpfr-3.1.6.tar.xz ${MPFR_MD5SUM}
get_archive ftp://sourceware.org/pub/newlib/newlib-2.5.0.20170922.tar.gz ${NEWLIB_MD5SUM}
