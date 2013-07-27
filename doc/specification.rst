Designing an application
========================

Planning ahead
--------------

Before starting to code, it is necessary to plan ahead by thinking
about what the program will do, and how it should do it.  When
designing a graphical interface, one should pay attention to
*how* the user will interact with it, to ensure that it is both
easy to understand and efficient to use.

When designing a GTK+ application, it is useful to sketch the
interface on paper, before constructing it.  Interface designers such
as Glade are helpful here, but a pen and paper are best for the
initial design.

Introducing :program:`ogcalc`
-----------------------------

As part of the production (and quality control) processes in the
brewing industry, it is necessary to determine the alcohol content of
each batch at several stages during the brewing process.  This is
calculated using the density (gravity) in
:math:`\mathrm{g}/\mathrm{cm}^3` and the refractive index.  A
correction factor is used to align the calculated value with that
determined by distillation, which is the standard required by HM
Customs \& Excise.  Because alcoholic beverages are only slightly
denser than water, the PG value is the :math:`(\mathrm{density} -1)
\times 10000`.  That is, 1.0052 would be entered as 52.

Original gravity is the density during fermentation.  As alcohol is
produced during fermentation, the density falls.  Traditionally, this
would be similar to the PG, but with modern high-gravity brewing (at a
higher concentration) it tends to be higher.  It is just as important
that the OG is within the set limits of the specification for the
product as the ABV.


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


Designing the interface
-----------------------

The program needs to ask the user for the values of :math:`C`,
:math:`P`, and :math:`R`.  It must then display the results, :math:`A`
and :math:`O`.

A simple sketch of the interface is shown in the Figure :ref:`Sketching a
user interface <fig-sketch>`.

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
