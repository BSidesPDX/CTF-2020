#!/bin/sh

set -e

make

cp ./speakers ../solve
mv ./speakers ../distFiles
cp ./Dockerfile ../distFiles

