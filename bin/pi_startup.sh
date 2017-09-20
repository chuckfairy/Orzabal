#!/bin/bash

_dir=$(realpath $(dirname $0));

sudo mount -o remount,size=128M /dev/shm;

nohup /usr/bin/jackd -dalsa -dhw:0 -r48000 -p1024 -n2 -Xseq;

nohup $_dir/../src/qt/orzabal.qt
