#!/bin/bash

# Requires entr

find . -name '*.cpp' | entr sh -c 'make -j8'
