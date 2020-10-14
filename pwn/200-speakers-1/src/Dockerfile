FROM ubuntu:20.04

RUN apt-get update -y && apt-get install -y \
    lib32z1 xinetd \
 && rm -rf /var/lib/apt/lists/*

RUN useradd -m ctf

WORKDIR /

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
