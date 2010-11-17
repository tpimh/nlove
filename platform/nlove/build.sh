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

if [ "$1" = "-r" -o ! -d "platform/nlove/build" ]; then
	REBUILD=1
fi

if [ $REBUILD ]; then
	rm src/common/config.h
	cp platform/nlove/CMakeLists.txt src/CMakeLists.txt
	if [ -f "platform/nlove/CMakeLists-${PLATFORM}.patch" ]; then
		patch -p0 src/CMakeLists.txt platform/nlove/CMakeLists-${PLATFORM}.patch
	fi
fi
mkdir platform/nlove/build 2> /dev/null
cd platform/nlove/build
if [ $REBUILD ]; then
	if [ -f "../XCompile-${TOOLCHAIN}.txt" ]; then
		cmake ../../../src/ -DCMAKE_TOOLCHAIN_FILE=../XCompile-${TOOLCHAIN}.txt
	else
		cmake ../../../src/
	fi
fi
make
if [ -f "liblove.so" ]; then
	cp liblove.so ../../../
fi
if [ -f "liblove.a" ]; then
	cp liblove.a ../../../
fi
cp nlove ../../../
