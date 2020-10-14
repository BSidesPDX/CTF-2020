FROM ubuntu:18.04

RUN apt-get update -y && apt-get install -y \
    lib32z1 xinetd \
 && rm -rf /var/lib/apt/lists/*

RUN useradd -m ctf

WORKDIR /home/ctf

RUN cp -R /lib* /home/ctf && \
    cp -R /usr/lib* /home/ctf

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
COPY ./speakers-1 /speakers-1
COPY ./start.sh /start.sh
RUN echo "Blocked by ctf_xinetd" > /etc/banner_fail

COPY ./flag.txt /flag.txt
RUN chown root:ctf /flag.txt /speakers-1 /start.sh && \
    chmod 740 /flag.txt /speakers-1 /start.sh

RUN chmod +x /speakers-1 /start.sh

CMD ["/start.sh"]

EXPOSE 9999
