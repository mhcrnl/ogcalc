Designing an application
========================

Planning ahead
--------------

Before starting to code, it is necessary to plan ahead by thinking
about what the program will do, and how it should do it.  When
designing a graphical interface, one should pay attention to *how* the
user will interact with it, to ensure that it is both easy to
understand and efficient to use.  In other words, to detail a clear,
simple specification for the application.

When designing an application, I personally find it useful to sketch
the interface on paper, before constructing it.  Interface designers
such as Glade are helpful here, but a pen and paper are more efficient
for the initial design.  The reason for this is that it's possible to
spend hours tinkering with the arrangement of containers (which we'll
come to shortly) and widgets, and fiddling with their properties,
rather than tackling the meat of the problem.  Working out the main
aspects of the user interface is the main focus here; getting it
implemented nicely is a separate job which is much quicker to do in a
single go once you've worked out exactly what it is you're doing and
how you're going to do it.

Introducing :program:`ogcalc`
-----------------------------

As part of the production (and quality control) processes in the
brewing industry, it is necessary to determine the alcohol content of
each batch at several stages during the brewing process.  One method
for doing this is to calulate it using the density (gravity) in
:math:`\mathrm{g}/\mathrm{cm}^3` and the refractive index of a sample.
A correction factor is used to align the calculated value with that
determined by distillation, which is the standard required by HM
Customs \& Excise, and gas chromatography.

Original gravity is the density during fermentation.  As alcohol is
produced during fermentation, the density falls.  Traditionally, this
would be similar to (if not the same as) the measured ("present")
gravity, but with modern high-gravity brewing (at a higher
concentration) it tends to be higher.  It is just as important that
the OG is within the set limits of the specification for the product
as the ABV.

The :program:`ogcalc` program performs the following calculation:

.. math::

   O = (R \times 2.597) - (P \times 1.644) - 34.4165 + C

If O is less than 60, then

.. math::

   A = (O - P) \times 0.130

otherwise

.. math::

   A = (O - P) \times 0.134

The symbols have the following meanings:

:math:`A`
   Percentage Alcohol By Volume
:math:`C`
   Correction Factor
:math:`O`
   Original Gravity
:math:`P`
   Present Gravity
:math:`R`
   Refractive Index

Because alcoholic beverages are only slightly denser than water, the
gravity value for the purpose of this calculation is the
:math:`(\mathrm{density} -1) \times 10000`.  That is, 1.0052 would be
converted to 52.


Designing the interface
-----------------------

The program needs to

* ask the user for the values :math:`C`, :math:`P`, and :math:`R`.
* perform the calculation
* display the calculated results, :math:`A` and :math:`O`.
* reset the interface to allow the process to be repeated
* have a facility for terminating the application

A simple sketch of an interface which may perform all these tasks is
shown in the Figure :ref:`Sketching a user interface <fig-sketch>`.

.. _fig-sketch:
.. figure:: figures/sketch.*
   :figwidth: 60%
   :width: 80%
   :align: center

   Sketching a user interface.  The :program:`ogcalc` main window is
   drawn simply, to illustrate its functionality.  The top row
   contains three numeric entry fields, followed by two result fields
   on the middle row.  The bottom row contains buttons to quit the
   program, reset the interface and do the calculation.

This interface contains three entry fields to allow the user to enter
the three values required.  Each is accompanied by a label to indicate
its purpose.  A full (non-abbreviated) description may also be added
in the form of tooltips (see later).  The calculate button will
trigger the calculation and display of results.  The results are shown
in the middle row, again with labels to describe what the results
are.  Finally, a reset button will clear the entry fields and results
from the previous calculation, allowing a new calculation to be
performed, and the quit button will terminate the application.

.. _fig-sketch-focus:
.. figure:: figures/sketch-focus.*
   :figwidth: 60%
   :width: 80%
   :align: center

   Sequence of focus changes when using the interface to perform a
   calculation.  Starting at the PG entry, the PG value is entered,
   followed by RI and CF, the calculate button is then pressed to
   display the result, and the result button clears the interface and
   resets the focus back to the PG entry for the next calculation.

One non-visible aspect of the user interface is how to navigate
between the different elements of the interface in order to make use
of the application as efficiently as possible.  It's typically
possible to make use of the Tab key to move between elements, and we
will support this method of working, but the application is also
intended to support fast, accurate and efficient entry using a
numerical keypad, so we want to move between the entry boxes when
Enter is pressed, allow the number to be typed without having to mess
around selecting and clearing the old value, and then do the
calculation, and then reset on repeated presses.  This sequence is
illustrated in the :ref:`Sequence of focus changes <fig-sketch-focus>`
figure.  It's very common for UI designers to focus primarily on the
appearance of the interface, but there's nothing worse than an
interface which is inefficient for the end user to suffer through
using as a result of it being awkward and frustrating to use, so it's
something which should be considered from the start.  In our case, the
application is going to be used in a busy laboratory where the users
may have multiple samples to perform the calculation for in a very
short timeframe.  They are also doing lots of other things at the same
time.  The last thing they want is an interface which might let them
accidentally mis-enter data, mis-read the results, or confuse
different samples.  The latter reason is why we will completely reset
the interface between calculations, and also why the entered numbers
are shown directly above the results--it's so you can easily
double-check what you've done against the recorded (written)
experimental data.  It's unfortunate that other toolkits, for example
Cocoa on MacOS X and TIFKAM on Windows have neglected this so that
their interfaces actually *require* a mouse for certain actions.  If
you care about your users, this is almost never an acceptable choice:
looks should not (and do not have to) compromise basic usability.

The next sections will look at how this very simple specification can
be turned into a real, working application.
