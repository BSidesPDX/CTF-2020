#!/bin/sh

gcc main.c -o basic-heap -Wl,-z,relro,-z,now -fno-stack-protector -g -O0 #-Wl,-Ttext=0xdeadbeef -v
#strip basic-heap

cp ./basic-heap ../distFiles
cp ./Dockerfile ../distFiles # so they can see libc version
