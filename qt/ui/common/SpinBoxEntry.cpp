/* ogcalc - calculate %ABV and OG from PG, RI and CF.
 *
 * Copyright © 2003-2013  Roger Leigh <rleigh@codelibre.net>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
 * MA 02139, USA.
 *
 **********************************************************/

#include "SpinBoxEntry.h"

SpinBoxEntry::SpinBoxEntry (QWidget *parent) :
  QDoubleSpinBox(parent)
{
}

SpinBoxEntry::~SpinBoxEntry ()
{
}

void
SpinBoxEntry::keyPressEvent (QKeyEvent *event)
{
  // If Enter or Return are pressed, emit the enterPressed
  // signal, or else defer to the parent class.
  switch(event->key())
    {
    case Qt::Key_Enter:
    case Qt::Key_Return:
      emit enterPressed();
      break;
    default:
      QDoubleSpinBox::keyPressEvent (event);
    }
}
