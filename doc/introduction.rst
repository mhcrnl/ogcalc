Introduction
============

What is Qt?
-----------

What is GTK+?
-------------

GTK+ is a *toolkit* used for writing graphical applications.
Originally written for the X11 windowing system, it has now been
ported to other systems, such as Microsoft Windows and the Apple
Macintosh, and so may be used for cross-platform software development.
GTK+ was written as a part of the *GNU Image Manipulation Program*
(GIMP), but has long been a separate project, used by many other free
software projects, one of the most notable being the *GNU Network
Object Model Environment* (GNOME) Project.

GTK+ is written in C and, because of the ubiquity of the C language,
*bindings* have been written to allow the development of GTK+
applications in many other languages.  This short tutorial is intended
as a simple introduction to writing GTK+ applications in C, C++ and
Python, using the 2.x (2.6 and later) version of GTK+.  It also
covers the use of the Glade user interface designer for *rapid
application development* (RAD).

It is assumed that the reader is familiar with C and C++ programming,
and it would be helpful to work through the "Getting Started"
chapter of the GTK+ tutorial before reading further.  The GTK+, GLib,
libglade, Gtkmm and libglademm API references will be useful while
working through the examples.  Very little Python knowledge is
required, but the Python tutorial and manual, and the PyGTK and Glade
API references, will also be useful.

I hope you find this tutorial informative.  Please send any
corrections or suggestions to `rleigh@debian.org
<mailto:rleigh@debian.org>`_.

Building the example code
-------------------------

Several working, commented examples accompany the tutorial.  They are
also available from `people.debian.org/~rleigh/ogcalc/
<http://people.debian.org/~rleigh/ogcalc/>`_.  To build them, type:

::

   ./configure
   make

This will check for the required libraries and build the
example code.  Each program may then be run from within its
subdirectory.

I have been asked on various occasions to write a tutorial to explain
how the GNU autotools work.  While this is not the aim of this
tutorial, I have converted the build to use the autotools as a simple
example of their use.

Legal bit
---------

This tutorial document, the source code and compiled binaries, and all
other files distributed in the source package are copyright
© 2003--2013 Roger Leigh.  These files and binary programs
are free software; you can redistribute them and/or modify them under
the terms of the GNU General Public Licence as published by the Free
Software Foundation; either version 2 of the Licence, or (at your
option) any later version.

A copy of the GNU General Public Licence version 2 is provided in the
file :file:`COPYING`, in the source package from which this
document was generated.
