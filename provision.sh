
# cant use interactive settings in vagrant provision.
export DEBIAN_FRONTEND=noninteractive

# 環境変数読み込み
cat /vagrant/.env | sed 's/# .*$//' | xargs -I {} echo export {} >> /home/vagrant/.bashrc
cat /vagrant/.env | sed 's/# .*$//' | xargs -I {} echo export {} >> ~/.bashrc
source ~/.bashrc

apt update && apt upgrade -y 

apt install -y \
        gcc \
        g++ \
        cmake \
        git \
        libjsoncpp-dev \
        uuid-dev \
        openssl \
        libssl-dev \
        zlib1g-dev \

git clone https://github.com/an-tao/drogon \
        && cd drogon \
        && git submodule update --init \
        && mkdir build \
        && cd build \
        && cmake .. \
        && make && make install \
        && cd ../../ && rm -rf drogon \


apt-get clean \
    && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# set bash function
su - vagrant -c 'cat < /vagrant/function.sh >> ~/.bashrc'
