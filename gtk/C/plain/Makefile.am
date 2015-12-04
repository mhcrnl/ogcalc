# ogcalc - a basic GTK+ program written in C.

# Not using GNU conventions
AUTOMAKE_OPTIONS = foreign

# The program to build.
noinst_PROGRAMS = ogcalc

# The sources and compiler flags.
ogcalc_SOURCES = ogcalc.c
ogcalc_CFLAGS = $(GTK_CFLAGS)
ogcalc_LDADD = $(GTK_LIBS)

# Files not automatically distributed which should be included
# in the distribution tarball.
EXTRA_DIST = README.md
