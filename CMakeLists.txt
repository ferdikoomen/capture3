#
# MINIMUN VERSION OF CMAKE
#
cmake_minimum_required(VERSION 3.13)


#
# PROJECT INFO
#
project(Capture3)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
set(DESCRIPTION "Capture3 - Copyright (c) 2016-2020, Ferdi Koomen")
set(COMPANY "Ferdi Koomen")
set(COPYRIGHT "Copyright (c) 2016-2020, Ferdi Koomen. All rights reserved.")
set(IDENTIFIER "com.capture3.application")


#
# USE GCC 8.x, C++11 and OpenMP
#
set(CMAKE_C_COMPILER "/usr/local/bin/gcc-8")
set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-8")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pragmas")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=10.15") # Catalina
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_EXTENSIONS)


#
# QT 5 DEPENDENCIES
#
set(QT "/usr/local/opt/qt5")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${QT}/lib/cmake/")
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Sql REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Gui_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Network_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5OpenGL_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Sql_EXECUTABLE_COMPILE_FLAGS}")


#
# OUTPUT DIRECTORIES
#
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "lib/static/")
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/bin")


#
# PROJECT FILES
#
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "src/*.h")
file(GLOB_RECURSE RESOURCE_FILES "resources/*.*")


#
# LIBRARIES
#
set(LIBRARIES
        jpeg
        png
        raw
        gphoto2
        gphoto2_port
        glfw

        # FFMPEG
        avcodec
        avdevice
        avfilter
        avformat
        avutil
        swresample
        swscale

        # OPEN CV
        opencv_core
        opencv_imgcodecs
        opencv_imgproc
        opencv_photo
        opencv_video
        opencv_videoio
        opencv_highgui
        opencv_calib3d
        opencv_features2d
        opencv_objdetect
        opencv_flann

        # BOOST
        boost_chrono
        boost_date_time
        boost_filesystem
        boost_system
        boost_timer
        )


#
# FRAMEWORKS
#
set(FRAMEWORKS
        "-framework Accelerate"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework OpenGL"
        "-framework OpenCL"
        "-framework GLUT"
        "-framework AGL"
        "-framework CoreFoundation"
        "-framework CoreServices"
        "-framework CoreMedia"
        "-framework CoreVideo"
        "-framework CoreAudio"
        )


#
# LINK DIRECTORIES
#
set(LINK_DIR
        "/usr/local/opt/libjpeg/lib/"
        "/usr/local/opt/libpng/lib/"
        "/usr/local/opt/libraw/lib/"
        "/usr/local/opt/libgphoto2/lib/"
        "/usr/local/opt/glfw/lib/"
        "/usr/local/opt/ffmpeg/lib/"
        "/usr/local/opt/boost/lib/"
        "/usr/local/opt/opencv/lib/"
        "/usr/local/lib/"
        "/usr/lib/"
        "${QT}/lib/"
        "${QT}/plugins/"
        )
link_directories(${LINK_DIR})


#
# INCLUDE DIRECTORIES
#
set(INCLUDE_DIR
        "/usr/local/opt/libjpeg/include/"
        "/usr/local/opt/libpng/include/"
        "/usr/local/opt/libraw/include/"
        "/usr/local/opt/libgphoto2/include/"
        "/usr/local/opt/glfw/include/"
        "/usr/local/opt/ffmpeg/include/"
        "/usr/local/opt/boost/include/"
        "/usr/local/opt/opencv/include/opencv4"
        "/usr/local/include/"
        "/usr/include/"
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Gui_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5Network_INCLUDE_DIRS}
        ${Qt5OpenGL_INCLUDE_DIRS}
        ${Qt5Sql_INCLUDE_DIRS}
        )
include_directories(${INCLUDE_DIR})


#
# DEFINITIONS
#
set(DEFINITIONS
        ${Qt5Core_DEFINITIONS}
        ${Qt5Gui_DEFINITIONS}
        ${Qt5Widgets_DEFINITIONS}
        ${Qt5Network_DEFINITIONS}
        ${Qt5OpenGL_DEFINITIONS}
        ${Qt5Sql_DEFINITIONS}
        )
