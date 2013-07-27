Qt basics
=========

Prequisites
-----------

Qt is a collection of several C++ libraries.  This tutorial assumes
some basic C++ knowledge such as classes, class methods, inheritance,
polymorphism.  We aren't doing anything particularly esoteric or
advanced however, so if you're completely new to C++, it shouldn't be
too difficult to follow.

Libraries
---------

Qt is comprised of several separate libraries, many of which are not
related to GUI programming.  In this tutorial, we only require a
select few:

:program:`Qt5Core`
   The core Qt library.
:program:`Qt5Gui`
   The GUI part of Qt.
:program:`Qt5Widgets`
   The standard GUI widgets, which are separate from the GUI itself.
:program:`Qt5Svg`
   The SVG library.  This is optional; we're only using this to load
   an SVG icon for the application.  If it's not used, the icon won't
   load, but will otherwise not cause any problems.

