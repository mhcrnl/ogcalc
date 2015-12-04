#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

dnl The minimum version of autoconf required.
AC_PREREQ(2.59)
dnl Initialise automake with the package name, version and
dnl bug-reporting address.
AC_INIT([ogcalc], [1.5.0], [rleigh@codelibre.net])
dnl For safety, check we are in the right directory by
dnl checking for a known unique file.
AC_CONFIG_SRCDIR([ogcalc.cpp])
dnl Place auxilliary scripts here.
AC_CONFIG_AUX_DIR([scripts])
dnl Put macro definitions here (though they aren't used).
AC_CONFIG_HEADER([config.h])

dnl Initialise automake stuff.
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_ENABLE_SHARED
AC_DISABLE_STATIC
AC_PROG_LIBTOOL
AC_PATH_PROG([QMAKE], [qmake])

# Checks for libraries.
PKG_CHECK_MODULES([QT], [Qt5Core Qt5UiTools Qt5Gui Qt5Widgets Qt5Svg])
PKG_CHECK_MODULES([QTW], [Qt5Widgets])
PKG_CHECK_MODULES([QTUI], [Qt5Core Qt5UiTools Qt5Designer])

plugindir=$(${QMAKE} -query QT_INSTALL_PLUGINS)
AC_SUBST(plugindir)

# Checks for header files (none at the moment).

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions (none at the moment).

dnl Configure which files to generate.
AC_CONFIG_FILES([Makefile])

dnl Output the generated config.status script.
AC_OUTPUT
