#!/bin/bash
gcc -fpermissive app.cpp
gcc -c star.cpp
gcc -c Stars.cpp
make
./Stars
