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

#include <gtk/gtk.h>

GtkWidget *
create_spin_entry( const gchar    *label_text,
                   const gchar    *tooltip_text,
                   GtkWidget     **spinbutton_pointer,
                   GtkAdjustment  *adjustment,
                   guint           digits );
GtkWidget *
create_result_label(const gchar   *label_text,
                    const gchar   *tooltip_text,
                    GtkWidget    **result_label_pointer );
void on_button_clicked_reset( GtkWidget *widget,
                              gpointer   data );
void on_button_clicked_calculate( GtkWidget *widget,
                                  gpointer   data );

/* This structure holds all of the widgets needed to get all
   the values for the calculation. */
struct calculation_widgets
{
  GtkWidget *pg_val;     /* PG entry widget */
  GtkWidget *ri_val;     /* RI entry widget */
  GtkWidget *cf_val;     /* CF entry widget */
  GtkWidget *og_result;  /* OG result label */
  GtkWidget *abv_result; /* ABV% result label */
};

/* The bulk of the program.  This is nearly all setting up
   of the user interface.  If Glade and libglade were used,
   this would be under 10 lines only! */
int main(int argc, char *argv[])
{
  /* These are pointers to widgets used in constructing the
     interface, and later used by signal handlers. */
  GtkWidget                  *window;
  GtkWidget                  *vbox1,   *vbox2;
  GtkWidget                  *hbox1,   *hbox2;
  GtkWidget                  *quit, *reset, *calculate;
  GtkObject                  *adjustment;
  GtkWidget                  *hsep;
  struct calculation_widgets  cb_widgets;

  /* Initialise GTK+. */
  gtk_init(&argc, &argv);

  /* Create a new top-level window. */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  /* Set the window title. */
  gtk_window_set_title (GTK_WINDOW(window),
                        "OG & ABV Calculator");
  /* Disable window resizing, since there's no point in this
     case. */
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  /* Connect the window close button ("destroy" event) to
     gtk_main_quit(). */
  g_signal_connect (G_OBJECT(window),
                    "destroy",
                    gtk_main_quit, NULL);

  /* Create a GtkVBox to hold the other widgets.  This
     contains other widgets, which are packed in to it
     vertically. */
  vbox1 = gtk_vbox_new (FALSE, 0);
  /* Add the VBox to the Window.  A GtkWindow /is a/
     GtkContainer which /is a/ GtkWidget.  GTK_CONTAINER
     casts the GtkWidget to a GtkContainer, like a C++
     dynamic_cast. */
  gtk_container_add (GTK_CONTAINER(window), vbox1);
  /* Display the VBox.  At this point, the Window has not
     yet been displayed, so the window isn't yet visible. */
  gtk_widget_show(vbox1);

  /* Create a second GtkVBox.  Unlike the previous VBox, the
     widgets it will contain will be of uniform size and
     separated by a 5 pixel gap. */
  vbox2 = gtk_vbox_new (TRUE, 5);
  /* Set a 10 pixel border width. */
  gtk_container_set_border_width(GTK_CONTAINER(vbox2), 10);
  /* Add this VBox to our first VBox. */
  gtk_box_pack_start (GTK_BOX(vbox1), vbox2,
                      FALSE, FALSE, 0);
  gtk_widget_show(vbox2);

  /* Create a GtkHBox.  This is identical to a GtkVBox
     except that the widgets pack horizontally instead of
     vertically. */
  hbox1 = gtk_hbox_new (FALSE, 10);

  /* Add to vbox2.  The function's other arguments mean to
     expand into any extra space alloted to it, to fill the
     extra space and to add 0 pixels of padding between it
     and its neighbour. */
  gtk_box_pack_start (GTK_BOX(vbox2), hbox1, TRUE, TRUE, 0);
  gtk_widget_show (hbox1);


  /* A GtkAdjustment is used to hold a numeric value: the
     initial value, minimum and maximum values, "step" and
     "page" increments and the "page size".  It's used by
     spin buttons, scrollbars, sliders etc.. */
  adjustment = gtk_adjustment_new (0.0, 0.0, 10000.0,
                                   0.01, 1.0, 0);
  /* Call a helper function to create a GtkSpinButton entry
     together with a label and a tooltip.  The spin button
     is stored in the cb_widgets.pg_val pointer for later
     use. We also specify the adjustment to use and the
     number of decimal places to allow. */
  hbox2 = create_spin_entry("PG:",
                            "Present Gravity (density)",
                            &cb_widgets.pg_val,
                            GTK_ADJUSTMENT (adjustment), 2);
  /* Pack the returned GtkHBox into the interface. */
  gtk_box_pack_start(GTK_BOX(hbox1), hbox2, TRUE, TRUE, 0);
  gtk_widget_show(hbox2);

  /* Repeat the above for the next spin button. */
  adjustment = gtk_adjustment_new (0.0, 0.0, 10000.0,
                                   0.01, 1.0, 0);
  hbox2 = create_spin_entry("RI:",
                            "Refractive Index",
                            &cb_widgets.ri_val,
                            GTK_ADJUSTMENT (adjustment), 2);
  gtk_box_pack_start(GTK_BOX(hbox1), hbox2, TRUE, TRUE, 0);
  gtk_widget_show(hbox2);

  /* Repeat again for the last spin button. */
  adjustment = gtk_adjustment_new (0.0, -50.0, 50.0,
                                   0.1, 1.0, 0);
  hbox2 = create_spin_entry("CF:",
                            "Correction Factor",
                            &cb_widgets.cf_val,
                            GTK_ADJUSTMENT (adjustment), 1);
  gtk_box_pack_start(GTK_BOX(hbox1), hbox2, TRUE, TRUE, 0);
  gtk_widget_show(hbox2);

  /* Now we move to the second "row" of the interface, used
     to display the results. */

  /* Firstly, a new GtkHBox to pack the labels into. */
  hbox1 = gtk_hbox_new (TRUE, 10);
  gtk_box_pack_start (GTK_BOX(vbox2), hbox1, TRUE, TRUE, 0);
  gtk_widget_show (hbox1);

  /* Create the OG result label, then pack and display. */
  hbox2 = create_result_label("OG:",
                              "Original Gravity (density)",
                              &cb_widgets.og_result);

  gtk_box_pack_start(GTK_BOX(hbox1), hbox2, TRUE, TRUE, 0);
  gtk_widget_show(hbox2);

  /* Repeat as above for the second result value. */
  hbox2 = create_result_label("ABV %:",
                              "Percent Alcohol By Volume",
                              &cb_widgets.abv_result);
  gtk_box_pack_start(GTK_BOX(hbox1), hbox2, TRUE, TRUE, 0);
  gtk_widget_show(hbox2);

  /* Create a horizontal separator (GtkHSeparator) and add
     it to the VBox. */
  hsep = gtk_hseparator_new();
  gtk_box_pack_start(GTK_BOX(vbox1), hsep, FALSE, FALSE, 0);
  gtk_widget_show(hsep);

  /* Create a GtkHBox to hold the bottom row of buttons. */
  hbox1 = gtk_hbox_new(TRUE, 5);
  gtk_container_set_border_width(GTK_CONTAINER(hbox1), 10);
  gtk_box_pack_start(GTK_BOX(vbox1), hbox1, TRUE, TRUE, 0);
  gtk_widget_show(hbox1);

  /* Create the "Quit" button.  We use a "stock"
     button--commonly-used buttons that have a set title and
     icon. */
  quit = gtk_button_new_from_stock(GTK_STOCK_QUIT);
  /* We connect the "clicked" signal to the gtk_main_quit()
     callback which will end the program. */
  g_signal_connect (G_OBJECT (quit), "clicked",
                    gtk_main_quit, NULL);
  gtk_box_pack_start(GTK_BOX(hbox1), quit,
                     TRUE, TRUE, 0);
  gtk_widget_show(quit);

  /* This button resets the interface. */
  reset = gtk_button_new_with_mnemonic("_Reset");
  /* The "clicked" signal is connected to the
     on_button_clicked_reset() callback above, and our
     "cb_widgets" widget list is passed as the second
     argument, cast to a gpointer (void *). */
  g_signal_connect (G_OBJECT (reset), "clicked",
                    G_CALLBACK(on_button_clicked_reset),
                    (gpointer) &cb_widgets);
  /* g_signal_connect_swapped is used to connect a signal
     from one widget to the handler of another.  The last
     argument is the widget that will be passed as the first
     argument of the callback.  This causes
     gtk_widget_grab_focus to switch the focus to the PG
     entry. */
  g_signal_connect_swapped
    (G_OBJECT (reset),
     "clicked",
     G_CALLBACK (gtk_widget_grab_focus),
     (gpointer)GTK_WIDGET(cb_widgets.pg_val));
  /* This lets the default action (Enter) activate this
     widget even when the focus is elsewhere.  This doesn't
     set the default, it just makes it possible to set.*/
  GTK_WIDGET_SET_FLAGS (reset, GTK_CAN_DEFAULT);
  gtk_box_pack_start(GTK_BOX(hbox1), reset,
                     TRUE, TRUE, 0);
  gtk_widget_show(reset);

  /* The final button is the Calculate button. */
  calculate = gtk_button_new_with_mnemonic("_Calculate");
  /* When the button is clicked, call the
     on_button_clicked_calculate() function.  This is the
     same as for the Reset button. */
  g_signal_connect (G_OBJECT (calculate), "clicked",
                    G_CALLBACK(on_button_clicked_calculate),
                    (gpointer) &cb_widgets);
  /* Switch the focus to the Reset button when the button is
     clicked. */
  g_signal_connect_swapped
    (G_OBJECT (calculate),
     "clicked",
     G_CALLBACK (gtk_widget_grab_focus),
     (gpointer)GTK_WIDGET(reset));
  /* As before, the button can be the default. */
  GTK_WIDGET_SET_FLAGS (calculate, GTK_CAN_DEFAULT);
  gtk_box_pack_start(GTK_BOX(hbox1), calculate,
                     TRUE, TRUE, 0);
  /* Make this button the default.  Note the thicker border
     in the interface--this button is activated if you press
     enter in the CF entry field. */
  gtk_widget_grab_default (calculate);
  gtk_widget_show(calculate);

  /* Set up data entry focus movement.  This makes the
     interface work correctly with the keyboard, so that you
     can touch-type through the interface with no mouse
     usage or tabbing between the fields. */

  /* When Enter is pressed in the PG entry box, focus is
     transferred to the RI entry. */
  g_signal_connect_swapped
    (G_OBJECT (cb_widgets.pg_val),
     "activate",
     G_CALLBACK (gtk_widget_grab_focus),
     (gpointer) GTK_WIDGET(cb_widgets.ri_val));
  /* RI -> CF. */
  g_signal_connect_swapped
    (G_OBJECT (cb_widgets.ri_val),
     "activate",
     G_CALLBACK (gtk_widget_grab_focus),
     (gpointer) GTK_WIDGET(cb_widgets.cf_val));
  /* When Enter is pressed in the RI field, it activates the
     Calculate button. */
  g_signal_connect_swapped
    (G_OBJECT (cb_widgets.cf_val),
     "activate",
     G_CALLBACK (gtk_window_activate_default),
     (gpointer) GTK_WIDGET(window));

  /* The interface is complete, so finally we show the
     top-level window.  This is done last or else the user
     might see the interface drawing itself during the short
     time it takes to construct.  It's nicer this way. */
  gtk_widget_show (window);

  /* Enter the GTK Event Loop.  This is where all the events
     are caught and handled.  It is exited with
     gtk_main_quit(). */
  gtk_main();

  return 0;
}

