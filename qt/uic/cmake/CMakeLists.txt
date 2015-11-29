cmake_minimum_required(VERSION 2.8)
PROJECT(ogcalc)

set(OGCALC_VERSION_MAJOR 1)
set(OGCALC_VERSION_MINOR 5)
set(OGCALC_VERSION_PATCH 0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Svg REQUIRED)

SET(ogcalc_SOURCES main.cpp ogcalc.cpp  SpinBoxEntry.cpp)
SET(ogcalc_HEADERS ogcalc.h SpinBoxEntry.h)
SET(ogcalc_UI ogcalc.ui)

qt5_wrap_ui(ogcalc_UI_HEADERS ${ogcalc_UI})

if(WIN32)
  set(ogcalc_RESOURCES ogcalc.rc)
endif(WIN32)

add_executable(ogcalc ${ogcalc_SOURCES} ${ogcalc_HEADERS_MOC} ${ogcalc_UI_HEADERS} ${ogcalc_UI} ${ogcalc_RESOURCES})
qt5_use_modules(ogcalc Core Gui Widgets Svg)

set(ARCHIVE_NAME
  "ogcalc-qt-uic-cmake-${OGCALC_VERSION_MAJOR}.${OGCALC_VERSION_MINOR}.${OGCALC_VERSION_PATCH}")
# Normally, "git archive" would work well, but it doesn't follow
# symlinks.  Due to using symlinks heavily, we need to follow them to
# avoid creating broken archives.
add_custom_target(dist
    COMMAND tar chfv - "--transform='s;^;${ARCHIVE_NAME}/;'" \$\$\(git ls-tree -r --name-only HEAD . | grep -v '^.gitignore'\) | gzip -9 > ${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.gz
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
