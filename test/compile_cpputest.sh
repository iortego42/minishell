#!/bin/sh
cd cpputest
./autogen.sh
./configure
make all
cd ..