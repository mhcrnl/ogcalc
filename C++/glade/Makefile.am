# ogcalcmm a GTK+ program written in C++, using Gtkmm and libglademm
# (the C++ bindings for GTK+ and libglade).

# The program to build.
bin_PROGRAMS = ogcalc

# The sources and compiler flags.
ogcalc_SOURCES = ogcalc.cc ogcalc.h ogcalc-main.cc
ogcalc_CXXFLAGS = $(GLADEMM_CFLAGS)
ogcalc_LDADD = $(GLADEMM_LIBS)

# The Glade user interface files
noinst_DATA = ogcalc.glade ogcalc.gladep

# Files not automatically distributed which should be included
# in the distribution tarball.
EXTRA_DIST = $(noinst_DATA)
