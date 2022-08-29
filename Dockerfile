FROM katsutoshiotogawa/drogon:v1
RUN apt update && apt upgrade -y

# 作業用ディレクトリ
WORKDIR /home/tmp
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
        /usr/local/vcpkg/ports/argparse \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN useradd -m app
USER app
WORKDIR /home/app

# COPY
EXPOSE 8080

CMD ["/usr/local/bin/hello_drogon"]
