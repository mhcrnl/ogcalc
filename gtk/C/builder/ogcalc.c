/* ogcalc - calculate %ABV and OG from PG, RI and CF.
 *
 * Copyright © 2003-2004  Roger Leigh <rleigh@debian.org>
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

void
on_button_clicked_reset( GtkWidget *widget,
                         gpointer   data );
void
on_button_clicked_calculate( GtkWidget *widget,
                             gpointer   data );

/* The bulk of the program.  Since Glade and libglade are
   used, this is just 9 lines! */
int main(int argc, char *argv[])
{
  GtkBuilder *builder;
  GtkWidget *window;
  GError *error = NULL;

  /* Initialise GTK+. */
  gtk_init(&argc, &argv);

  /* Load the interface description. */
  builder = gtk_builder_new();
  if (!gtk_builder_add_from_file(builder, "ogcalc.ui", &error))
    { /* Handle error here. */ }

  /* Set up the signal handlers. */
  gtk_builder_connect_signals(builder, (gpointer) builder);

  /* Find the main window (not shown by default, ogcalcmm.cc
     needs it to be hidden initially) and then show it. */
  window = GTK_WIDGET(gtk_builder_get_object(builder, "ogcalc_main_window"));
  gtk_widget_show(window);

  /* Enter the GTK Event Loop.  This is where all the events
     are caught and handled.  It is exited with
     gtk_main_quit(). */
  gtk_main();

  return 0;
}

/* This is a callback.  This resets the values of the entry
   widgets, and clears the results. */
void on_button_clicked_reset( GtkWidget *widget,
                              gpointer   data )
{
  GtkWidget *pg_val;
  GtkWidget *ri_val;
  GtkWidget *cf_val;
  GtkWidget *og_result;
  GtkWidget *abv_result;

  GtkBuilder *builder;

  /* Find the Glade XML tree containing widget. */
  builder = GTK_BUILDER(data);

  /* Pull the other widgets out the the tree. */
  pg_val = GTK_WIDGET(gtk_builder_get_object(builder, "pg_entry"));
  ri_val = GTK_WIDGET(gtk_builder_get_object(builder, "ri_entry"));
  cf_val = GTK_WIDGET(gtk_builder_get_object(builder, "cf_entry"));
  og_result = GTK_WIDGET(gtk_builder_get_object(builder, "og_result"));
  abv_result = GTK_WIDGET(gtk_builder_get_object(builder, "abv_result"));

  gtk_spin_button_set_value (GTK_SPIN_BUTTON(pg_val), 0.0);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON(ri_val), 0.0);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON(cf_val), 0.0);
  gtk_label_set_text (GTK_LABEL(og_result), "");
  gtk_label_set_text (GTK_LABEL(abv_result), "");
}

/* This callback does the actual calculation. */
void on_button_clicked_calculate( GtkWidget *widget,
                                  gpointer   data )
{
  GtkWidget *pg_val;
  GtkWidget *ri_val;
  GtkWidget *cf_val;
  GtkWidget *og_result;
  GtkWidget *abv_result;

  gdouble pg, ri, cf, og, abv;
  gchar *og_string;
  gchar *abv_string;

  GtkBuilder *builder;

  /* Find the Glade XML tree containing widget. */
  builder = GTK_BUILDER(data);

  /* Pull the other widgets out the the tree. */
  pg_val = GTK_WIDGET(gtk_builder_get_object(builder, "pg_entry"));
  ri_val = GTK_WIDGET(gtk_builder_get_object(builder, "ri_entry"));
  cf_val = GTK_WIDGET(gtk_builder_get_object(builder, "cf_entry"));
  og_result = GTK_WIDGET(gtk_builder_get_object(builder, "og_result"));
  abv_result = GTK_WIDGET(gtk_builder_get_object(builder, "abv_result"));

  /* Get the numerical values from the entry widgets. */
  pg = gtk_spin_button_get_value (GTK_SPIN_BUTTON(pg_val));
  ri = gtk_spin_button_get_value (GTK_SPIN_BUTTON(ri_val));
  cf = gtk_spin_button_get_value (GTK_SPIN_BUTTON(cf_val));

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

  gtk_label_set_markup (GTK_LABEL(og_result), og_string);
  gtk_label_set_markup (GTK_LABEL(abv_result), abv_string);

  g_free (og_string);
  g_free (abv_string);
}

/*
 * Local Variables:
 * mode:C
 * fill-column:60
 * End:
 */
