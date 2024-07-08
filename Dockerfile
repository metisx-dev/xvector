FROM ubuntu:20.04

# Don't ask anything when installing packages
ARG DEBIAN_FRONTEND=nointeractive

RUN apt update
#RUN apt install -y bash

RUN apt install -y software-properties-common
## to install latest gcc
RUN add-apt-repository ppa:ubuntu-toolchain-r/test
RUN apt update
RUN apt install -y sudo
RUN apt install -y vim
RUN apt install -y openssh-server
RUN apt install -y openssh-client
RUN apt install -y curl
RUN apt install -y wget
RUN apt install -y sshfs
#RUN apt install -y linux-headers-6.5.0-21-generic # for 22.04
RUN apt install -y linux-headers-5.15.0-105-generic
RUN apt install -y kmod
RUN apt install -y build-essential
#RUN apt install -y gcc
#RUN apt install -y g++
RUN apt install -y gcc-13
RUN apt install -y g++-13
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 130
RUN update-alternatives --install /usr/bin/cc cc /usr/bin/gcc-13 130
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-13 130
RUN update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-13 130
RUN apt install -y ninja-build
RUN apt install -y make
RUN apt install -y libssl-dev
RUN apt install -y pkg-config
RUN apt install -y libre2-dev
RUN apt install -y flex
RUN apt install -y bison
RUN apt install -y libreadline-dev
RUN apt install -y libboost-all-dev
RUN apt install -y libfmt-dev
RUN apt install -y gdb
RUN apt install -y openjdk-11-jdk
RUN apt install -y python3
RUN apt install -y pip
RUN apt install -y python3-pyelftools
RUN apt install -y python3-pip
RUN apt install -y python3-pandas
RUN apt install -y git

RUN pip install pyserial --upgrade
RUN pip install numpy --upgrade
RUN pip install click --upgrade
RUN pip install pandas --upgrade
RUN pip install bitarray --upgrade
RUN pip install vcd --upgrade
RUN pip install pyvcd --upgrade
RUN pip install pyarrow --upgrade
RUN pip install pexpect --upgrade
RUN pip install requests --upgrade
#
RUN echo "    StrictHostKeyChecking no" > /etc/ssh/ssh_config

#COPY ./reinstall-cmake.sh /tmp/
#RUN chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh "3.28.1" && rm -f /tmp/reinstall-cmake.sh

RUN cd $(mktemp -d -t cmake-XXXXXXXX)
RUN apt purge -y --auto-remove cmake
RUN curl -sSL "https://github.com/Kitware/CMake/releases/download/v3.28.1/cmake-3.28.1-linux-x86_64.sh" -O
RUN chmod +x ./cmake-3.28.1-linux-x86_64.sh
RUN mkdir -p /opt/cmake
RUN ./cmake-3.28.1-linux-x86_64.sh --prefix=/opt/cmake --skip-license
RUN ln -s /opt/cmake/bin/cmake /usr/bin/cmake && \
    ln -s /opt/cmake/bin/cpack /usr/bin/cpack

WORKDIR /xvector
