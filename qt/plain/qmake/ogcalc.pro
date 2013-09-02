#-------------------------------------------------
#
# Project created by QtCreator 2013-07-07T19:09:57
#
#-------------------------------------------------

QT       += core gui widgets svg

TARGET = ogcalc
TEMPLATE = app

VERSION = 1.5.0

SOURCES += main.cpp\
        ogcalc.cpp \
    SpinBoxEntry.cpp

HEADERS  += ogcalc.h \
    SpinBoxEntry.h

QMAKE_INFO_PLIST = ogcalc.plist

ICON = ogcalc.icns

RC_FILE = ogcalc.rc

DISTFILES += AUTHORS ChangeLog COPYING NEWS README

ARCHIVE_NAME = ogcalc-qt-plain-qmake-$$VERSION
QMAKE_EXTRA_TARGETS += dist
dist.target = dist
dist.commands += tar chfv - "--transform='s;^;$$ARCHIVE_NAME/;'" \$\$\(git ls-tree -r --name-only HEAD . | grep -v '^.gitignore'\) | gzip -9 > "$${ARCHIVE_NAME}.tar.gz"
