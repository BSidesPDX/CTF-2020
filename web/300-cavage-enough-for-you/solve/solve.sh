#!/bin/bash
cwd=$(pwd)

mkdir client
cp src/* client/
cd client
echo "Generating pkcs8 key for http sig"
openssl genrsa -out key.pem 2048
openssl rsa -pubout -in key.pem -out key_public.pem
openssl pkcs8 -topk8 -inform PEM -outform PEM -in key.pem -out key.pkcs8 -nocrypt
sleep 1
cat key_public.pem |sed ':a;N;$!ba;s/\n/\\n/g' | sed 's/ *$//' >key_public_nosp.pem
truncate -s -1 key_public_nosp.pem
python3 pem_inject.py

rm key.pem key_public.pem

mv tls2.go tls.go
mv payload2.json payload.json 

go build .


curl -k -X POST http://localhost:1337/addkey -d @payload.json #replace localhost with ip

./client -host=localhost:1337/logs >logs.txt

tac logs.txt > logsr.txt
mv logsr.txt logs.txt

python3 urlparse.py

cd ..
rm -rf client/
