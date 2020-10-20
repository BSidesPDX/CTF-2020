#!/bin/bash

header=$(curl localhost:8081/security | base64)
headernospace="$(echo -e "${header}" | tr -d '[:space:]')"

curl localhost:8081/security -H "Rules: $headernospace" 

