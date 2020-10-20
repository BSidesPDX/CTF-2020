from debian:stretch

RUN apt-get update \
    && apt-get install -y --no-install-recommends curl tor apache2 nano \
    && a2enmod headers 

RUN echo "HiddenServiceDir /var/lib/tor/hidden_http/\nHiddenServiceVersion 2\nHiddenServicePort 80 127.0.0.1:80" >> /etc/tor/torrc

WORKDIR /app
COPY entrypoint.sh /app
COPY status.conf /etc/apache2/mods-available
RUN update-rc.d apache2 defaults
EXPOSE 80
VOLUME ["/app/onion_hostname"]
VOLUME ["/app/onion_private_key"]
ENTRYPOINT ["/bin/bash", "entrypoint.sh"]

CMD ["/bin/bash"]
