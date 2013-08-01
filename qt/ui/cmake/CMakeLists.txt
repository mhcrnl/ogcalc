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

SET(entry_SOURCES SpinBoxEntry.cpp)
SET(entry_HEADERS SpinBoxEntry.h)

SET(plugin_SOURCES SpinBoxEntryPlugin.cpp)
SET(plugin_HEADERS SpinBoxEntryPlugin.h)

SET(ogcalc_SOURCES main.cpp ogcalc.cpp SpinBoxEntryPlugin.cpp)
SET(ogcalc_HEADERS ogcalc.h SpinBoxEntryPlugin.h)

add_library(entry SHARED ${entry_SOURCES} ${entry_HEADERS_MOC})
qt5_use_modules(entry Core Gui UiTools Widgets Designer Svg)

add_library(plugin MODULE ${plugin_SOURCES} ${plugin_HEADERS_MOC})
qt5_use_modules(plugin Core Gui UiTools Widgets Designer Svg)
target_link_libraries(plugin entry)

add_executable(ogcalc ${ogcalc_SOURCES} ${ogcalc_HEADERS_MOC})
qt5_use_modules(ogcalc Core Gui UiTools Widgets Designer Svg)
target_link_libraries(ogcalc entry)