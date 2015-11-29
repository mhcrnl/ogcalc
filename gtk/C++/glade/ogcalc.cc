/* ogcalc - calculate %ABV and OG from PG, RI and CF.
 *
 * Copyright © 2003-2004  Roger Leigh <rleigh@codelibre.net>
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

#include <iomanip>
#include <sstream>

#include <sigc++/retype_return.h>

#include "ogcalc.h"

ogcalc::ogcalc()
{
  // Set the window title.
  set_title("OG & ABV Calculator");
  // Don't permit resizing.
  set_resizable(false);

  // Get the Glade user interface and add it to this window.
  xml_interface =
    Gnome::Glade::Xml::create("ogcalc.glade",
                              "ogcalc_main_vbox");
  Gtk::VBox *main_vbox;
  xml_interface->get_widget("ogcalc_main_vbox", main_vbox);
  add(*main_vbox);

  // Pull all of the widgets out of the Glade interface.
  xml_interface->get_widget("pg_entry", pg_entry);
  xml_interface->get_widget("ri_entry", ri_entry);
  xml_interface->get_widget("cf_entry", cf_entry);
  xml_interface->get_widget("og_result", og_result);
  xml_interface->get_widget("abv_result", abv_result);
  xml_interface->get_widget("quit_button", quit_button);
  xml_interface->get_widget("reset_button", reset_button);
  xml_interface->get_widget("calculate_button",
                            calculate_button);

  // Set up signal handers for buttons.
  quit_button->signal_clicked().connect
    ( sigc::mem_fun(*this, &ogcalc::hide) );
  reset_button->signal_clicked().connect
    ( sigc::mem_fun(*this, &ogcalc::on_button_clicked_reset) );
  reset_button->signal_clicked().connect
    ( sigc::mem_fun(*pg_entry, &Gtk::Widget::grab_focus) );
  calculate_button->signal_clicked().connect
    ( sigc::mem_fun(*this,
		    &ogcalc::on_button_clicked_calculate) );
  calculate_button->signal_clicked().connect
    ( sigc::mem_fun(*reset_button, &Gtk::Widget::grab_focus) );

  // Set up signal handlers for numeric entries.
  pg_entry->signal_activate().connect
    ( sigc::mem_fun(*ri_entry, &Gtk::Widget::grab_focus) );
  ri_entry->signal_activate().connect
    ( sigc::mem_fun(*cf_entry, &Gtk::Widget::grab_focus) );
  cf_entry->signal_activate().connect
    ( sigc::hide_return
      ( sigc::mem_fun(*this,
		      &Gtk::Window::activate_default) ) );

  // Ensure calculate is the default.  The Glade default was
  // lost since it was not packed in a window when set.
  calculate_button->grab_default();
}

ogcalc::~ogcalc()
{
}

void
ogcalc::on_button_clicked_calculate()
{
  // PG, RI, and CF values.
  double pg = pg_entry->get_value();
  double ri = ri_entry->get_value();
  double cf = cf_entry->get_value();

  // Calculate OG.
  double og = (ri * 2.597) - (pg * 1.644) - 34.4165 + cf;

  // Calculate ABV.
  double abv;
  if (og < 60)
    abv = (og - pg) * 0.130;
  else
    abv = (og - pg) * 0.134;

  std::ostringstream output;
  // Use the user's locale for this stream.
  output.imbue(std::locale(""));
  output << "<b>" << std::fixed << std::setprecision(2)
         << og << "</b>";
  og_result->set_markup(Glib::locale_to_utf8(output.str()));
  output.str("");
  output << "<b>" << std::fixed << std::setprecision(2)
         << abv << "</b>";
  abv_result->set_markup
    (Glib::locale_to_utf8(output.str()));
}

void
ogcalc::on_button_clicked_reset()
{
  pg_entry->set_value(0.0);
  ri_entry->set_value(0.0);
  cf_entry->set_value(0.0);
  og_result->set_text("");
  abv_result->set_text("");
}

// Local Variables:
// mode:C++
// fill-column:60
// End:
