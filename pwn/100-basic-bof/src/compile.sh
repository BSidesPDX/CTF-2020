#!/bin/sh

gcc main.c -o basic-bof -Wl,-z,relro,-z,now -fno-stack-protector -g -O0 #-Wl,-Ttext=0xdeadbeef -v
#strip basic-bof

cp ./basic-bof ../distFiles
cp ./Dockerfile ../distFiles # so they can see libc version
