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

cp platform/nlove/CMakeLists.txt src/CMakeLists.txt
if [ -f "platform/nlove/CMakeLists-${PLATFORM}.patch" ]; then
	patch -p0 src/CMakeLists.txt platform/nlove/CMakeLists-${PLATFORM}.patch
fi
mkdir platform/nlove/build 2> /dev/null
cd platform/nlove/build
if [ -f "../XCompile-${TOOLCHAIN}.txt" ]; then
	cmake ../../../src/ -DCMAKE_TOOLCHAIN_FILE=../XCompile-${TOOLCHAIN}.txt
else
	cmake ../../../src/
fi
make
cp nlove ../../../
