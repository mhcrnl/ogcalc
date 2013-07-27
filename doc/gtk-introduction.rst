GTK+ basics
===========

Objects
-------

GTK+ is an *object-oriented* (OO) toolkit.  I'm afraid that unless one
is aware of the basic OO concepts (classes, class methods,
inheritance, polymorphism), this tutorial (and GTK+ in general) will
seem rather confusing.  On my first attempt at learning GTK+, I didn't
understand it, but after I learnt C++, the concepts GTK+ is built on
finally made sense.

The C language does not natively support classes, and so GTK+ provides
its own object/type system, **GObject**.  GObject provides
objects, inheritance, polymorphism, constructors, destructors and
other facilities such as reference counting and signal emission and
handling.  Essentially, it provides C++ classes in C.  The syntax
differs a little from C++ though.  As an example, the following C++

.. code-block:: c++

   myclass c;
   c.add(2);

would be written like this using GObject:

.. code-block:: c

   myclass *c = myclass_new();
   myclass_add(c, 2);

The difference is due to the lack of a :c:data:`this`
pointer in the C language (since objects do not exist).  This means
that class methods require the object pointer passing as their first
argument.  This happens automatically in C++, but it needs doing
"manually" in C.

Another difference is seen when dealing with polymorphic objects.  All
GTK+ widgets (the controls, such as buttons, checkboxes, labels, etc.)
are derived from :c:type:`GtkWidget`.  That is to say, a
:c:type:`GtkButton` *is a* :c:type:`GtkWidget`, which *is a*
:c:type:`GtkObject`, which *is a* :c:type:`GObject`.  In C++, one can call
member functions from both the class and the classes it is derived
from.  With GTK+, the object needs explicit casting to the required
type.  For example

.. code-block:: c++

   GtkButton mybutton;
   mybutton.set_label("Cancel");
   mybutton.show();

would be written as

.. code-block:: c

   GtkButton *mybutton = gtk_button_new();
   gtk_button_set_label(mybutton, "Cancel");
   gtk_widget_show(GTK_WIDGET(mybutton))

In this example, :cpp:func:`set_label` is a method of
:cpp:class:`GtkButton`, whilst :cpp:func:`show` is a method of
:cpp:class:`GtkWidget`, which requires an explicit cast.  The C API
uses functions prefixed with the class name, the object being operated
upon being passed as the first argument.  The ``GTK_WIDGET()`` cast
is actually a form of *run-time type identification* (RTTI).  This
ensures that the objects are of the correct type when they are used.

Objects and C "work", but there are some issues to be aware of, such
as a lack of type-safety of callbacks and limited compile-time type
checking.  Using GObject, deriving new widgets is both complex and
error-prone.  For these, and other, reasons, C++ may be a better
language to use.  :program:`libsigc++` provides type-safe signal
handling, and all of the GTK+ (and GLib, Pango et. al.) objects are
available as standard C++ classes.  Callbacks may also be class
methods, which makes for cleaner code since the class can contain
object data, removing the need to pass in data as a function argument.
These potential problems will become clearer in the next sections.

Libraries
---------

GTK+ is comprised of several separate libraries:

:program:`atk`
   Accessibility Toolkit, to enable use by disabled people.
:program:`gdk`
   GIMP Drawing Kit (XLib abstraction layer---windowing system dependent part).
:program:`gdk-pixbuf`
   Image loading and display.
:program:`glib`
   Basic datatypes and common algorithms.
:program:`gmodule`
   Dynamic module loader (:program:`libdl` portability wrapper).
:program:`gobject`
   Object/type system.
:program:`gtk`
   GIMP Tool Kit (windowing system independent part).
:program:`pango`
   Type layout and rendering.

When using :program:`libglade` another library is required:

:program:`glade`
   User Interface description loader/constructor.

Lastly, when using C++, some additional C++ libraries are also needed:

:program:`atkmm`
   C++ ATK wrapper.
:program:`gdkmm`
   C++ GDK wrapper.
:program:`gtkmm`
   C++ GTK+ wrapper.
:program:`glademm`
   C++ Glade wrapper.
:program:`pangomm`
   C++ Pango wrapper.
:program:`sigc++`
   Advanced C++ signalling and event handling (wraps GObject signals).

This looks quite intimidating!  However, there is no need to worry,
since compiling and linking programs is quite easy.  Since the
libraries are released together as a set, there are few library
interdependency issues.
