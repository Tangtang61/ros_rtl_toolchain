#!/bin/bash
set -e

if [ -z "$1" ]; then
    echo "Usage: `basename $0` <job number>"
    exit 1
fi

BUILD_PROC_NUM=$1

SCRIPT_PATH=`readlink -f $0`
SCRIPT_DIR=`dirname ${SCRIPT_PATH}`
REPO_BASE=${SCRIPT_DIR}/../../ros_rtl_toolchain
RTL_GCC_BUILD_BASE=${REPO_BASE}/source/ros_rtl/toolchain/mcos-gcc
RTL_LOG_BASE=${REPO_BASE}/log
PATCH_DIR=${REPO_BASE}/patch
FILE_DIR=${REPO_BASE}/file
SCR_DIR=${REPO_BASE}/script
TOOL_ARC_DIR=/work/share/archives/toolchain
CMAKE_DIR=/opt/aarch64_mcos/aarch64-elf-mcos/cmake/

rm -rf /opt/aarch64_mcos/

if [ ! -d ${RTL_LOG_BASE} ]
then
    mkdir ${RTL_LOG_BASE}
fi

rm -rf ${RTL_GCC_BUILD_BASE}
mkdir -p ${RTL_GCC_BUILD_BASE}

tar xf ${TOOL_ARC_DIR}/binutils-2.29.tar.xz -C ${RTL_GCC_BUILD_BASE}
tar xf ${TOOL_ARC_DIR}/gcc-5.5.0.tar.xz -C ${RTL_GCC_BUILD_BASE}
tar xf ${TOOL_ARC_DIR}/gmp-6.1.2.tar.xz -C ${RTL_GCC_BUILD_BASE}
tar xf ${TOOL_ARC_DIR}/mpc-1.0.3.tar.gz -C ${RTL_GCC_BUILD_BASE}
tar xf ${TOOL_ARC_DIR}/mpfr-3.1.6.tar.xz -C ${RTL_GCC_BUILD_BASE}
tar xf ${TOOL_ARC_DIR}/newlib-2.5.0.20170922.tar.gz -C ${RTL_GCC_BUILD_BASE}

cp -af ${PATCH_DIR}/* ${RTL_GCC_BUILD_BASE}
cp -af ${FILE_DIR}/mcos ${RTL_GCC_BUILD_BASE}/newlib-2.5.0.20170922/newlib/libc/sys/

echo "building the toolchain."
cp -af ./_make_toolchain.sh ${RTL_GCC_BUILD_BASE}
pushd ${RTL_GCC_BUILD_BASE} > /dev/null
set +e
./_make_toolchain.sh ${BUILD_PROC_NUM} > ${RTL_LOG_BASE}/build_toolchain.log 2>&1
if [ $? -ne 0 ]; then
    echo "*** building the toolchain is failed. ***"
else
    if [ ! -d ${CMAKE_DIR} ]
    then
        mkdir ${CMAKE_DIR}
    fi
    cp -af ${FILE_DIR}/aarch64_elf_mcos_ros_toolchain.cmake ${CMAKE_DIR}
    echo "building the toolchain is complete."
fi
popd > /dev/null