add_definitions(${DEFINITIONS})


#
# EXECUTABLE
#
add_executable(${PROJECT_NAME} MACOSX_BUNDLE
        ${SOURCE_FILES}
        ${HEADER_FILES}
        ${RESOURCE_FILES}
        ${MACOSX_APP_ICON}
        )


#
# LIBRARIES
#
target_link_libraries(${PROJECT_NAME}
        ${LIBRARIES}
        ${FRAMEWORKS}
        ${Qt5Core_LIBRARIES}
        ${Qt5Gui_LIBRARIES}
        ${Qt5Widgets_LIBRARIES}
        ${Qt5Network_LIBRARIES}
        ${Qt5OpenGL_LIBRARIES}
        ${Qt5Sql_LIBRARIES}
        )


#
# MAC OSX BUNDLE PROPERTIES
#
if (APPLE)
    set(MACOSX_APP "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app")
    set(MACOSX_APP_ICON ${CMAKE_CURRENT_SOURCE_DIR}/resources/icon/icon.icns)
    set_source_files_properties(${MACOSX_APP_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    set_target_properties(${PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/resources/plist/Info.plist.in
            MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
            MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
            MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION}
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
            MACOSX_BUNDLE_INFO_STRING ${DESCRIPTION}
            MACOSX_BUNDLE_GUI_IDENTIFIER ${IDENTIFIER}
            MACOSX_BUNDLE_COPYRIGHT ${COPYRIGHT}
            MACOSX_BUNDLE_ICON_FILE icon.icns
            )
endif ()


#
# INSTALL BUNDLE
#
install(
        TARGETS
        ${PROJECT_NAME}
        BUNDLE DESTINATION .
        RUNTIME DESTINATION bin
)


#
# COPY QT PLUGINS
#
install(FILES "${QT}/plugins/imageformats/libqicns.dylib" DESTINATION "${MACOSX_APP}/Contents/Plugins/imageformats/")
install(FILES "${QT}/plugins/imageformats/libqico.dylib" DESTINATION "${MACOSX_APP}/Contents/Plugins/imageformats/")
install(FILES "${QT}/plugins/imageformats/libqjpeg.dylib" DESTINATION "${MACOSX_APP}/Contents/Plugins/imageformats/")
install(FILES "${QT}/plugins/imageformats/libqsvg.dylib" DESTINATION "${MACOSX_APP}/Contents/Plugins/imageformats/")
install(FILES "${QT}/plugins/imageformats/libqtiff.dylib" DESTINATION "${MACOSX_APP}/Contents/Plugins/imageformats/")
install(FILES "${QT}/plugins/platforms/libqcocoa.dylib" DESTINATION "${MACOSX_APP}/Contents/Plugins/platforms/")
install(FILES "${QT}/plugins/platforms/libqminimal.dylib" DESTINATION "${MACOSX_APP}/Contents/Plugins/platforms/")
install(FILES "${QT}/plugins/sqldrivers/libqsqlite.dylib" DESTINATION "${MACOSX_APP}/Contents/Plugins/sqldrivers/")


#
# COPY TEST FILES
#
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/resources/test/DSC_0001.NEF" DESTINATION "${MACOSX_APP}/Contents/Resources/")


#
# 1. WRITE QT CONFIG
# 2. FIND PLUGINS
# 3. BUNDLE APP
# 4. FIX APP
#
install(CODE "file(WRITE \"${MACOSX_APP}/Contents/Resources/qt.conf\" \"[Paths]\n\rPlugins = Plugins\n\r\")")
install(CODE "file(GLOB_RECURSE PLUGINS \"${MACOSX_APP}/Contents/Plugins/*\")")
install(CODE "include(BundleUtilities)")
install(CODE "fixup_bundle(\"${MACOSX_APP}/Contents/MacOS/${PROJECT_NAME}\" \"\${PLUGINS}\" \"${LINK_DIR}\")")

