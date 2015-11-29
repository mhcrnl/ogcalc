/* ogcalc - calculate %ABV and OG from PG, RI and CF.
 *
 * Copyright © 2004  Roger Leigh <rleigh@codelibre.net>
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

#include "ogcalc.h"

/* Declare class and instance initialisation functions and
   an ogcalc_get_type function to get the GType of Ogcalc.
   This has the side effect of registering Ogcalc as a new
   GType if it has not already been registered. */
G_DEFINE_TYPE(Ogcalc, ogcalc, GTK_TYPE_WINDOW);

GtkWidget *
_ogcalc_create_spin_entry( const gchar    *label_text,
			   const gchar    *tooltip_text,
			   GtkSpinButton **spinbutton_pointer,
			   GtkAdjustment  *adjustment,
			   guint           digits );
GtkWidget *
_ogcalc_create_result_label(const gchar   *label_text,
			    const gchar   *tooltip_text,
			    GtkLabel     **result_label_pointer );

static void
ogcalc_finalize( Ogcalc *self );

/* This is the class initialisation function.  It has no
   comparable C++ equivalent, since this is done by the
   compliler. */
static void
ogcalc_class_init ( OgcalcClass *klass )
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  /* Override the virtual finalize method in the GObject
     class vtable (which is contained in OgcalcClass). */
  gobject_class->finalize = (GObjectFinalizeFunc) ogcalc_finalize;
}

/* This is the object initialisation function.  It is
   comparable to a C++ constructor.  Note the similarity
   between "self" and the C++ "this" pointer. */
