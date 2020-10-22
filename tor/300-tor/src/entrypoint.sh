#!/bin/bash
# this script is used to boot a Docker container
source venv/bin/activate
while true; do
    flask db upgrade
    if [[ "$?" == "0" ]]; then
        break
    fi
    echo Deploy command failed, retrying in 5 secs...
    sleep 5
done

cp app.db.orig app.db

#exec gunicorn -b :5000 --access-logfile - --error-logfile - microblog:app

mkdir static

cp deployment/nginx.conf /etc/nginx/
cp deployment/microblog /etc/nginx/sites-available/
ln -s /etc/nginx/sites-available/microblog /etc/nginx/sites-enabled

venv/bin/gunicorn --workers 3 --bind unix:microblog.sock -m 007 wsgi:app &

service nginx start

mkdir -p /var/lib/tor/hidden_http/
cp /app/onion_hostname/tor300-hostname /var/lib/tor/hidden_http/hostname
cp /app/onion_private_key/tor300-private_key /var/lib/tor/hidden_http/private_key
chown -R debian-tor:debian-tor /var/lib/tor/hidden_http/
chmod -R 0700 /var/lib/tor/hidden_http/

service tor restart

while true; do sleep 30; done;
