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

SET(ogcalc_SOURCES ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/ogcalc.cpp ${PROJECT_SOURCE_DIR}/SpinBoxEntry.cpp)
SET(ogcalc_HEADERS ${PROJECT_SOURCE_DIR}/ogcalc.h ${PROJECT_SOURCE_DIR}/SpinBoxEntry.h)

if(WIN32)
  set(ogcalc_RESOURCES ${PROJECT_SOURCE_DIR}/ogcalc.rc)
endif(WIN32)

add_executable(ogcalc ${ogcalc_SOURCES} ${ogcalc_HEADERS_MOC} ${ogcalc_RESOURCES})
qt5_use_modules(ogcalc Core Gui Widgets Svg)

install(TARGETS ogcalc DESTINATION bin)

set(ARCHIVE_NAME
  "${CMAKE_PROJECT_NAME}-${OGCALC_VERSION_MAJOR}.${OGCALC_VERSION_MINOR}.${OGCALC_VERSION_PATCH}")
# Normally, "git archive" would work well, but it doesn't follow
# symlinks.  Due to using symlinks heavily, we need to follow them to
# avoid creating broken archives.
add_custom_target(dist
    COMMAND tar chfv - "--transform='s;^;${ARCHIVE_NAME}/;'" \$\$\(git ls-tree -r --name-only HEAD . | grep -v '^.gitignore'\) | gzip -9 > ${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.xz
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

# build CPACK installer (not currently complete)
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${OGCALC_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${OGCALC_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${OGCALC_VERSION_PATCH}")
set(CPACK_SOURCE_PACKAGE_FILE_NAME
  "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_GENERATOR ZIP)
set(CPACK_PACKAGE_CONTACT "Roger Leigh <rleigh@debian.org>")
set(CPACK_SOURCE_IGNORE_FILES "${CMAKE_CURRENT_BINARY_DIR}/;~$;${CPACK_SOURCE_IGNORE_FILES}")
include (CPack)
