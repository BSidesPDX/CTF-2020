#!/bin/bash

mkdir -p /var/lib/tor/hidden_http/
cp /app/onion_hostname/tor100-hostname /var/lib/tor/hidden_http/hostname
cp /app/onion_private_key/tor100-private_key /var/lib/tor/hidden_http/private_key
chown -R debian-tor:debian-tor /var/lib/tor/hidden_http/
chmod -R 0700 /var/lib/tor/hidden_http/
service apache2 start
service tor restart

while true; do sleep 30; done;
