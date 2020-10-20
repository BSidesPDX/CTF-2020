FROM ubuntu:19.04

RUN sed -i -re 's/([a-z]{2}\.)?archive.ubuntu.com|security.ubuntu.com/old-releases.ubuntu.com/g' /etc/apt/sources.list && apt-get update -y && apt-get install -y \
    lib32z1 xinetd \
 && rm -rf /var/lib/apt/lists/*

RUN useradd -m ctf

WORKDIR /home/ctf

RUN cp -Rn /lib* /home/ctf
RUN ls /home/ctf
RUN cp -Rn /usr /home/ctf

RUN mkdir /home/ctf/dev && \
    mknod /home/ctf/dev/null c 1 3 && \
    mknod /home/ctf/dev/zero c 1 5 && \
    mknod /home/ctf/dev/random c 1 8 && \
    mknod /home/ctf/dev/urandom c 1 9 && \
    chmod 666 /home/ctf/dev/*

RUN mkdir /home/ctf/bin && \
    cp /bin/sh /home/ctf/bin && \
    cp /bin/ls /home/ctf/bin && \
    cp /bin/cat /home/ctf/bin

COPY ./ctf.xinetd /etc/xinetd.d/ctf
COPY ./start.sh /start.sh
RUN echo "Blocked by ctf_xinetd" > /etc/banner_fail

RUN chmod +x /start.sh

COPY ./flag.txt /home/ctf/
COPY ./speakers /home/ctf/

RUN chown -R root:ctf /home/ctf && \
    chmod -R 750 /home/ctf && \
    chmod 740 /home/ctf/flag.txt

CMD ["/start.sh"]

EXPOSE 9999
