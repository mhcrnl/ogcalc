Building Qt applications
========================

There are several different ways to build the examples in this
tutorial and, by extension, your own applications.

* by hand
* using :program:`make`
* using :program:`automake`
* using :program:`qmake`
* using :program:`cmake`

Each example contains a set of subdirectories.  The code is identical
in each directory (it's symlinked to :file:`common`), but each
subdirectory contains the files specific to a particular build system.

These examples are all written in C++.  Examples in Python are in
:file:`python` subdirectories.  The Python examples do not require
building and may be run directly, with the exception of the :file:`ui`
sample which contains a :file:`Makefile` to generate a source file.

Building by hand
----------------

Example subdirectory: :file:`byhand`.

To build:

::

   ./build

This directory contains a :program:`build` script which is a simple
list of the commands to execute in order to build the example.

While a simple list of steps is easy to understand, which is the
reason they are included in the tutorial, it becomes painful very
quickly:

* All files must be rebuilt, even if only one source file changed.
* No dependency tracking.
* No parallel building.
* No portability (this script requires a shell, and won't produce
  Windows :file:`.exe` or MacOS X :file:`.app` applications).

Building with :program:`make`
-----------------------------

Example subdirectory: :file:`make`.

To build:

::

   make

:program:`make` is the default build tool on Linux and MacOS X.
Windows users' won't have it unless extra tools are installed (see
`Cygwin <http://www.cygwin.com>`_, `MinGW <http://www.mingw.org/>`_
and the MinGW version of the `packaged version of Qt
<http://qt-project.org/downloads>`_ for Windows ).  Plain make can
work well, but it's lacking a few important features such as:

* Being able to detect platform-specific features including library locations.
* Using correct suffixes for program and library names.
* Knowing how to correctly compile and link programs and libraries/
* Limited dependency tracking.

If you are only supporting a single platform, then these issues won't
be particularly apparent, though most missing features may be added by
hand with effort.  However, supporting multiple platforms cleanly is
hard, even if GNU :program:`make` does at least make it possible.


Building with :program:`automake`
---------------------------------

Example subdirectory: :file:`automake`.

To build:

::

   autoreconf -i
   ./configure
   make

Coupled with :program:`autoconf` and :program:`libtool`, the GNU
"autotools" address a number of the most important shortcomings of
plain :program:`make`.  The :program:`configure` script generated by
:program:`autoconf` detects the platform-specific details,
:program:`automake` generates a complex but comprehensive
:file:`Makefile.in` from a simpler :file:`Makefile.am` template.  A
:file:`Makefile` for use by :program:`make` is generated as the end
result of this process.

The "autotools" do not replace :program:`make`, but rather add a
separate layer (or set of layers) above it to add higher-level
functionality.  The more complex generated :file:`Makefile` also adds
features like sophisticated dependency tracking when using a
compatible compiler.  However, some limitations still remain

* It's still dependent upon having a Unix shell, so won't work on
  Windows by default/
* While platform specific details are abstracted making program and
  library building possible, working properly on multiple platforms
  still requires much more work.
* Learning how to use :program:`autoconf` and :program:`automake`
  effectively is a significant investment of time and effort.

Building with :program:`qmake`
------------------------------

Example subdirectory: :file:`qmake`.

To build (Linux and MacOS):

::

   qmake
   make

:program:`qmake` is provided with Qt.  Like :program:`automake`, it's
a :file:`Makefile` generator, which takes a :file:`.pro` project file
as input and outputs a platform-specific build file.  This allows it
to support systems which don't use :program:`make` since it's not
restricted to generating :file:`Makefile`, and is also no longer
dependent upon a Unix shell to function.  If you're using Qt Creator
as an IDE, it can work with project files and :program:`qmake`
directly.

Since Qt applications may use :program:`moc` to parse and generate
additional source code and headers, :program:`uic` to compile forms
etc., these can be a pain to deal with in other build systems (though
it's certainly possible).  However, :program:`qmake` understands how
to deal with them natively, making working with them transparent and
effortless.

However, there are some downsides:

* Project files are very simple, and much of the full power of
  :program:`make` is unavailable.
* In a big project, you might already be using another build system.
* You might need to use libraries in addition to the Qt libraries, and
  integrating them into the build may be difficult.
* It's a library-specific build system like Boost's :program:`bjam`;
  you probably don't want to learn and use yet another build tool
  especially since its scope is quite limited.

If you are developing Qt applications only, then :program:`qmake` is a
good choice due to the nice integration of all the tools.  However,
I'm reluctant to recommend it for more heterogeneous projects or for
bigger projects due to its limitations.

Building with :program:`cmake`
------------------------------

To build (Linux and MacOS):

::

   cmake .
   make

Like :program:`qmake`, :program:`cmake` is a :file:`Makefile`
generator, which takes a :file:`CMakeLists.txt` file as input and
outputs a platform-specific build file.  As for :program:`qmake`, this
allows it to support systems which don't use :program:`make` since
it's not restricted to generating :file:`Makefile`, and is also no
longer dependent upon a Unix shell to function.  It can, for example,
also generate project files for Eclipse, KDevelop and Microsoft Visual
Studio.

:program:`cmake` is interesting because it combines the
platform-specific feature and library autodetection of
:program:`autoconf`, has a similar template style to
:program:`automake`, while also allowing very flexible extension in a
platform-independent manner using macros, custom commands, etc.  It
also provides commands for handling the automatic generation and
building of sources and headers with :program:`moc` and
:program:`uic`.

:program:`cmake` will never provide the depth of coverage that the
"autotools" provide (they are arbitrarily extensible and can be made
to do anything).  However, it has pre-canned functions to do 99% of
what you want, and the remaining 1% can be easily tacked on.  In
contrast, the autotools would get you 75% of the way there, and
require a whole pile of extra work on top, which would potentially
require writing large and hard to maintain amounts of :program:`m4`
macrocode and :program:`make` rules while the :program:`cmake`
equivalent is relatively compact.


Summary
-------

I don't recommend the use of scripts or plain :program:`make` except
for the most simple, trivial projects where the application is only
being built for a single system.  Even then, think about using a
better system!

:program:`qmake` seems like a fine choice for Qt-only projects, but
less ideal outside this scope.

I'm a newcomer to :program:`cmake`, having used the autotools
extensively for the last 14 years.  I don't yet have the expertise or
experience to recommend :program:`cmake`, but it certainly looks like
it would be the ideal choice for cross-platform projects which also
have to deal with Windows.  If you only deal with Linux and MacOS,
then the autotools might be better in some circumstances.  However,
given the massive complexity of the autotools, I would be far from
surprised to see :program:`cmake` displace them in the future.

I used writing the Qt part of this tutorial as an exercise in learning
the basics of :program:`cmake`, including building libraries and
plugins in addition to basic programs.  It was fairly straightforward,
certainly much less difficult in time and effort than it would be
using the autotools without any prior experience.  I would definitely
recommend trying out :program:`cmake` first.

However, don't let my experiences influence you too greatly.  The
above discussion is necessarily brief, and does not go into any of the
systems in great depth; it would be worth considering your
requirements researching them all in detail before committing to one,
since this may be a major commitment with many implications, some of
which may not be immediately obvious.  Look at the examples, try them
all, and compare them for yourself.  Also consider that these are
simple examples; think about how each would differ when you also
factor in keeping them updated and maintained in a bigger, changing,
codebase.
