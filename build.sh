#!/bin/bash
clear
echo Setting up Ducktape for compiling...
echo Choose your generator:
echo 1\) Borland Makefiles
echo 2\) MSYS Makefiles
echo 3\) MinGW Makefiles \(Default for Windows\)
echo 4\) NMake Makefiles
echo 5\) NMake Makefiles JOM
echo 6\) Unix Makefiles \(Default for Linux\)
echo 7\) Watcom WMake
echo -n Enter your option \(1,2,3,4,5,6,7\):
set generator=None
read idx
if [ ${idx} = 1 ]
then
	generator="Borland Makefiles"
fi
if [ ${idx} = 2 ]
then
	generator="MSYS Makefiles"
fi
if [ ${idx} = 3 ]
then
	generator="MinGW Makefiles"
fi
if [ ${idx} = 4 ]
then
	generator="NMake Makefiles"
fi
if [ ${idx} = 5 ]
then
	generator="NMake Makefiles JOM"
fi
if [ ${idx} = 6 ]
then
	generator="Unix Makefiles"
fi
if [ ${idx} = 7 ]
then
	generator="Watcom WMake"
fi
clear

echo Specify your compiler:
echo \(You may enter a path to your compiler or just the compiler\'s command name if the compiler path is already in your PATH environment variable\)
read compiler
clear

echo Choose the build type:
echo 1\) Debug
echo 2\) Release
echo -n Enter your option (1,2):
set build=None
read build
if [ ${idx} = 1 ]
then
	generator="DEBUG"
fi
if [ ${idx} = 2 ]
then
	generator="RELEASE"
fi

mkdir build
clear
cd build
cmake -G "${generator}" -DCMAKE_CXX_COMPILER=${compiler} -DCMAKE_BUILD_TYPE=${generator} ..
make