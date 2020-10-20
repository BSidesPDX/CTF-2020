#!/bin/sh

gcc main.c -o basic-bof -Wl,-z,relro,-z,now -fno-stack-protector -g -O0 -no-pie -static # -Wl,-Ttext=0xdeadbeef -static
#strip basic-bof

cp ./basic-bof ../distFiles
