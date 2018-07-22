To configure and build...

mkdir build
cd build
cmake -DCONNEXTDDS_ARCH=x64Linux3gcc5.4.0 -DCMAKE_MODULE_PATH=$NDDSHOME/resource/cmake -DRTICODEGEN_DIR=$NDDSHOME/bin ..
cmake --build .