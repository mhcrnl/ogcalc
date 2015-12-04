# ogcalc - a GTK+ program written in C, but using libglade to
# construct the interface and connect all signals, and GObject to
# create a class derived from a GTK+ GtkWindow class.

# Not using GNU conventions
AUTOMAKE_OPTIONS = foreign

# The program to build.
noinst_PROGRAMS = ogcalc

# The sources and compiler flags.
ogcalc_SOURCES = ogcalc.c ogcalc.h ogcalc-main.c
ogcalc_CFLAGS = $(GTKBUILDER_CFLAGS)
ogcalc_LDADD = $(GTKBUILDER_LIBS)

# The Glade user interface files.
noinst_DATA = ogcalc.ui

# Files not automatically distributed which should be included
# in the distribution tarball.
EXTRA_DIST =		\
	$(noinst_DATA)	\
	README.md
