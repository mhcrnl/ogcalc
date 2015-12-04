Introduction
============

The purpose of this tutorial
----------------------------

This tutorial is intended to teach you some of the basic concepts
needed to write a working GUI application using either the Qt or GTK+
toolkits.  It starts right from the beginning, so if you've never
written any GUI code ever before, you might find this useful in
explaining some of the underlying concepts and practices.

The tutorial starts with a short specification for a very simple
calculator application, looking at how the GUI might look and
function, before any code is encountered.  Next, some of the basics of
how graphical interfaces are structured and function are covered.  The
example program is then implemented identically in both Qt and GTK+,
which makes it possible to see the similarities and differences
between them.  Both the Qt and GTK+ examples include several variants
to demonstrate how to write everything entirely by hand, or make use
of interactive GUI designers to do the bulk of the interface layout.
If you are looking into using either Qt or GTK+ for a new application
and you're not sure which is most appropriate, you might find this of
help.

I wrote the first version of this tutorial in the 2003-2004 timeframe
when I originally learned to use GTK+.  At the time, I found the
documentation quite poor, and so over the next few years I developed
it as a working example of how to get to grips with the fundamentals
of using the C API, including :c:type:`GObject`, :program:`glade` and
other important parts of the GTK+ puzzle.  I later added versions
which demonstrated how to effectively use other languages using the
GTK+ bindings in C++ using :program:`gtkmm`, and in Python with PyGTK.
At the time I was involved in using Gtkmm for a commercial application
and also involved in fixing Windows portability bugs in GTK+.  Fast
forward a decade, and it's 2013.  I've reworked the tutorial and added
major new secions using Qt rather than GTK+, and also updated the GTK+
part to include :c:type:`GtkBuilder` in addition to :program:`glade`.

The purpose of this tutorial is not a "Qt vs. GTK+" contest.  It's
explicitly reimplementing the same user interface functionality,
behaviour and layout in both toolkits in order to make the comparison
as objective as possible.  As will be made clear, the basic concepts
underlying graphical user interface logic in both toolkits are
very similar.  The reader may wish to consider some factors which may
be important to them:

* Code size
* Code clarity
* Code maintainability
* Code robustness and safety
* Code portability
* Compatibility with other tools and libraries
* Support for particular programming languages
* Support for different platforms and display systems
* Programmer time and efficiency
* Barrier to entry for new team members
* Community surrounding and development of the "platform"
* Long term prospects of the "platform"

Should you use Qt or GTK+?  The decision is entirely up to you.  My
personal experiences to date would lead me to say that **Qt** is a
better choice.  However, when I originally wrote this tutorial, I
would have argued that GTK+ would be the most sensible choice for
various reasons.  But I was wrong.  It's now abuntantly clear to me
that GTK+ is inferior for many technical and other reasons, which
we'll cover as we go through the details in tutorial.  However, that
is not to say that GTK+ may not be preferable in some circumstances.
If you want a quick summary, the rest of this section and the
:ref:`sec-conclusion` section contain the most salient points.


What is Qt?
-----------

Qt is a *toolkit* used for writing graphical applications (and much
more).  Qt works well on Linux (X11, soon Wayland), Microsoft Windows
and the Apple Macintosh, as well as on small handheld devices such as
mobile phones, and so may be used for cross-platform software
development.  The examples in this tutorial will build and run on
Linux, Windows and MacOS X.

One well known use of Qt is as the foundation of KDE, and there are a
large number of applications using it, from free software to
commercial and proprietary applications on all platforms.

Qt is written in C++, with `Qt bindings
<https://qt-project.org/wiki/Category:LanguageBindings>`_ available
other languages.  This tutorial is intended as a simple introduction
to writing Qt applications in C++ and Python, using the 5.x version of
Qt.  It also covers the use of the Qt designer for *rapid application
development* (RAD).  The examples will also build with Qt 4.x with
minor adjustments to the sources.

The `Qt Project website <https://qt-project.org/>`_ contains
everything you'll need to know about Qt.


