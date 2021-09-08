FROM gitpod/workspace-base:latest

RUN sudo apt update && sudo apt upgrade -y

# [drogon install](https://github.com/drogonframework/drogon/wiki/ENG-02-Installation)
RUN sudo apt install -y \
    cmake \
    libjsoncpp-dev \
    uuid-dev \
    openssl \
    libssl-dev \
    zlib1g-dev \

RUN git clone https://github.com/an-tao/drogon \
    && cd drogon \
    && git submodule update --init \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make && sudo make install \
