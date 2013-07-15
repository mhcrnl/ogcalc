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

#include <iomanip>
#include <sstream>

#include <sigc++/retype_return.h> // Broken sigc++ header?

#include "ogcalc.h"

ogcalc::ogcalc()
{
  // Set the window title.
  set_title("OG & ABV Calculator");
  // Don't permit resizing.
  set_resizable(false);

  // Create a Gtk::VBox to hold the other widgets.  This
  // contains other widgets, which are packed in to it
  // vertically.
  Gtk::VBox *vbox1 = manage (new Gtk::VBox(false, 0));
  // Add the VBox to the Window.
  add (*vbox1);
  // Display the Vbox.  At this point, the Window has not
  // yet been displayed, so the window isn't yet visible.
  vbox1->show();

  // Create a second Gtk::VBox.  Unlike the previous VBox,
  // the widgets it will contain will be of uniform size and
  // separated by a 5 pixel gap.
  Gtk::VBox *vbox2 = manage (new Gtk::VBox(true, 5));
  // Set a 10 pixel border width.
  vbox2->set_border_width(10);
  // Add this VBox to our first VBox.
  vbox1->pack_start(*vbox2, false, false, 0);
  vbox2->show();

  // Create a Gtk::HBox.  This is identical to a GtkVBox
  // except that the widgets pack horizontally, instead of
  // vertically.
  Gtk::HBox *hbox1 = manage (new Gtk::HBox(false, 10));
  // Add to vbox2.  The function's other arguments mean to
  // expand into any extra space alloted to it, to fill the
  // extra space and to add 0 pixels of padding between it
  // and its neighbour.
  vbox2->pack_start(*hbox1, true, true, 0);
  hbox1->show();

  // Create a Tooltip for later use.
  Gtk::Tooltips *tooltip = manage (new Gtk::Tooltips);

  {
    // A second Gtk::HBox to pack into the first.  This is
    // purely aesthetic--to get nice border spacing.
    Gtk::HBox *hbox2 = manage (new Gtk::HBox(false, 5));
    hbox1->pack_start(*hbox2, true, true, 0);
    hbox2->show();

    // An eventbox.  This widget is just a container for
    // widgets (like labels) that don't have an associated X
    // window, and so can't receive X events.  This is just
    // used to we can add tooltips to each label.
    Gtk::EventBox *eventbox = manage (new Gtk::EventBox);
    eventbox->show();
    hbox2->pack_start(*eventbox, false, false, 0);
    // Create a label.
    Gtk::Label *label = manage (new Gtk::Label("PG:"));
    // Add the label to the eventbox.
    eventbox->add(*label);
    label->show();

    // A Gtk::Adjustment is used to hold a numeric value:
    // the initial value, minimum and maximum values, "step"
    // and "page" increments and the "page size".  It's used
    // by spin buttons, scrollbars, sliders etc..
    Gtk::Adjustment *adjustment =
      manage (new Gtk::Adjustment(0.0, 0.0, 10000.0,
				  0.01, 1.0, 0));
    // Create a Gtk::SpinButton and associate it with the
    // adjustment. It adds/substracts 0.5 when the spin
    // buttons are used, and has 2 d.p. accuracy.
    pg_entry =
      manage (new Gtk::SpinButton(*adjustment, 0.5, 2));
    // Only numbers can be entered.
    pg_entry->set_numeric();
    hbox2->pack_start(*pg_entry, true, true, 0);
    pg_entry->show();

    // Create a tooltip and add it to the EventBox
    // previously created.
    tooltip->set_tip(*eventbox,
		     "Present Gravity (density)");
  }

  // Repeat the above for the next spin button.
  {
    Gtk::HBox *hbox2 = manage (new Gtk::HBox(false, 5));
    hbox1->pack_start(*hbox2, true, true, 0);
    hbox2->show();

    Gtk::EventBox *eventbox = manage (new Gtk::EventBox);
    eventbox->show();
    hbox2->pack_start(*eventbox, false, false, 0);
    Gtk::Label *label = manage (new Gtk::Label("RI:"));
    eventbox->add(*label);
    label->show();

    Gtk::Adjustment *adjustment =
      manage (new Gtk::Adjustment(0.0, 0.0, 10000.0,
				  0.01, 1.0, 0));
    ri_entry =
      manage (new Gtk::SpinButton(*adjustment, 0.5, 2));
    ri_entry->set_numeric();
    hbox2->pack_start(*ri_entry, true, true, 0);
    ri_entry->show();

    tooltip->set_tip(*eventbox,
		     "Refractive Index");
  }

  // Repeat again for the last spin button.
  {
    Gtk::HBox *hbox2 = manage (new Gtk::HBox(false, 5));
    hbox1->pack_start(*hbox2, true, true, 0);
    hbox2->show();

    Gtk::EventBox *eventbox = manage (new Gtk::EventBox);
    eventbox->show();
    hbox2->pack_start(*eventbox, false, false, 0);
    Gtk::Label *label = manage (new Gtk::Label("CF:"));
    eventbox->add(*label);
    label->show();

    Gtk::Adjustment *adjustment =
      manage (new Gtk::Adjustment(0.0, -50.0, 50.0,
				   0.1, 1.0, 0));
    cf_entry =
      manage (new Gtk::SpinButton(*adjustment, 0.2, 1));
    cf_entry->set_numeric();
    hbox2->pack_start(*cf_entry, true, true, 0);
    cf_entry->show();

    tooltip->set_tip(*eventbox,
		     "Correction Factor");
  }

  // Now we move to the second "row" of the interface, for
  // displaying the results.

  // Firstly, a new Gtk::HBox to pack the labels into.
  hbox1 = manage (new Gtk::HBox (true, 10));
  vbox2->pack_start(*hbox1, true, true, 0);
  hbox1->show();

  {
    // A second Gtk::HBox to pack into the first.  This is
    // purely aesthetic--to get nice border spacing.
    Gtk::HBox *hbox2 = manage (new Gtk::HBox(false, 5));
    hbox1->pack_start(*hbox2, true, true, 0);
    hbox2->show();

    // As before, a label in an event box with a tooltip.
    Gtk::EventBox *eventbox = manage (new Gtk::EventBox);
    eventbox->show();
    hbox2->pack_start(*eventbox, false, false, 0);
    Gtk::Label *label = manage (new Gtk::Label("OG:"));
    eventbox->add(*label);
    label->show();

    // This is a label, used to display the OG result.
    og_result = manage (new Gtk::Label);
    // Because it's a result, it is set "selectable", to
    // allow pasting of the result, but it's not modifiable.
    og_result->set_selectable();
    hbox2->pack_start(*og_result, true, true, 0);
    og_result->show();

    // Add the tooltip to the event box.
    tooltip->set_tip(*eventbox, "Original Gravity (density)");
  }

  // Repeat as above for the second result value.
  {
    Gtk::HBox *hbox2 = manage (new Gtk::HBox(false, 5));
    hbox1->pack_start(*hbox2, true, true, 0);
    hbox2->show();

    Gtk::EventBox *eventbox = manage (new Gtk::EventBox);
    eventbox->show();
    hbox2->pack_start(*eventbox, false, false, 0);
    Gtk::Label *label = manage (new Gtk::Label("ABV %:"));
    eventbox->add(*label);
    label->show();

    abv_result = manage (new Gtk::Label);
    abv_result->set_selectable();
    hbox2->pack_start(*abv_result, true, true, 0);
    abv_result->show();

    tooltip->set_tip(*eventbox, "Percent Alcohol By Volume");
  }

  // Create a horizontal separator (Gtk::HSeparator) and add
  // it to the VBox.
  Gtk::HSeparator *hsep = manage (new Gtk::HSeparator);
  vbox1->pack_start(*hsep, false, false, 0);
  hsep->show();

  // Create a Gtk::HBox to hold the bottom row of buttons.
  {
    Gtk::HBox *hbox1 = manage (new Gtk::HBox(true, 5));
    hbox1->set_border_width(10);
    vbox1->pack_start(*hbox1, true, true, 0);
    hbox1->show();

    // Create the "Quit" button.  We use a "stock"
    // button--commonly-used buttons that have a set title
    // and icon.
    quit_button = manage (new Gtk::Button(Gtk::Stock::QUIT));
    hbox1->pack_start(*quit_button, true, true, 0);
    quit_button->show();

    // This button resets the interface.
    reset_button = manage (new Gtk::Button("_Reset", true));
    reset_button->set_flags(Gtk::CAN_DEFAULT);
    hbox1->pack_start(*reset_button);
    reset_button->show();

    // The final button is the Calculate button.
    calculate_button = manage (new Gtk::Button("_Calculate", true));
    calculate_button->set_flags(Gtk::CAN_DEFAULT);
    hbox1->pack_start(*calculate_button);
    calculate_button->show();
  }

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

  // Ensure calculate is the default.
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
