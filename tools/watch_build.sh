#!/bin/bash

# Requires entr

find ./src ./lib-src -name '*.[chq]*'  | entr sh -c 'cd build; make -j8'
