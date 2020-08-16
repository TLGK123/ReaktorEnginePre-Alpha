if [ ! -d "build" ]; then
  mkdir build
fi
cd build
cmake -H../ -B.
#cmake -Hpath/to/source -Bpath/to/build