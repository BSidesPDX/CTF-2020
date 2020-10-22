from debian:stretch

RUN apt-get update \
    && apt-get install -y --no-install-recommends curl tor apache2 nano \
    && a2enmod headers \
    && sed -i 's/#Require ip 192.0.2.0\/24/Header set X-Flag: BSidesPDX{4p4ch3_s3rv3r_st4tus_1s_l34ky}/' /etc/apache2/mods-enabled/status.conf \
    && update-rc.d apache2 defaults

RUN echo "HiddenServiceDir /var/lib/tor/hidden_http/\nHiddenServiceVersion 2\nHiddenServicePort 80 127.0.0.1:80" >> /etc/tor/torrc

WORKDIR /app
COPY entrypoint.sh /app

EXPOSE 80
VOLUME ["/app/onion_hostname"]
VOLUME ["/app/onion_private_key"]
ENTRYPOINT ["/bin/bash", "entrypoint.sh"]

CMD ["/bin/bash"]