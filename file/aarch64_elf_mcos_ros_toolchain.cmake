set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

SET(CMAKE_C_COMPILER   aarch64-elf-mcos-gcc)
SET(CMAKE_CXX_COMPILER aarch64-elf-mcos-g++)
SET(CMAKE_ASSEMBLER    aarch64-elf-mcos-as)
SET(CMAKE_LINKER       aarch64-elf-mcos-ld)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(BUILD_USER_ID    $ENV{BUILD_USER_ID})
set(BUILD_AARCH_NAME aarch64-elf-mcos)
set(BUILD_GCC_PREFIX /opt/aarch64_mcos)

set(BUILD_TESTING 0)
set(COMPILE_EXAMPLES 0)
set(CMAKE_VERBOSE_MAKEGILE ON)

add_compile_options(-nostdinc -v -g -O2)

# for the fomral newlib libc 
add_definitions(-D__TM_ZONE=tm_zone)
add_definitions(-D__TM_GMTOFF=tm_gmtoff)
SET(CMAKE_C_COMPILER_FORCED 1)
SET(CMAKE_CXX_COMPILER_FORCED 1)
SET(BUILD_SHARED_LIBS BOOL=OFF)

# for ROS1
set(ROS_BUILD_SHARED_LIBS BOOL=OFF)
set(ROS_BUILD_STATIC_LIBS BOOL=ON)
set(ROS_BUILD_STATIC_EXES BOOL=ON)
set(CMAKE_INCLUDE_DIRECTORIES_BEFORE=ON)
set(RT_LIBRARY "/opt/aarch64_mcos/aarch64-elf-mcos/lib/libc.a")
set(BOOST_ROOT "/opt/aarch64_mcos/aarch64-elf-mcos")
set(BOOST_LIBRARYDIR "/opt/aarch64_mcos/aarch64-elf-mcos/lib")
set(BOOST_INCLUDEDIR "/opt/aarch64_mcos/aarch64-elf-mcos/include")
set(console_bridge_DIR "/opt/aarch64_mcos/aarch64-elf-mcos/lib/console_bridge/cmake")
set(lz4_LIBRARIES "/opt/aarch64_mcos/aarch64-elf-mcos/lib/liblz4.a")
set(lz4_INCLUDE_DIRS "/opt/aarch64_mcos/aarch64-elf-mcos/include")
set(BZIP2_LIBRARIES "/opt/aarch64_mcos/aarch64-elf-mcos/lib/libbz2.a")
set(BZIP2_INCLUDE_DIR "/opt/aarch64_mcos/aarch64-elf-mcos/include")
set(Eigen3_DIR "/opt/aarch64_mcos/aarch64-elf-mcos/share/eigen3/cmake")

set(EIGEN_ROOT "/opt/aarch64_mcos/aarch64-elf-mcos/")
set(FLANN_ROOT "/opt/aarch64_mcos/aarch64-elf-mcos/")
set(QHULL_ROOT "/opt/aarch64_mcos/aarch64-elf-mcos/")
set(QHULL_INCLUDE_DIR "/opt/aarch64_mcos/aarch64-elf-mcos/include")
set(PCL_DIR "/opt/aarch64_mcos/aarch64-elf-mcos/share/pcl-1.7")
set(TinyXML2_ROOT_DIR "/opt/aarch64_mcos/aarch64-elf-mcos")
set(UUID_INCLUDE_DIRS "/opt/aarch64_mcos/aarch64-elf-mcos/include")
set(UUID_LIBRARIES "/opt/aarch64_mcos/aarch64-elf-mcos/lib/libuuid.a")
set(Poco_INCLUDE_DIR "/opt/aarch64_mcos/aarch64-elf-mcos/include")
set(Poco_LIBRARY_DIR "/opt/aarch64_mcos/aarch64-elf-mcos/lib")
set(Poco_LIBRARIES "/opt/aarch64_mcos/aarch64-elf-mcos/lib/libPocoFoundation.a")
set(ASIO_INCLUDE_DIR "/opt/aarch64_mcos/aarch64-elf-mcos/include")
set(TinyXML_ROOT_DIR "/opt/aarch64_mcos/aarch64-elf-mcos")
set(urdfdom_headers_DIR "/opt/aarch64_mcos/aarch64-elf-mcos/share/urdfdom_headers/cmake")
set(urdfdom_DIR "/opt/aarch64_mcos/aarch64-elf-mcos/share/urdfdom/cmake")

add_definitions(-DCLOCK_MONOTONIC=1)
add_definitions(-D__linux__=1)
add_definitions(-D_GLIBCXX_HAS_GTHREADS=1)
add_definitions(-D_GLIBCXX__PTHREADS=1)
add_definitions(-D__sizeof_ptr=8)
add_definitions(-DGTEST_HAS_CLONE=0)
add_definitions(-DBOOST_ASIO_DISABLE_EPOLL=1)
add_definitions(-DBOOST_ASIO_DISABLE_EVENTFD=1)
add_definitions(-DASIO_DISABLE_EPOLL=1)
add_definitions(-DASIO_DISABLE_EVENTFD=1)
add_definitions(-DPOCO_NO_INOTIFY=1)
#add_definitions(-DEIGEN_DONT_VECTORIZE=1)
#add_definitions(-DEIGEN_DONT_ALIGN_STATICALLY=1)
add_definitions(-DTIXML_USE_STL=1)

#for boost
include_directories(/opt/aarch64_mcos/lib/gcc/aarch64-elf-mcos/5.5.0/../../../../aarch64-elf-mcos/include)
include_directories(/opt/aarch64_mcos/lib/gcc/aarch64-elf-mcos/5.5.0/include-fixed)
include_directories(/opt/aarch64_mcos/lib/gcc/aarch64-elf-mcos/5.5.0/include)

#for eMCOS RTL include path
include_directories(/home/$ENV{BUILD_USER_ID}/source/ros_rtl/toolchain/mcos-svc/include/mcos)

#for libc test's os_mmap_gcc.h include path
include_directories(/home/$ENV{BUILD_USER_ID}/source/ros_rtl/toolchain/mcos-svc/include/misc)
include_directories(/opt/aarch64_mcos/aarch64-elf-mcos/include/c++/5.5.0)

#for C++
include_directories(/opt/aarch64_mcos/aarch64-elf-mcos/include/c++/5.5.0/backward)
include_directories(/opt/aarch64_mcos/aarch64-elf-mcos/include/c++/5.5.0/aarch64-elf-mcos)

