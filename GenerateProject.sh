#!/bin/sh
if [ ! -d "build" ]; then
  mkdir build
fi
cd build
cmake -H../ -B.		#cmake -Hpath/to/source -Bpath/to/build

sys=`uname  -a`
sysname=$(echo $sys | sed 's/ //g' | tr '[A-Z]' '[a-z]')

if [ ! -z $(echo $sysname | grep "darwin") ]
then
    echo "Mac"
	make -j4
elif [ ! -z $(echo $sysname | grep "linux") ]
then
    echo "Linux"
	make -j4
elif [ ! -z $(echo $sysname | grep "ubuntu") ]
then	
    echo "Ubuntu"
	make -j4
elif [ ! -z $(echo $sysname | grep "windows") ]
then
	echo "------------------------------------------------------------------------"
	echo "--------------------Successful to generate vs project-------------------"
    echo "Please use Visual Studio to open build/TmingEngine.sln "
	echo "Then set the Editor as a startup project                                "
	echo "build and run   ,       engoy it !!!                                    "
	echo "------------------------------------------------------------------------"
else
    echo $sysname
fi


