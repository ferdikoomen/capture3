# Install Xcode command line tools

sudo xcode-select --install


# Install platform headers

cd /Library/Developer/CommandLineTools/Packages/
open .
macOS_SDK_headers_for_macOS_10.14.pkg

# Install Cmake

https://cmake.org

sudo "/Applications/CMake.app/Contents/bin/cmake-gui" --install


# Install Homebrew

https://brew.sh

Then install the following dependencies:

```
brew install gcc
brew install jpeg
brew install webp
brew install libtiff
brew install libraw
brew install glfw
brew install freeimage
brew install freetype
brew install boost
brew install ffmpeg
brew install openssl
brew install imagemagick
brew install gphoto2
brew install opencv
brew install qt
```