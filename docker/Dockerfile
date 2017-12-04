FROM rootproject/root-ubuntu16

RUN apt-get update && apt-get install -y liblz4-dev scons && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/tylern4/hipo2root.git

RUN cd hipo2root && scons && make

WORKDIR /tmp/

ENTRYPOINT ["/hipo2root/hipo2root"]
