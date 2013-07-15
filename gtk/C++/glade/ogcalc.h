/* ogcalc - calculate %ABV and OG from PG, RI and CF.
 *
 * Copyright (C) 2003-2004  Roger Leigh <rleigh@debian.org>
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

#ifndef OGCALCMM_H
#define OGCALCMM_H

#include <gtkmm.h>
#include <libglademm.h>

class ogcalc : public Gtk::Window
{
public:
  ogcalc();
  virtual ~ogcalc();

protected:
  // Calculation signal handler.
  virtual void on_button_clicked_calculate();
  // Reset signal handler.
  virtual void on_button_clicked_reset();

  // The widgets that are manipulated.
  Gtk::SpinButton* pg_entry;
  Gtk::SpinButton* ri_entry;
  Gtk::SpinButton* cf_entry;
  Gtk::Label* og_result;
  Gtk::Label* abv_result;
  Gtk::Button* quit_button;
  Gtk::Button* reset_button;
  Gtk::Button* calculate_button;

  // Glade interface description.
  Glib::RefPtr<Gnome::Glade::Xml> xml_interface;
};

#endif // OGCALCMM_H

// Local Variables:
// mode:C++
// fill-column:60
// End:

