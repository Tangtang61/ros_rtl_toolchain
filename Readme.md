# ros_rtl_toolchain

ros_rtl_toolchainは、ROS-RTLを導入するためのレポジトリです。  
ROS-RTLとは、eMCOS環境でのROSアプリケーションの実行に必要なRun Time Libraryです。  
eMCOSの詳細は以下を参照してください。  
https://www.esol.co.jp/embedded/emcos.html

以下に導入手順を記載します。  

[補足]  
- ROS_RTL上で動作する、ライブラリ群(ros_rtl_libリポジトリ)、ROS kinetic(ros_rtl_kineticリポジトリ)の導入手順を含みます。  
- ros_rtl_toolchain、ros_rtl_lib、ros_rtl_kineticには依存関係が存在します。  
  必ず下記の順番で導入（ビルド）してください。  
  1. ros_rtl_toolchain  
  1. ros_rtl_lib  
  1. ros_rtl_kinetic

# 目次

1. [機材環境](#機材環境)
1. [ビルド環境のコンテナの生成](#ビルド環境のコンテナの生成)
1. [ROS-RTLリポジトリの取得](#ROS-RTLリポジトリの取得)
1. [ROS-RTLのアーカイブ生成](#ROS-RTLのアーカイブ生成)
   1. [ros_rtl_toolchainのアーカイブ生成](##ros_rtl_toolchainのアーカイブ生成)
   1. [ros_rtl_libのアーカイブ生成](##ros_rtl_libのアーカイブ生成)
   1. [ros_rtl_kineticのアーカイブ生成](##ros_rtl_kineticのアーカイブ生成)
1. [ROS-RTLのビルド](#ROS-RTLのビルド)
   1. [ros_rtl_toolchainのビルド](##ros_rtl_toolchainのビルド)
   1. [ros_rtl_libのビルド](##ros_rtl_libのビルド)
   1. [ros_rtl_kineticのビルド](##ros_rtl_kineticのビルド)
1. [サンプルプログラムのビルド](#サンプルプログラムのビルド)
1. [ライセンス](#ライセンス)
1. [コンタクト](#コンタクト)

# 機材環境

PCの推奨スペックは以下のとおりです。また、Docker環境のインストールが必要です。

```
OS : Ubuntu 16.04 LTS
CPU: Core-i7以上 (スレッド数が12以上)
RAM: 16GBytes以上
HDD: 1TBytes以上
```

# ビルド環境のコンテナの生成

ROS-RTLのアーカイブをビルドするためのコンテナを生成する手順を記載します。  
ターミナルに以下のコマンドを入力し、アーカイブを保存するフォルダを生成します。  
(以降同様に、ターミナルに入力するコマンドに対して説明を記載します)

````
% sudo mkdir -p /work/share/archives
````

生成したフォルダの書き込み権限を取得します。

````
% sudo chmod -R a+w /work/share/
````

UbuntuのDockerのイメージを取得します。  

````
% sudo docker pull ubuntu:16.04
````

Dockerfileのワークフォルダを生成します。

```
% mkdir -p ~/ros_rtl_container
```

Dockerfileを生成します。

```
% cd ~/ros_rtl_container
% vi Dockerfile
```

ファイルの内容は以下のとおりです。

```
FROM ubuntu:16.04

ENV DEBIAN_FRONTEND noninteractive
ARG NONPV_USER_ID=cross-test
ARG NONPV_USER_PW=cross-test!
ARG NONPV_USER_HM=/home/$NONPV_USER_ID

RUN apt-get clean && apt-get update && apt-get install -y locales
RUN locale-gen en_US.UTF-8
RUN apt-get update && apt-get install -y \
    vim \
    sudo \
    wget \
    zip \
    openssh-server \
    cmake \
    python-empy \
    subversion \
    build-essential \
    freebsd-buildutils \
    pxz \
    libfdt-dev \
    libfdt1 \
    autoconf \
    automake \
    bison \
    flex \
    texinfo \
    libc6-i386 \
    && rm -rf /var/lib/apt/lists/*
RUN apt-get update && apt-get install -y lsb-release \
    && rm -rf /var/lib/apt/lists/*

RUN /bin/bash -c 'apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 \
    --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116'    

RUN /bin/bash -c 'echo "deb http://packages.ros.org/ros/ubuntu xenial main" > \
    /etc/apt/sources.list.d/ros-latest.list'

RUN apt-get update && apt-get install -y \
    python-rosdep \
    python-rosinstall-generator \
    python-wstool \
    python-rosinstall \   
    && rm -rf /var/lib/apt/lists/*
RUN rosdep init \
    && rosdep update

RUN useradd -d $NONPV_USER_HM -m -s /bin/bash $NONPV_USER_ID
RUN echo $NONPV_USER_ID:$NONPV_USER_PW | chpasswd
RUN echo "$NONPV_USER_ID ALL=NOPASSWD: ALL" >> /etc/sudoers
RUN sudo -i -u $NONPV_USER_ID rosdep update

RUN sudo chmod 777 -R /opt

ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8
```

Dockerイメージを生成します。  

```
% cd ~/ros_rtl_container
% sudo docker build -t cross_test_base ./
```

Dockerイメージからコンテナを生成します。  
このとき、コンテナをアタッチする際に必要なイメージのハッシュキーが出力されます。  
下記の2222は、開発環境へのSSHポート転送用のポートです。  
複数のコンテナを生成する場合は、well-knownポートに重複しないものを設定してください。

```
% sudo docker run -p 2222:22 -t -id --name "cross-test1" -v /work/share:/work/share cross_test_base /bin/bash
```

コンテナをアタッチします。

```
% sudo docker attach <"docker run"コマンド入力時、出力したイメージのハッシュキー>
```

アタッチ後、リモートログインするため、SSHサーバを起動します。  
SSHサーバの起動後、"crtl+p+q"でコンテナをデタッチします。

```
% /etc/init.d/ssh start
```

SSH経由でコンテナにリモートログインします。  
以降の手順はコンテナ上で実施してください。

```
ssh cross-test@<PCのIPアドレス> -p 2222
```

リモートログインに必要なアカウント情報は以下のとおりです。

```
User ID: cross-test
Password: cross-test!
```

# ROS-RTLリポジトリの取得

ROS-RTLリポジトリを取得します。

````
cd ~/
git clone https://github.com/esol-community/ros_rtl_toolchain.git
git clone https://github.com/esol-community/ros_rtl_lib.git
git clone https://github.com/esol-community/ros_rtl_kinetic.git
````

# ROS-RTLのアーカイブ生成

以下の3点のROS-RTLのアーカイブを生成します。

- ros_rtl_toolchain
- ros_rtl_lib
- ros_rtl_kinetic

## ros_rtl_toolchainのアーカイブ生成

ros_rtl_toolchainのアーカイブを生成します。

````
% cd ~/ros_rtl_toolchain/script
% bash gen_archives_toolchain.sh
````

以下の内容がコンソールに出力されたことを確認してください。

```
newlib-2.5.0.20170922.tar.gz :verify success
```

## ros_rtl_libのアーカイブ生成

ros_rtl_libのアーカイブを生成します。

````
% cd ~/ros_rtl_lib/script
% bash gen_archives_lib.sh
````

以下の内容がコンソールに出力されたことを確認してください。

```
rtems-4.10.2.tar.bz2 :verify success
```

## ros_rtl_kineticのアーカイブ生成

ros_rtl_kineticのアーカイブを生成します。ros_rtl_kineticのアーカイブ生成時には、同時にソースファイルが展開されます。

````
% cd ~/ros_rtl_kinetic/script
% bash gen_archives_kinetic.sh
````

以下の内容がコンソールに出力されたことを確認してください。

```
update complete.
```

# ROS-RTLのビルド

## ros_rtl_toolchainのビルド

ros_rtl_toolchainをビルドします。  
スクリプトの引数で、ビルド時に並列処理するジョブ数を指定しています。  
以下の例では、8を指定しています。必要に応じて修正してください。

```
% cd ~/ros_rtl_toolchain/script
% bash build_toolchain.sh 8
```

以下の内容がコンソールに出力されたことを確認してください。

```
building the toolchain is complete.
```

## ros_rtl_libのビルド

ros_rtl_libをビルドします。  
スクリプトの引数で、ビルド時に並列処理するジョブ数を指定しています。  
以下の例では、8を指定しています。必要に応じて修正してください。

```
% cd ~/ros_rtl_lib/script
% bash build_lib.sh 8
```

以下の内容がコンソールに出力されたことを確認してください。

```
building the googletest library is complete.
```

## ros_rtl_kineticのビルド

ros_rtl_kineticをビルドします。

```
% cd ~/ros_rtl_kinetic/script
% bash build_kinetic.sh
```

以下の内容がコンソールに出力されたことを確認してください。

```
building the ros kinetic is complete.
```

# サンプルプログラムのビルド

以下の2点の実行ファイルを生成します。

- talker
- listener

ソースフォルダを生成します。

```
% mkdir ~/ros_tutorials
```

GITからros_tutorialsをsrcフォルダにダウンロードします。

```
% cd ~/ros_tutorials
% git clone -b kinetic-devel https://github.com/ros/ros_tutorials.git src
```

Qtに対応していないため、turtlesimをcatkinビルドの対象外にします。

```
% touch ~/ros_tutorials/src/turtlesim/CATKIN_IGNORE
```

ビルドスクリプトを生成します。

```
% cd ~/ros_tutorials
% vi setup_to_build_ros_tutorials.sh
```

ファイルの内容は以下のとおりです。

```
#!/bin/bash

set -e

BUILD_AARCH_NAME=aarch64-elf-mcos
BUILD_GCC_DIR=/opt/aarch64_mcos
BUILD_TOOLCHAIN_PATH=/opt/aarch64_mcos/aarch64-elf-mcos/cmake/aarch64_elf_mcos_ros_toolchain.cmake

export PATH=${BUILD_GCC_DIR}/bin/:${PATH}

cd `dirname $0`

rm -rf ./src/CMakeLists.txt
ln -s ~/ros_rtl_kinetic/source/ros_kinetic/install_isolated/share/catkin/cmake/toplevel.cmake ./src/CMakeLists.txt

if [ -d ${PWD}/build ]; then
    rm -rf ${PWD}/build
    rm -rf ${PWD}/devel
fi

source ~/ros_rtl_kinetic/source/ros_kinetic/install_isolated/setup.bash

echo 'Execute catkin_make.'
catkin_make -DCMAKE_FIND_DEBUG_MODE=1 -DCMAKE_TOOLCHAIN_FILE=${BUILD_TOOLCHAIN_PATH} -D_CMAKE_MCOS_ROS_RTL=1 > log_rostutorials_catkinmake.log 2>&1

echo "Completed."
```

ros_tutorialsをビルドします。

```
% cd ~/ros_tutorials
% bash setup_to_build_ros_tutorials.sh
```

以下の内容がコンソールに出力されたことを確認してください。

```
Completed.
```

実行ファイルが生成されていることを確認してください。

```
% test -f ~/ros_tutorials/devel/lib/roscpp_tutorials/talker
% test -f ~/ros_tutorials/devel/lib/roscpp_tutorials/listener
```

# ライセンス

レポジトリ内の各ソースコードには、各ヘッダファイルのライセンスが適用されます。

# コンタクト

本レポジトリに関する問い合わせ先は以下のメールアドレスにお願いいたします。  
embedded-ros@esol.co.jp
