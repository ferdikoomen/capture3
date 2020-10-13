# Install Xcode command line tools

sudo xcode-select --install



# Install Cmake

https://cmake.org

sudo "/Applications/CMake.app/Contents/bin/cmake-gui" --install



# Install Yarn

https://yarnpkg.com



# Install Homebrew

https://brew.sh

Then install the following dependencies:

```
brew install cmake
brew install python@3
brew install gcc@6
brew install gcc@8
brew install jpeg
brew install webp
brew install libtiff
brew install libraw
brew install glfw
brew install freeimage
brew install freetype
brew install woff2
brew install boost
brew install ffmpeg
brew install openssl
brew install imagemagick
brew install gphoto2
brew install opencv@3
brew install opencv@4
brew install qt
```



# Install OpenCV

Homebrew has clang compiled libraries for OSX, but we want to use GCC and OpenMP to speedup some calculations.
So, once we have all the dependencies installed we can just build OpenCV like this:

```
cd /Users/ferdi/Workspace/GitHub/opencv/opencv
mkdir build
cd build
cmake  \
-D CMAKE_BUILD_TYPE=Release \
-D BUILD_DOCS=OFF \
-D BUILD_EXAMPLES=OFF \
-D BUILD_PERF_TESTS=OFF \
-D BUILD_TESTS=OFF \
-D WITH_LAPACK=OFF \
-D WITH_AVFOUNDATION=OFF \
-D WITH_FFMPEG=ON \
-D WITH_OPENMP=ON \
-D WITH_OPENGL=ON \
-D WITH_QT=ON \
-D Qt5_DIR=/usr/local/opt/qt5/lib/cmake/Qt5 \
-D QT_QMAKE_EXECUTABLE=/usr/local/opt/qt5/bin/qmake \
-D Qt5Concurrent_DIR=/usr/local/opt/qt5/lib/cmake/Qt5Concurrent \
-D Qt5Core_DIR=/usr/local/opt/qt5/lib/cmake/Qt5Core \
-D Qt5Gui_DIR=/usr/local/opt/qt5/lib/cmake/Qt5Gui \
-D Qt5Test_DIR=/usr/local/opt/qt5/lib/cmake/Qt5Test \
-D Qt5Widgets_DIR=/usr/local/opt/qt5/lib/cmake/Qt5Widgets \
-D Qt5OpenGL_DIR=/usr/local/opt/qt5/lib/cmake/Qt5OpenGL \
-D OPENCV_EXTRA_MODULES_PATH=/Users/ferdi/Workspace/GitHub/opencv/opencv_contrib/modules \
-D CMAKE_INSTALL_PREFIX=/usr/local/opencv \
-D CMAKE_C_COMPILER=/usr/local/bin/gcc-8 \
-D CMAKE_CXX_COMPILER=/usr/local/bin/g++-8 \
..
make
sudo make install
```



# Warning about "Atomic"?

`error: '_Atomic' does not name a type`

Replace `_Atomic ulong` with `volatile u_long` in the following files:

- `/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/sys/ucred.h`
- `/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/ucred.h`


