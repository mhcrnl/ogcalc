cmake_minimum_required(VERSION 3.0)
project(ogcalc VERSION 1.5.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 5.2.0 REQUIRED COMPONENTS Core Gui UiTools Widgets Designer Svg)

get_target_property(QMAKE_EXECUTABLE Qt5::qmake LOCATION)
function(query_qmake VAR RESULT)
  exec_program(${QMAKE_EXECUTABLE} ARGS "-query ${VAR}" RETURN_VALUE return_code OUTPUT_VARIABLE output )
  if(NOT return_code)
    file(TO_CMAKE_PATH "${output}" output)
    set(${RESULT} ${output} PARENT_SCOPE)
  endif(NOT return_code)
endfunction(query_qmake)

query_qmake(QT_INSTALL_PLUGINS QT_PLUGINS_DIR)

set(SpinBoxEntry_SOURCES SpinBoxEntry.cpp)
set(SpinBoxEntry_HEADERS SpinBoxEntry.h)

set(SpinBoxEntryPlugin_SOURCES SpinBoxEntryPlugin.cpp)
set(SpinBoxEntryPlugin_HEADERS SpinBoxEntryPlugin.h)

set(ogcalc_SOURCES main.cpp ogcalc.cpp SpinBoxEntryPlugin.cpp)
set(ogcalc_HEADERS ogcalc.h SpinBoxEntryPlugin.h)

if(WIN32)
  set(ogcalc_RESOURCES ogcalc.rc)
endif(WIN32)

add_library(SpinBoxEntry SHARED ${SpinBoxEntry_SOURCES} ${SpinBoxEntry_HEADERS} ${SpinBoxEntry_HEADERS_MOC})
qt5_use_modules(SpinBoxEntry Core Gui UiTools Widgets Designer Svg)

add_library(SpinBoxEntryPlugin MODULE ${SpinBoxEntryPlugin_SOURCES} ${SpinBoxEntryPlugin_HEADERS_MOC})
qt5_use_modules(SpinBoxEntryPlugin Core Gui UiTools Widgets Designer Svg)
target_link_libraries(SpinBoxEntryPlugin SpinBoxEntry)

add_executable(ogcalc ${ogcalc_SOURCES} ${ogcalc_HEADERS_MOC} ${ogcalc_RESOURCES})
qt5_use_modules(ogcalc Core Gui UiTools Widgets Designer Svg)
target_link_libraries(ogcalc SpinBoxEntry)

install(TARGETS ogcalc DESTINATION bin)
install(TARGETS SpinBoxEntry DESTINATION lib)
install(TARGETS SpinBoxEntryPlugin DESTINATION ${QT_PLUGINS_DIR}/designer)

set(ARCHIVE_NAME
    "ogcalc-qt-ui-cmake-${ogcalc_VERSION_MAJOR}.${ogcalc_VERSION_MINOR}.${ogcalc_VERSION_PATCH}")
# Normally, "git archive" would work well, but it doesn't follow
# symlinks.  Due to using symlinks heavily, we need to follow them to
# avoid creating broken archives.
add_custom_target(dist
    COMMAND tar chfv - "--transform='s;^;${ARCHIVE_NAME}/;'" \$\$\(git ls-tree -r --name-only HEAD . | grep -v '^.gitignore'\) | gzip -9 > ${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.gz
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
