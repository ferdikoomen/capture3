#!/bin/sh


# Run NPM
npm install
npm run build


# Clean directory
mkdir -p build/debug
cd build/debug


# Run CMAKE, with default (Clang) compiler
cmake -D CMAKE_BUILD_TYPE=Debug ../../


# Build the application
make -j 8


# Start the application
./bin/Capture3.app/Contents/MacOS/Capture3