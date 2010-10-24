#!/bin/sh

cp platform/nlove/CMakeLists.txt src/CMakeLists.txt
mkdir platform/nlove/build
cd platform/nlove/build
cmake ../../../src/
make
cp nlove ../../../
