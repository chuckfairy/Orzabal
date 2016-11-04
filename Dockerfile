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


# Qt 5
RUN apt-get -y install \
    libqt5concurrent5 \
    libqt5core5a \
    libqt5dbus5 \
    libqt5declarative5 \
    libqt5gui5 \
    libqt5multimedia5 \
    libqt5network5 \
    libqt5opengl5 \
    libqt5opengl5-dev \
    libqt5qml-graphicaleffects \
    libqt5qml5 \
    libqt5quick5 \
    libqt5quicktest5 \
    libqt5script5 \
    libqt5scripttools5 \
    libqt5svg5 \
    libqt5widgets5 \
    libqt5xml5 \
    pyqt5-dev \
    python3-pyqt5 \
    python3-pyqt5-dbg \
    qt5-default \
    qt5-qmake \
    qt5-image-formats-plugins \
    qtdeclarative5-controls-plugin \
    qtdeclarative5-dbg \
    qtdeclarative5-dev \
    qtdeclarative5-dev-tools \
    qtdeclarative5-dialogs-plugin \
    qtdeclarative5-models-plugin \
    qtdeclarative5-qtquick2-plugin \
    qtdeclarative5-window-plugin \
    qttools5-dev-tools \
    qttools5-dev

# Git load
RUN git clone https://github.com/chuckfairy/jack-tests.git /gabrielo
RUN cd /gabrielo; git submodule update --init; cmake .; make


# VNC testing

# Set user for VNC server (USER is only for build)
ENV USER root

## LXDE
RUN apt-get install -y lxde-core

## TightVNC
RUN apt-get install -y tightvncserver

RUN echo "test2345" > pass.txt; cat pass.txt pass.txt | vncpasswd

EXPOSE 8080

COPY bin/docker_vnc.sh /opt/
CMD ["/opt/docker_vnc.sh"]
