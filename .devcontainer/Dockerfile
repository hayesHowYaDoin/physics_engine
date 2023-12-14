# Use Ubuntu as the base image
FROM ubuntu:20.04
LABEL maintainer="Jordan Hayes jordanhayes98@gmail.com"

# Configure timezone
ENV DEBIAN_FRONTEND=noninteractive 
ENV TZ=America/New_York
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Update and install basic packages
RUN apt-get update
RUN apt-get install -y build-essential git openssh-server gdb pkg-config valgrind systemd-coredump nano

# GCC 13
RUN echo "************************ GCC 13 ************************"
RUN apt-get install -y software-properties-common
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test
RUN apt-get update
RUN apt-get install -y gcc-13 g++-13

# CMake 3.28
RUN echo "************************ cmake ************************"
ADD https://cmake.org/files/v3.28/cmake-3.28.0-linux-x86_64.sh /cmake-3.28.0-linux-x86_64.sh
RUN mkdir /opt/cmake
RUN sh /cmake-3.28.0-linux-x86_64.sh --prefix=/opt/cmake --skip-license
RUN ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake
RUN cmake --version

# Ninja
RUN echo "************************ Ninja ************************"
RUN apt-get install -y curl unzip
RUN curl -L https://github.com/ninja-build/ninja/releases/latest/download/ninja-linux.zip -o ninja-linux.zip
RUN unzip ninja-linux.zip -d /usr/local/bin/
RUN rm ninja-linux.zip

# google benchmark
RUN echo "************************ google benchmark ************************"
RUN git clone https://github.com/google/benchmark
RUN mkdir -p  benchmark/build && cd benchmark/build
WORKDIR "benchmark/build"
RUN cmake -DCMAKE_CXX_FLAGS=-std=c++1z   -DBENCHMARK_DOWNLOAD_DEPENDENCIES=TRUE   -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON ../ && cmake --build .  --parallel && cmake --install .
WORKDIR "/"
RUN rm -rf benchmark

# google test
RUN echo "************************ google test ************************"
RUN git clone https://github.com/google/googletest
RUN mkdir -p googletest/build && cd googletest/build
WORKDIR "googletest/build"
RUN cmake -DCMAKE_CXX_FLAGS=-std=c++1z   -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON ../ && cmake --build .  --parallel && cmake --install .
WORKDIR "/"
RUN rm -rf googletest

# Uninstall standard version of GCC
RUN apt-get remove -y gcc-9 g++-9
