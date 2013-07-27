.. _sec-python:

Python
======

Introduction
------------

Python is a popular scripting language, particularly with beginners to
programming, but also used by many veteran developers.  It has a clear
and simple syntax, coupled with decent support for both procedural and
object-oriented programming.  Unlike C and C++, Python is an
interpreted language, and so compilation is not necessary.  This has
some advantages, for example development is faster, particularly when
prototyping new code.  There are also disadvantages, such as programs
running much slower than machine code.  Worse, all code paths must be
run in order to verify they are syntactically correct, and simple
typing mistakes can result in a syntactically correct, but
dysfunctional, program.  A good C or C++ compiler would catch these
errors, but Python cannot.  There are tools, such as
:program:`pychecker`, which help with this.  The purpose of this
document is not to advocate any particular tool, however.  The pros
and cons of each language have been discussed at length in many other
places.

Python has a language binding for GTK+, pyGTK, which allows the
creation of GTK+ user interfaces directly, including the ability to
derive new classes from the standard GTK+ classes, and use Python
functions and object methods as callbacks.  The functionality
provided by :program:`libglade` in C is also similarly available.

In the next section, examples show the use of pyGTK to create the
:program:`ogcalc` interface, using both plain GTK+ and Glade.
The author wrote the Python scripts with only a few hours of Python
experience, directly from the original C source, which demonstrates
just how easy Python is to get into.

Code listing
------------

:file:`gtk/python/plain/ogcalc`

.. literalinclude:: ../gtk/python/plain/ogcalc
   :language: python
   :lines: 26-333

:file:`gtk/python/glade/ogcalc`

.. literalinclude:: ../gtk/python/glade/ogcalc
   :language: python
   :lines: 26-131

Analysis
--------

What the GTK+ classes and methods do here will not be discussed,
having been covered in the previous sections.  Instead, the
Python-specific differences will be examined.

.. code-block:: python

   import pygtk
   pygtk.require('2.0')
   import gtk

This preamble imports the pyGTK modules for us, and checks that the
GTK+ version is correct.

.. code-block:: python

   class OgcalcSpinEntry(gtk.HBox):
       def __init__(self, label_text, tooltip_text,
                    adjustment, digits):
           gtk.HBox.__init__(self, False, 5)
           …

   class OgcalcResult(gtk.HBox):
       def __init__(self, label_text, tooltip_text):
           gtk.HBox.__init__(self, False, 5)
           …

These two simple classes derive from :py:class:`GtkHBox`.  They are the
Python equivalents of the :c:func:`create_spin_entry` and
:c:func:`create_result_label` functions in Section :ref:`sec-gtkc`.
They are mostly identical to the C code in terms of the objects
created and the object methods used.  The main difference is that
:c:func:`create_spin_entry` has a :c:data:`spinbutton_pointer`
argument which has been dropped here.  The same difference applies to
:c:func:`create_result_label` for
:c:data:`result_label_pointer`.  In Python, we can't pass pointers
as easily as in C, however we can access the spinbutton as a member of
the :py:class:`OgcalcSpinEntry` object instead (``object.spinbutton``).

Note that because the object is derived, the :py:func:`__init__`
initialiser (constructor) has to manually chain up to the parent
initialiser in order to correctly initialise the class instance.

.. code-block:: python

   class Ogcalc(gtk.Window):

is our main application object.  It derives from
:py:class:`gtk.Window`.

.. code-block:: python

       def on_button_clicked_reset(self, data=None):
           self.pg_entry.spinbutton.set_value(0.0)
           …
           self.abv_result.result_value.set_text("")

This function resets the interface to its initial state.  Note that
all the member variables are accessed through :py:attr:`self`, which
is the class instance, and that the spinbutton and value label to be
manipulated are contained within the helper objects defined above.

.. code-block:: python

       def on_button_clicked_calculate(self, data=None):
           …
           self.og_result.result_value.set_markup \
           ("<b>%(result)0.2f</b>" %{'result': og})

This function does the calculation.  Note the substitution of the
result value into the string, which is rather simpler than both the C
and the C++ code used to construct the result string.

.. code-block:: python

       def __init__(self):
           gtk.Window.__init__(self, gtk.WINDOW_TOPLEVEL)
           self.set_title("OG & ABV Calculator")

This is the initialiser for the :py:class:`Ogcalc` class.  It starts by
chaining up the :py:class:`gtk.Window` initialiser, and then calls the
:py:func:`set_title` :py:class:`gtk.Window` method to set the window
title.

.. code-block:: python

           self.connect("destroy", gtk.main_quit, None)

This connects the "destroy" signal to the :py:func:`gtk.main_quit`
function.  There's far less to type than the C and C++ equivalents,
and hence it's rather more readable.

.. code-block:: python

           self.pg_entry = \
           OgcalcSpinEntry("PG:", "Present Gravity (density)",
                           adjustment, 2)

Here we create a helper object for entering the PG value.

.. code-block:: python

           self.abv_result = \
           OgcalcResult("ABV %:", "Percent Alcohol By Volume")

Here we create a helper object for displaying the ABV result.

.. code-block:: python

           button1 = gtk.Button(None, gtk.STOCK_QUIT, False)
           button1 = gtk.Button("_Reset", None, True)
           button2 = gtk.Button("_Calculate", None, True)

This code creates the buttons.  Unlike C and C++, where different
functions or overloaded constructors were used to create an object
with different parameters, Python only has a single initialiser
function, which is used for both stock and non-stock widgets.
Depending on whether a stock or non-stock widget is being created, the
first and third, or the second arguments are redundant, respectively.

.. code-block:: python

           button1.connect_object("clicked",
               Ogcalc.on_button_clicked_reset, self)

This connects the "clicked" signal to the :py:class:`Ogcalc`
:py:func:`on_button_clicked_reset` method of the :py:attr:`self`
object.

.. code-block:: python

           self.pg_entry.spinbutton.connect_object("activate",
               gtk.Widget.grab_focus, self.ri_entry.spinbutton)

This connects the "activate" signal to the :py:class:`Ogcalc`
:py:func:`grab_focus` method of the
:py:attr:`self.ri_entry.spinbutton` object.

.. code-block:: python

   if __name__ == "__main__":
       ogcalc = Ogcalc()
       ogcalc.show()
       gtk.main()

The classes are intended for use as a module in a larger program.
When run as a standalone script from the command-line, we "run" the
class by creating an instance of it, showing it, and then run the GTK+
main loop.

The Glade code is identical, except for loading the Glade interface:

.. code-block:: python

           self.xml = gtk.glade.XML("ogcalc.glade",
                                    "ogcalc_main_vbox", None);

Here the Glade interface is loaded, rooted at the
``ogcalc_main_vbox`` widget,

.. code-block:: python

           self.pg_val = self.xml.get_widget("pg_entry");

and now a specific widget is pulled out of the XML interface
description.
