#!/bin/sh
cmake -S . -B ../build  # -S is followed by path to source. "." means everything is to be sourced. -B is followed by path to build.
cmake --build ../build
cd ../build && ctest