/* A utility function for UI construction.  It constructs
   part of the widget tree, then returns its root. */
GtkWidget *
create_spin_entry( const gchar    *label_text,
                   const gchar    *tooltip_text,
                   GtkWidget     **spinbutton_pointer,
                   GtkAdjustment  *adjustment,
                   guint           digits )
{
  GtkWidget   *hbox;
  GtkWidget   *eventbox;
  GtkWidget   *spinbutton;
  GtkWidget   *label;
  GtkTooltips *tooltip;

  /* A GtkHBox to pack the entry child widgets into. */
  hbox = gtk_hbox_new(FALSE, 5);

  /* An eventbox.  This widget is just a container for
     widgets (like labels) that don't have an associated X
     window, and so can't receive X events.  This is just
     used to we can add tooltips to each label. */
  eventbox = gtk_event_box_new();
  gtk_widget_show(eventbox);
  gtk_box_pack_start (GTK_BOX(hbox), eventbox,
                      FALSE, FALSE, 0);
  /* Create a label. */
  label = gtk_label_new(label_text);
  /* Add the label to the eventbox. */
  gtk_container_add(GTK_CONTAINER(eventbox), label);
  gtk_widget_show(label);

  /* Create a GtkSpinButton and associate it with the
     adjustment. It adds/substracts 0.5 when the spin
     buttons are used, and has digits accuracy. */
  spinbutton =
    gtk_spin_button_new (adjustment, 0.5, digits);
  /* Only numbers can be entered. */
  gtk_spin_button_set_numeric
    (GTK_SPIN_BUTTON(spinbutton), TRUE);
  gtk_box_pack_start(GTK_BOX(hbox), spinbutton,
                     TRUE, TRUE, 0);
  gtk_widget_show(spinbutton);

  /* Create a tooltip and add it to the EventBox previously
     created. */
  tooltip = gtk_tooltips_new();
  gtk_tooltips_set_tip(tooltip, eventbox,
                       tooltip_text, NULL);

  *spinbutton_pointer = spinbutton;
  return hbox;
}

