#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

dnl The minimum version of autoconf required.
AC_PREREQ(2.59)
dnl Initialise automake with the package name, version and
dnl bug-reporting address.
AC_INIT([ogcalc], [1.2.0], [rleigh@debian.org])
dnl For safety, check we are in the right directory by
dnl checking for a known unique file.
AC_CONFIG_SRCDIR([C/plain/ogcalc.c])
dnl Place auxilliary scripts here.
AC_CONFIG_AUX_DIR([scripts])
dnl Put macro definitions here (though they aren't used).
AC_CONFIG_HEADER([config.h])

dnl Initialise automake stuff.
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.
PKG_CHECK_MODULES([GTK], [gtk+-2.0])
PKG_CHECK_MODULES([GLADE], [libglade-2.0])
PKG_CHECK_MODULES([GTKMM], [gtkmm-2.4])
PKG_CHECK_MODULES([GLADEMM], [libglademm-2.4])

# Checks for header files (none at the moment).

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions (none at the moment).

dnl Configure which files to generate.
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([C/Makefile])
AC_CONFIG_FILES([C/plain/Makefile])
AC_CONFIG_FILES([C/glade/Makefile])
AC_CONFIG_FILES([C/gobject/Makefile])
AC_CONFIG_FILES([C++/Makefile])
AC_CONFIG_FILES([C++/plain/Makefile])
AC_CONFIG_FILES([C++/glade/Makefile])
AC_CONFIG_FILES([figures/Makefile])
dnl Output the generated config.status script.
AC_OUTPUT
