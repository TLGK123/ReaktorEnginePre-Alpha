if [ ! -d "build" ]; then
  mkdir build
fi
cd build
cmake -H../ -B.
make -j4
#cmake -Hpath/to/source -Bpath/to/build