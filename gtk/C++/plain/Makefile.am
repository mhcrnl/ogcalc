# ogcalcmm a GTK+ program written in C++, using Gtkmm
# (the C++ bindings for GTK+).

# Not using GNU conventions
AUTOMAKE_OPTIONS = foreign

# The program to build.
bin_PROGRAMS = ogcalc

# The sources and compiler flags.
ogcalc_SOURCES = ogcalc.cc ogcalc.h ogcalc-main.cc
ogcalc_CXXFLAGS = $(GTKMM_CFLAGS)
ogcalc_LDADD = $(GTKMM_LIBS)

# Files not automatically distributed which should be included
# in the distribution tarball.
EXTRA_DIST = README.md