/* A utility function for UI construction.  It constructs
   part of the widget tree, then returns its root. */
GtkWidget *
create_result_label(const gchar   *label_text,
                    const gchar   *tooltip_text,
                    GtkWidget    **result_label_pointer )
{
  GtkWidget   *hbox;
  GtkWidget   *eventbox;
  GtkWidget   *result_label;
  GtkWidget   *result_value;
  GtkTooltips *tooltip;

  /* A GtkHBox to pack the entry child widgets into. */
  hbox = gtk_hbox_new(FALSE, 5);

  /* As before, a label in an event box with a tooltip. */
  eventbox = gtk_event_box_new();
  gtk_widget_show(eventbox);
  gtk_box_pack_start (GTK_BOX(hbox), eventbox,
                      FALSE, FALSE, 0);
  result_label = gtk_label_new(label_text);
  gtk_container_add(GTK_CONTAINER(eventbox), result_label);
  gtk_widget_show(result_label);

  /* This is a label, used to display the OG result. */
  result_value = gtk_label_new (NULL);
  /* Because it's a result, it is set "selectable", to allow
     copy/paste of the result, but it's not modifiable. */
  gtk_label_set_selectable (GTK_LABEL(result_value), TRUE);
  gtk_box_pack_start (GTK_BOX(hbox), result_value,
                      TRUE, TRUE, 0);
  gtk_widget_show(result_value);

  /* Add the tooltip to the event box. */
  tooltip = gtk_tooltips_new();
  gtk_tooltips_set_tip(tooltip, eventbox,
                       tooltip_text, NULL);

  *result_label_pointer = result_value;
  return hbox;
}

