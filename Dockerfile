FROM ubuntu:16.04

MAINTAINER Chuck Fairy <charlieabeling@gmail.com>

RUN echo "building gabrielo image"

#CMD echo "Hello Container"

RUN apt-get -qq update

RUN apt-get -y install g++ cmake git subversion libboost-all-dev


# Tools

RUN apt-get -y install libtag1-dev libcurl3 libgtkmm-2.4-dev libgtkmm-2.4-1v5


# ALSA
RUN apt-get -y install alsa-base alsa-oss alsa-utils alsa-tools alsa-tools-gui libalsaplayer0 libalsaplayer-dev libasound2 libasound2-dev libasound2-plugin*


# SND
RUN apt-get -y install libglibmm-2.4-* libsndfile1 libsndfile1-dbg libsndfile1-dev


# Liblo
RUN apt-get -y install liblo7 liblo-dev liblo-tools


# Audio plugins
RUN apt-get -y install libvamp-*sdk2v5 vamp-plugin* librubberband* libfftw3-* libjack-dev liblrdf0* libsamplerate0*  libserd-0-0 libserd-dev libsord-0-0 libsord-dev libsratom-0-0 libsratom-dev
RUN apt-get -y install liblv2dynparam* lv2core lv2-dev liblilv-dev liblilv-0-0


# Git load
RUN git clone https://github.com/chuckfairy/gabrielo.git /gabrielo
RUN cd /gabrielo; git submodule update --init; cmake .; make
