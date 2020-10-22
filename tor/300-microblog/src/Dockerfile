FROM ubuntu:20.04

RUN apt-get update \
    && apt-get install -y --no-install-recommends nginx tor python3 python3-venv curl

RUN echo "HiddenServiceDir /var/lib/tor/hidden_http/\nHiddenServiceVersion 2\nHiddenServicePort 80 127.0.0.1:8080" >> /etc/tor/torrc

WORKDIR /app

COPY requirements.txt requirements.txt
RUN python3 -m venv venv
RUN venv/bin/pip install -r requirements.txt
RUN venv/bin/pip install gunicorn

COPY app app
COPY migrations migrations
COPY deployment deployment
COPY microblog.py config.py entrypoint.sh app.db.orig wsgi.py ./
RUN chmod a+x entrypoint.sh

ENV FLASK_APP microblog.py

EXPOSE 80
VOLUME ["/app/onion_hostname"]
VOLUME ["/app/onion_private_key"]

ENTRYPOINT ["/bin/bash", "entrypoint.sh"]
