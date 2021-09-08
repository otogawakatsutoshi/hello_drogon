FROM gitpod/workspace-base:latest

RUN apt update && apt upgrade -y

# [drogon install](https://github.com/drogonframework/drogon/wiki/ENG-02-Installation)
RUN apt install -y \
    libjsoncpp-dev \
    uuid-dev \
    openssl \
    libssl-dev \
    zlib1g-dev

