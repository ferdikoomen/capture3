#!/bin/sh


# Run NPM
yarn install
npm run build


# Clean directory
rm -rf build/release
mkdir -p build/release
cd build/release


# Run CMAKE, with GCC 6.x compiler
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_C_COMPILER=/usr/local/gcc-6/bin/gcc -D CMAKE_CXX_COMPILER=/usr/local/gcc-6/bin/g++ ../../


# Build the application
make -j 8
make install
cd ../../


# Code APP
codesign --force --deep --verbose --sign "Developer ID Application: Ferdi Koomen" build/release/bin/Capture3.app
codesign --verbose --verify build/release/bin/Capture3.app


# Build a DMG file
dmgcanvas installer/installer.dmgCanvas build/release/bin/Capture3.dmg


# Code sign DMG file
codesign --verbose --sign "Developer ID Application: Ferdi Koomen" build/release/bin/Capture3.dmg
codesign --verbose --verify build/release/bin/Capture3.dmg