static void
ogcalc_init( Ogcalc *self )
{
  /* Set the window title */
  gtk_window_set_title(GTK_WINDOW (self),
                       "OG & ABV Calculator");
  /* Don't permit resizing */
  gtk_window_set_resizable(GTK_WINDOW (self), FALSE);

  /* Connect the window close button ("destroy-event") to
     a callback. */
  g_signal_connect(G_OBJECT (self), "delete-event",
                   G_CALLBACK (ogcalc_on_delete_event),
                   NULL);

  GtkWidget                  *vbox1,   *vbox2;
  GtkWidget                  *hbox1,   *hbox2;
  GtkObject                  *adjustment;
  GtkWidget                  *hsep;

  /* Create a GtkVBox to hold the other widgets.  This
     contains other widgets, which are packed in to it
     vertically. */
  vbox1 = gtk_vbox_new (FALSE, 0);
  /* Add the VBox to the Window.  A GtkWindow /is a/
     GtkContainer which /is a/ GtkWidget.  GTK_CONTAINER
     casts the GtkWidget to a GtkContainer, like a C++
     dynamic_cast. */
  gtk_container_add (GTK_CONTAINER(self), vbox1);
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
  hbox2 = _ogcalc_create_spin_entry("PG:",
				    "Present Gravity (density)",
				    &self->pg_val,
				    GTK_ADJUSTMENT (adjustment), 2);
  /* Pack the returned GtkHBox into the interface. */
  gtk_box_pack_start(GTK_BOX(hbox1), hbox2, TRUE, TRUE, 0);
  gtk_widget_show(hbox2);

  /* Repeat the above for the next spin button. */
  adjustment = gtk_adjustment_new (0.0, 0.0, 10000.0,
                                   0.01, 1.0, 0);
  hbox2 = _ogcalc_create_spin_entry("RI:",
				    "Refractive Index",
				    &self->ri_val,
				    GTK_ADJUSTMENT (adjustment), 2);
  gtk_box_pack_start(GTK_BOX(hbox1), hbox2, TRUE, TRUE, 0);
  gtk_widget_show(hbox2);

  /* Repeat again for the last spin button. */
  adjustment = gtk_adjustment_new (0.0, -50.0, 50.0,
                                   0.1, 1.0, 0);
  hbox2 = _ogcalc_create_spin_entry("CF:",
				    "Correction Factor",
				    &self->cf_val,
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
  hbox2 = _ogcalc_create_result_label("OG:",
				      "Original Gravity (density)",
				      &self->og_result);

  gtk_box_pack_start(GTK_BOX(hbox1), hbox2, TRUE, TRUE, 0);
  gtk_widget_show(hbox2);

  /* Repeat as above for the second result value. */
  hbox2 = _ogcalc_create_result_label("ABV %:",
				      "Percent Alcohol By Volume",
				      &self->abv_result);
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
  self->quit_button = GTK_BUTTON(gtk_button_new_from_stock(GTK_STOCK_QUIT));
  gtk_box_pack_start(GTK_BOX(hbox1), GTK_WIDGET(self->quit_button),
                     TRUE, TRUE, 0);
  gtk_widget_show(GTK_WIDGET(self->quit_button));

  /* This button resets the interface. */
  self->reset_button = GTK_BUTTON(gtk_button_new_with_mnemonic("_Reset"));
  /* g_signal_connect_swapped is used to connect a signal
     from one widget to the handler of another.  The last
     argument is the widget that will be passed as the first
     argument of the callback.  This causes
     gtk_widget_grab_focus to switch the focus to the PG
     entry. */
  g_signal_connect_swapped
    (G_OBJECT (self->reset_button),
     "clicked",
     G_CALLBACK (gtk_widget_grab_focus),
     (gpointer)GTK_WIDGET(self->pg_val));
  /* This lets the default action (Enter) activate this
     widget even when the focus is elsewhere.  This doesn't
     set the default, it just makes it possible to set.*/
  GTK_WIDGET_SET_FLAGS (self->reset_button, GTK_CAN_DEFAULT);
  gtk_box_pack_start(GTK_BOX(hbox1), GTK_WIDGET(self->reset_button),
                     TRUE, TRUE, 0);
  gtk_widget_show(GTK_WIDGET(self->reset_button));

  /* The final button is the Calculate button. */
  self->calculate_button = GTK_BUTTON(gtk_button_new_with_mnemonic("_Calculate"));
  /* Switch the focus to the Reset button when the button is
     clicked. */
  g_signal_connect_swapped
    (G_OBJECT (self->calculate_button),
     "clicked",
     G_CALLBACK (gtk_widget_grab_focus),
     (gpointer)GTK_WIDGET(self->reset_button));
  /* As before, the button can be the default. */
  GTK_WIDGET_SET_FLAGS (self->calculate_button, GTK_CAN_DEFAULT);
  gtk_box_pack_start(GTK_BOX(hbox1), GTK_WIDGET(self->calculate_button),
                     TRUE, TRUE, 0);
  /* Make this button the default.  Note the thicker border
     in the interface--this button is activated if you press
     enter in the CF entry field. */
  gtk_widget_grab_default (GTK_WIDGET(self->calculate_button));
  gtk_widget_show(GTK_WIDGET(self->calculate_button));

  /* Set up data entry focus movement.  This makes the
     interface work correctly with the keyboard, so that you
     can touch-type through the interface with no mouse
     usage or tabbing between the fields. */

  /* When Enter is pressed in the PG entry box, focus is
     transferred to the RI entry. */
  g_signal_connect_swapped
    (G_OBJECT (self->pg_val),
     "activate",
     G_CALLBACK (gtk_widget_grab_focus),
     (gpointer) self->ri_val);
  /* RI -> CF. */
  g_signal_connect_swapped
    (G_OBJECT (self->ri_val),
     "activate",
     G_CALLBACK (gtk_widget_grab_focus),
     (gpointer) self->cf_val);
  /* When Enter is pressed in the CF field, it activates the
     Calculate button. */
  g_signal_connect_swapped
    (G_OBJECT (self->cf_val), "activate",
     G_CALLBACK (gtk_window_activate_default),
     (gpointer) self);

  g_signal_connect_swapped
    (G_OBJECT (self->calculate_button), "clicked",
     G_CALLBACK (ogcalc_calculate),
     (gpointer) self);

  g_signal_connect_swapped
    (G_OBJECT (self->reset_button), "clicked",
     G_CALLBACK (ogcalc_reset),
     (gpointer) self);

  g_signal_connect_swapped
    (G_OBJECT (self->quit_button), "clicked",
     G_CALLBACK (gtk_widget_hide),
     (gpointer) self);

  /* Ensure calculate is the default.  The Glade default was
   * lost since it wasn't in a window when the default was
   * set. */
  gtk_widget_grab_default
    (GTK_WIDGET (self->calculate_button));

  ogcalc_reset(self, NULL);
}

/* This is the object initialisation function.  It is
   comparable to a C++ destructor.  Note the similarity
   between "self" and the C++ "this" pointer. */
static void
ogcalc_finalize (Ogcalc *self)
{
}

/* Create a new instance of the Ogcalc class (i.e. an
 * object) and pass it back by reference. */
Ogcalc *
ogcalc_new (void)
{
  return (Ogcalc *) g_object_new (OGCALC_TYPE, NULL);
}

/*
 * This function is called when the window is about to be
 * destroyed (e.g. if the close button on the window was
 * clicked).  It is not a destructor.
 */
gboolean
ogcalc_on_delete_event(Ogcalc   *ogcalc,
                       GdkEvent *event,
                       gpointer  user_data)
{
  gtk_widget_hide(GTK_WIDGET (ogcalc));
  /* We return true because the object should not be
     automatically destroyed. */
  return TRUE;
}

/* A utility function for UI construction.  It constructs
   part of the widget tree, then returns its root. */
GtkWidget *
_ogcalc_create_spin_entry( const gchar    *label_text,
			   const gchar    *tooltip_text,
			   GtkSpinButton **spinbutton_pointer,
			   GtkAdjustment  *adjustment,
			   guint           digits )
{
  GtkWidget     *hbox;
  GtkWidget     *eventbox;
  GtkSpinButton *spinbutton;
  GtkWidget     *label;
  GtkTooltips   *tooltip;

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
    GTK_SPIN_BUTTON(gtk_spin_button_new (adjustment, 0.5, digits));
  /* Only numbers can be entered. */
  gtk_spin_button_set_numeric
    (GTK_SPIN_BUTTON(spinbutton), TRUE);
  gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(spinbutton),
                     TRUE, TRUE, 0);
  gtk_widget_show(GTK_WIDGET(spinbutton));

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
_ogcalc_create_result_label(const gchar   *label_text,
			    const gchar   *tooltip_text,
			    GtkLabel     **result_label_pointer )
{
  GtkWidget   *hbox;
  GtkWidget   *eventbox;
  GtkWidget   *result_label;
  GtkLabel    *result_value;
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
  result_value = GTK_LABEL(gtk_label_new (NULL));
  /* Because it's a result, it is set "selectable", to allow
     copy/paste of the result, but it's not modifiable. */
  gtk_label_set_selectable (GTK_LABEL(result_value), TRUE);
  gtk_box_pack_start (GTK_BOX(hbox), GTK_WIDGET(result_value),
                      TRUE, TRUE, 0);
  gtk_widget_show(GTK_WIDGET(result_value));

  /* Add the tooltip to the event box. */
  tooltip = gtk_tooltips_new();
  gtk_tooltips_set_tip(tooltip, eventbox,
                       tooltip_text, NULL);

  *result_label_pointer = result_value;
  return hbox;
}

/* Reset the interface. */
void
ogcalc_reset( Ogcalc   *ogcalc,
              gpointer  data )
{
  gtk_spin_button_set_value (ogcalc->pg_val, 0.0);
  gtk_spin_button_set_value (ogcalc->ri_val, 0.0);
  gtk_spin_button_set_value (ogcalc->cf_val, 0.0);
  gtk_label_set_markup (ogcalc->og_result, "<b>N/A</b>");
  gtk_label_set_markup (ogcalc->abv_result, "<b>N/A</b>");
}

/* Peform the calculation. */
void
ogcalc_calculate( Ogcalc   *ogcalc,
                  gpointer  data )
{
  gdouble pg, ri, cf, og, abv;
  gchar *og_string;
  gchar *abv_string;

  pg = gtk_spin_button_get_value (ogcalc->pg_val);
  ri = gtk_spin_button_get_value (ogcalc->ri_val);
  cf = gtk_spin_button_get_value (ogcalc->cf_val);

  og = (ri * 2.597) - (pg * 1.644) - 34.4165 + cf;

  /* Do the sums. */
  if (og < 60)
    abv = (og - pg) * 0.130;
  else
    abv = (og - pg) * 0.134;

  /* Display the results.  Note the <b></b> GMarkup tags to
     make it display in Bold. */
  og_string = g_strdup_printf ("<b>%0.2f</b>", og);
  abv_string = g_strdup_printf ("<b>%0.2f</b>", abv);

  gtk_label_set_markup (ogcalc->og_result, og_string);
  gtk_label_set_markup (ogcalc->abv_result, abv_string);

  g_free (og_string);
  g_free (abv_string);
}

/*
 * Local Variables:
 * mode:C
 * fill-column:60
 * End:
 */
