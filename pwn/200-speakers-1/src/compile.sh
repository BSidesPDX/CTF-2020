#!/bin/sh

gcc main.c -o speakers-1 -Wl,-z,relro,-z,now -fno-stack-protector -g -O0 #-Wl,-Ttext=0xdeadbeef -v
strip speakers-1

cp ./speakers-1 ../distFiles
cp ./Dockerfile ../distFiles # so they can see libc version
