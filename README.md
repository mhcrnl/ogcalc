ogcalc
======

Calculate %ABV and OG from PG, RI and CF.


Legal
-----

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
USA.

The full licence text is available in the COPYING file.


Background
----------

While learning how to use GTK+, I wrote a small demo program to
explore the features of GTK+.  Later, I wanted to determine if using
either Glade (the GTK+ interface designer) or Gtkmm (the GTK+ C++
bindings) could make my life simpler, by making programs smaller,
better structured and more maintainable.  A year later, I needed to
evaluate the use of Python, and added the Python examples.

Several years later, after getting tired of the many problems which
make GTK+ a quite unproductive toolkit to work with, I added examples
using Qt version 5, again with variants similar to the above: plain
Qt, with the UI designer and uic, with the Qt designer as a plugin for
reuse with Qt designer, and with the PyQt Python bindings.

This package includes the same small program written in:

* GTK+2, using:
  * C.
  * C, using libglade.
  * C, using and GObject and libglade.
  * C++, using Gtkmm.
  * C++, using Gtkmm and libglademm.
  * Python, using PyGTK.
  * Python, using PyGTK and Glade.
* Qt5, using:
  * C++
  * C++, using uic
  * C++, using a ui plugin
  * PyQt

All of these programs use exactly the same interface, and behave in
exactly the same way, using the same program logic.  This allows an
accurate comparison to be made between the different programs, in
terms of their size, structure and logic.


Documentation
-------------

All the source files are extensively commented, so that it can be seen
what every function is doing.

A tutorial document further documents ogcalc, as well as GTK+ and Qt in
general.  Run `make html` or `make latexpdf` in the `doc` directory to
build the tutorial (requires Sphinx).


Building
--------

For GTK+, change to the subdirectory containing the example of choice, then run:

* `autoreconf` to set up the autotools
* `./configure` to configure the source tree.
* `make` or `make all` to build everything.
* `glade-2 ogcalc.glade` to view/edit the Glade interface.

All the programs require the GTK+ >= 2.4 libraries and headers to be
installed.  The Glade examples require libglade and its headers to be
installed.  ogcalcmm requires Gtkmm, libglademm and their headers to
be installed.

On a Debian system, these packages are required:

* ogcalc: libgtk2.0-dev (>= 2.4.1-1)
* ogcalc-gl: libglade2-dev
* ogcalcmm: libgtkmm-2.4-dev, libglademm-2.4-dev
* python: python-gtk2, python-glade2
* glade-2 provides the Glade interface editor.

For Qt, the examples include variants using GNU make,
automake and CMake.

* For GNU make, simply run `make`
* For automake, build as described for the autotools for GTK+, above
* For CMake, run `cmake .` and then `make`.  Other build systems are
  available via CMake, if required; see the CMake documentation.

On a Debian system, these packages are required:

* cmake
* qtbase5-dev qttools5-dev qt5-default libqt5svg5-dev
