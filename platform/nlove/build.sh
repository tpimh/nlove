#!/bin/sh

if [ -z $PLATFORM ]; then
	PLATFORM=$1
fi

if [ -z $PLATFORM ]; then
	PLATFORM="Generic"
fi

if [ -z $TOOLCHAIN ]; then
	TOOLCHAIN=$2
fi

if [ -z $TOOLCHAIN ]; then
	TOOLCHAIN=$PLATFORM
fi

cp platform/nlove/CMakeLists-${PLATFORM}.txt src/CMakeLists.txt
mkdir platform/nlove/build 2> /dev/null
cd platform/nlove/build
if [ "$TOOLCHAIN" = "Generic" ]; then
	cmake ../../../src/
else
	cmake ../../../src/ -DCMAKE_TOOLCHAIN_FILE=../XCompile-${TOOLCHAIN}.txt
fi
make
cp nlove ../../../
