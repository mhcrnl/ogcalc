cmake_minimum_required(VERSION 2.8)
PROJECT(ogcalc)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Svg REQUIRED)

SET(ogcalc_SOURCES main.cpp ogcalc.cpp  SpinBoxEntry.cpp)
SET(ogcalc_HEADERS ogcalc.h SpinBoxEntry.h)

add_executable(ogcalc ${ogcalc_SOURCES} ${ogcalc_HEADERS_MOC})
qt5_use_modules(ogcalc Core Gui Widgets Svg)
