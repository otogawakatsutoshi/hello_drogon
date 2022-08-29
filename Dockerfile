FROM gcc:12.2.0-bullseye as builder

ENV BUILD_TYPE=Release
RUN apt update && apt upgrade -y
# create drogon_ctl
RUN apt install --no-install-recommends -y \
    git \
    gcc \
    g++ \
    cmake \
    libjsoncpp-dev \
    uuid-dev \
    openssl \
    libssl-dev \
    zlib1g-dev 

# install optional dependency
RUN apt install --no-install-recommends -y postgresql-server-dev-all

WORKDIR /home/tmp

RUN git clone https://github.com/an-tao/drogon -b v1.7.5 \
    && cd drogon \
    && git submodule update --init \
    && mkdir build \
    && cd build \
    && cmake .. -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
    && make && make install

# install command line parser
RUN git clone https://github.com/p-ranav/argparse.git -b v2.6 \
    && cd argparse \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make && make install

# controller とかviewとか。
COPY ./ ./

RUN mkdir build \
    && cd build \
    && mkdir test \
    && cmake .. \
    && make

# testするならここでする。

RUN install /home/tmp/build/hello_drogon /usr/local/bin/

# 後片付け。
RUN rm -rf \
        /home/tmp \
        /usr/local/bin/drogon_ctl \
        /usr/local/include/drogon \
        /usr/local/lib/libdrogon.a \
        /usr/local/vcpkg/ports/drogon \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN useradd -m app
USER app
WORKDIR /home/app

# COPY
EXPOSE 8080

CMD ["/usr/local/bin/hello_drogon"]
