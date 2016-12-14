#!/bin/bash

#http://stackoverflow.com/questions/24095968/docker-for-gui-based-environments#27162721

docker run -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=unix$DISPLAY TheImage
