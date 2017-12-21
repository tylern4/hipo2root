FROM rootproject/root-ubuntu16

RUN apt-get update && apt-get install -y liblz4-dev scons && rm -rf /var/lib/apt/lists/*

WORKDIR /tmp/
RUN git clone https://github.com/tylern4/hipo2root.git \
    && cd hipo2root && scons && make && mv hipo2root /usr/bin/ \
    && rm -rf /tmp/*

ENTRYPOINT ["/usr/bin/hipo2root"]
