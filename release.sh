#!/bin/sh


# Run NPM
npm install
npm run build


# Clean directory
rm -r build/release
mkdir -p build/release
cd build/release


# Run CMAKE, with GCC 6.x compiler
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_C_COMPILER=/usr/local/gcc-6/bin/gcc -D CMAKE_CXX_COMPILER=/usr/local/gcc-6/bin/g++ ../../


# Build the application
make -j 8
make install


# Build a DMG file for distribution
dmgcanvas ../../installer/installer.dmgCanvas bin/Capture3.dmg