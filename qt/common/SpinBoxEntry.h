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

#ifndef SPINBOXENTRY_H
#define SPINBOXENTRY_H

#include <QtWidgets/QDoubleSpinBox>
#include <QtGui/QKeyEvent>

class SpinBoxEntry : public QDoubleSpinBox
{
  Q_OBJECT;
public:
  explicit SpinBoxEntry (QWidget *parent = 0);
  virtual ~SpinBoxEntry ();

protected:
  // Signal handler for key presses.
  void
  keyPressEvent (QKeyEvent *event);

signals:
  // Signal to be emitted when Enter is pressed.
  void
  enterPressed ();
};

#endif // SPINBOXENTRY_H

/*
 * Local Variables:
 * mode:C++
 * fill-column:60
 * End:
 */
