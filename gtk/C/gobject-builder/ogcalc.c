/* ogcalc - calculate %ABV and OG from PG, RI and CF.
 *
 * Copyright © 2004  Roger Leigh <rleigh@debian.org>
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

  /* Load the interface description. */
  self->builder = gtk_builder_new();
  char *objects[] = { "ogcalc_main_vbox", NULL };
  GError *error = NULL;

  gtk_builder_add_objects_from_file(self->builder, "ogcalc.ui",
				    objects, &error);

  /* Get the interface root and pack it into our window. */
  gtk_container_add
    (GTK_CONTAINER (self),
     GTK_WIDGET(gtk_builder_get_object(self->builder,
				       "ogcalc_main_vbox")));

  /* Get the widgets. */
  self->pg_val = GTK_SPIN_BUTTON
    (gtk_builder_get_object (self->builder, "pg_entry"));
  self->ri_val = GTK_SPIN_BUTTON
    (gtk_builder_get_object (self->builder, "ri_entry"));
  self->cf_val = GTK_SPIN_BUTTON
    (gtk_builder_get_object (self->builder, "cf_entry"));
  self->og_result = GTK_LABEL
    (gtk_builder_get_object (self->builder, "og_result"));
  self->abv_result = GTK_LABEL
    (gtk_builder_get_object (self->builder, "abv_result"));
  self->quit_button = GTK_BUTTON
    (gtk_builder_get_object (self->builder, "quit_button"));
  self->reset_button = GTK_BUTTON
    (gtk_builder_get_object (self->builder, "reset_button"));
  self->calculate_button = GTK_BUTTON
    (gtk_builder_get_object (self->builder, "calculate_button"));

  /* Set up the signal handlers. */
  gtk_builder_connect_signals(self->builder, NULL);

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
}

/* This is the object initialisation function.  It is
   comparable to a C++ destructor.  Note the similarity
   between "self" and the C++ "this" pointer. */
static void
ogcalc_finalize (Ogcalc *self)
{
  /* Free the XML interface description. */
  g_object_unref(G_OBJECT(self->builder));
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

/* Reset the interface. */
void
ogcalc_reset( Ogcalc   *ogcalc,
              gpointer  data )
{
  gtk_spin_button_set_value (ogcalc->pg_val, 0.0);
  gtk_spin_button_set_value (ogcalc->ri_val, 0.0);
  gtk_spin_button_set_value (ogcalc->cf_val, 0.0);
  gtk_label_set_text (ogcalc->og_result, "");
  gtk_label_set_text (ogcalc->abv_result, "");
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