What is GTK+?
-------------

GTK+ is also a *toolkit* used for writing graphical applications.
Originally written for the X11 windowing system, it has now been
ported to other systems, such as Microsoft Windows and the Apple
Macintosh, and so may in theory be used for cross-platform software
development.  The unfortunate reality is that it's effectively only
usable with X11 on Linux; the MacOS X port requires use of the X11
server so doesn't integrate well with the rest of the system, and the
Windows port has remained perpetually buggy.  In consequence, if you
want to be able to deploy robust, integrated, visually pleasing
applications on multiple platforms, GTK+ will be unable to fulfil this
requirement.

GTK+ was written as a part of the *GNU Image Manipulation Program*
(GIMP), but has long been a separate project, used by many other free
software projects, the most notable being the *GNU Network Object
Model Environment* (GNOME) Project.  Unfortunately, in recent years
GTK+ has lost most of its core maintainers, and is currently in a
state of apparent neglect.  The current maintainers have stated that
they only consider it as a toolkit for GNOME3, and the new GTK+
version 3.x releases have had a number of regressions and usability
problems, some in consequence of this.  The fact that the future of
GTK+ is to become increasingly GNOME-only is something that adopters
might need to consider.  If you're developing non-GNOME non-Linux
applications, be aware that your needs won't be well supported, and
it's likely to get worse.  This tutorial requires GTK+ 2.x (2.6 and
later); there are no plans to port to GTK+ 3.x, the bleak future of
GTK+ 3.x being the primary reason for this.

GTK+ is written in C and, because of the ubiquity of the C language,
`GTK+ bindings <http://www.gtk.org/language-bindings.php>`_ have been
written to allow the development of GTK+ applications in many other
languages.  This tutorial is intended as a simple introduction to
writing GTK+ applications in C, C++ and Python, using the 2.x (2.6 and
later) version of GTK+.  It also covers the use of the Glade user
interface designer for *rapid application development* (RAD).

The `GTK+ Project website <http://www.gtk.org/>`_ contains links to
all things GTK+.  Unfortunately, it's recently had a GNOME makeover
and is now fairly bland and vapid.  The nice GTK+ logo is gone, and
most of the links direct you to the GNOME website---you might have to
dig a bit to find what you want, particularly documentation for older
versions.


Extra reading
-------------

It is assumed that the reader is familiar with C and C++ programming.
If you're using Qt, the `Qt online documentation
<http://qt-project.org/doc/qt-5.1/qtdoc/index.html>`_ will be useful to
refer to as you're going through the tutorial, and also includes a
number of useful examples and tutorials.  If you're using GTK+, there
is also `GTK+ online documentation <http://www.gtk.org/documentation.php>`_
and it would be helpful to work through the "Getting Started" chapter
of the `GTK+ tutorial
<https://developer.gnome.org/gtk-tutorial/stable/>`_ before reading
further.  The GTK+, GLib, libglade, Gtkmm and libglademm API
references will be useful while working through the examples.  Very
little Python knowledge is required, but the PyGTK `tutorial
<http://www.pygtk.org/pygtk2tutorial/index.html>`_ and `API references
<http://www.pygtk.org/reference.html>`_, will also be useful.


Building the example code
-------------------------

Several working, commented examples accompany the tutorial.  They are
also available from `people.debian.org/~rleigh/ogcalc/
<http://people.debian.org/~rleigh/ogcalc/>`_.  To build them, type:

::

   ./configure
   make

This will check for the required libraries and build the example code.
Each program may then be run from within its subdirectory.  If some
libraries are missing, some of the examples might not be built. The
output of :program:`configure` should indicate any missing components.

I have been asked on various occasions to write a tutorial to explain
how the GNU autotools work.  While this is not the aim of this
tutorial, I have converted the build to use the autotools as a simple
example of their use.  All the GTK+ examples make use of
:program:`automake`.  The Qt samples have been written to demonstrate
the use of :program:`cmake`, :program:`qmake`, :program:`automake`,
and plain :program:`make`.
