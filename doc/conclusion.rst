Conclusion
==========

Which method of programming one chooses is dependent on many different
factors, such as:

* The languages one is familiar with.
* The size and nature of the program to be written.
* The need for long-term maintainability.
* The need for code reuse.

For simple programs, such as :program:`gtk/C/plain/ogcalc`, there is no
problem with writing in plain C, but as programs become more complex,
Glade can greatly ease the effort needed to develop and maintain the
code.  The code reduction and de-uglification achieved through
conversion to Glade/:program:`libglade` is beneficial even for small
programs, however, so I would recommend that Glade be used for all but
the most trivial code.

The C++ code using Gtkmm is slightly more complex than the code using
Glade.  However, the benefits of type and signal safety, encapsulation
of complexity and the ability to re-use code through the derivation of
new widgets make Gtkmm and :program:`libglademm` an even better choice.
Although it is possible to write perfectly good code in C, Gtkmm gives
the programmer security through compiler type checking that plain GTK+
cannot offer.  In addition, improved code organisation is possible,
because inheritance allows encapsulation.

GObject provides similar facilities to C++ in terms of providing
classes, objects, inheritance, constructors and destructors etc., and
is certainly very capable (it is, after all, the basis of the whole of
GTK+!).  The code using GObject is very similar to the corresponding
C++ code in terms of its structure.  However, C++ still provides
facilities such as RAII (Resource Acquisition is Initialisation) and
automatic destruction when an object goes out of scope that C cannot
provide.

Depending on whether the speed and safety tradeoffs are acceptable,
Python may also be a valid choice.  While Python code is certainly
clearer and simpler, the speed of execution and lack of compile-time
type checking are a concern.

There is no "best solution" for all use cases.  Choose based on your
own requirements, preferences and capabilities.  In addition, Glade is
not the solution for every problem.  The author typically uses a
mixture of custom widgets and Glade interfaces (and your custom
widgets can *contain* Glade interfaces!).  Really dynamic interfaces
must be coded by hand, since Glade interfaces are not sufficiently
flexible.  Use what is best for each situation.
