#!/bin/sh

rm -f speakers
make
strip ./speakers

docker build . -t speakers:speakers

