# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.245.0/containers/cpp/.devcontainer/base.Dockerfile

# [Choice] Debian / Ubuntu version (use Debian 11, Ubuntu 18.04/22.04 on local arm64/Apple Silicon): debian-11, debian-10, ubuntu-22.04, ubuntu-20.04, ubuntu-18.04
ARG VARIANT="bullseye"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

# [Optional] Install CMake version different from what base image has already installed. 
# CMake reinstall choices: none, 3.21.5, 3.22.2, or versions from https://cmake.org/download/
ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="none"

# Optionally install the cmake for vcpkg
COPY ./reinstall-cmake.sh /tmp/
RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
        chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

# [Optional] Uncomment this section to install additional vcpkg ports.
# RUN su vscode -c "${VCPKG_ROOT}/vcpkg install <your-port-name-here>"

# [Optional] Uncomment this section to install additional packages.
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends <your-package-list-here>

RUN apt update && apt upgrade -y

RUN apt install -y mlocate
RUN apt install -y neovim

# use localhost ssl
# RUN apt install -y mkcert
RUN apt install -y libnss3-tools

RUN wget https://github.com/FiloSottile/mkcert/releases/download/v1.4.3/mkcert-v1.4.3-linux-amd64 \
    && mv mkcert* mkcert \
    && install ./mkcert /usr/bin/ \
    && rm ./mkcert

# install htpasswd for bcrypt
RUN apt-get install -y apache2-utils

# install dependency for drogon
RUN apt install -y \
    git \
    gcc \
    g++ \
    cmake \
    libjsoncpp-dev \
    uuid-dev \
    openssl \
    libssl-dev \
    zlib1g-dev 

# install drogon documentation
RUN apt install -y \
    doxygen \
    doxygen-doxyparse

# Could NOT find Doxygen (missing: DOXYGEN_EXECUTABLE) 
# build drogon
RUN git clone https://github.com/an-tao/drogon -b v1.7.5 \
    && cd drogon \
    && git submodule update --init \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make && make install
# 失敗の原因切り分けのため、情報として置いておく。
# 本番作成用のコンテナなら削除すること。
    # && cd ../../ \
    # && rm -rf drogon

RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN updatedb
