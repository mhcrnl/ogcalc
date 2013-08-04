cmake_minimum_required(VERSION 2.8)
PROJECT(ogcalc)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5UiTools REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Designer)
FIND_PACKAGE(Qt5Svg REQUIRED)

SET(SpinBoxEntry_SOURCES SpinBoxEntry.cpp)
SET(SpinBoxEntry_HEADERS SpinBoxEntry.h)

SET(SpinBoxEntryPlugin_SOURCES SpinBoxEntryPlugin.cpp)
SET(SpinBoxEntryPlugin_HEADERS SpinBoxEntryPlugin.h)

SET(ogcalc_SOURCES main.cpp ogcalc.cpp SpinBoxEntryPlugin.cpp)
SET(ogcalc_HEADERS ogcalc.h SpinBoxEntryPlugin.h)

if(WIN32)
  set(ogcalc_RESOURCES ogcalc.rc)
endif(WIN32)

add_library(SpinBoxEntry SHARED ${SpinBoxEntry_SOURCES} ${SpinBoxEntry_HEADERS_MOC})
qt5_use_modules(SpinBoxEntry Core Gui UiTools Widgets Designer Svg)

add_library(SpinBoxEntryPlugin MODULE ${SpinBoxEntryPlugin_SOURCES} ${SpinBoxEntryPlugin_HEADERS_MOC})
qt5_use_modules(SpinBoxEntryPlugin Core Gui UiTools Widgets Designer Svg)
target_link_libraries(SpinBoxEntryPlugin SpinBoxEntry)

add_executable(ogcalc ${ogcalc_SOURCES} ${ogcalc_HEADERS_MOC} ${ogcalc_RESOURCES})
qt5_use_modules(ogcalc Core Gui UiTools Widgets Designer Svg)
target_link_libraries(ogcalc SpinBoxEntry)