/* This is a callback function.  It resets the values of the
   entry widgets, and clears the results.  "data" is the
   calculation_widgets structure, which needs casting back
   to its correct type from a gpointer (void *) type. */
void on_button_clicked_reset( GtkWidget *widget,
                              gpointer   data )
{
  /* Widgets to manipulate. */
  struct calculation_widgets *w;

  w = (struct calculation_widgets *) data;

  gtk_spin_button_set_value (GTK_SPIN_BUTTON(w->pg_val),
                             0.0);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON(w->ri_val),
                             0.0);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON(w->cf_val),
                             0.0);
  gtk_label_set_text (GTK_LABEL(w->og_result), "");
  gtk_label_set_text (GTK_LABEL(w->abv_result), "");
}

/* This callback does the actual calculation.  Its arguments
   are the same as for on_button_clicked_reset(). */
void on_button_clicked_calculate( GtkWidget *widget,
                                  gpointer   data )
{
  gdouble                     pg, ri, cf, og, abv;
  gchar                      *og_string;
  gchar                      *abv_string;
  struct calculation_widgets *w;

  w = (struct calculation_widgets *) data;

  /* Get the numerical values from the entry widgets. */
  pg = gtk_spin_button_get_value
    (GTK_SPIN_BUTTON(w->pg_val));
  ri = gtk_spin_button_get_value
    (GTK_SPIN_BUTTON(w->ri_val));
  cf = gtk_spin_button_get_value
    (GTK_SPIN_BUTTON(w->cf_val));

  /* Do the sums. */
  og = (ri * 2.597) - (pg * 1.644) - 34.4165 + cf;

  if (og < 60)
    abv = (og - pg) * 0.130;
  else
    abv = (og - pg) * 0.134;

  /* Display the results.  Note the <b></b> GMarkup tags to
     make it display in boldface. */
  og_string = g_strdup_printf ("<b>%0.2f</b>", og);
  abv_string = g_strdup_printf ("<b>%0.2f</b>", abv);

  gtk_label_set_markup (GTK_LABEL(w->og_result),
                        og_string);
  gtk_label_set_markup (GTK_LABEL(w->abv_result),
                        abv_string);

  g_free (og_string);
  g_free (abv_string);
}

/*
 * Local Variables:
 * mode:C
 * fill-column:60
 * End:
 */
