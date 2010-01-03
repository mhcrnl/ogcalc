/* ogcalc - calculate %ABV and OG from PG, RI and CF.
 *
 * Copyright (C) 2004  Roger Leigh <rleigh@debian.org>
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
#include <glade/glade.h>

#include "ogcalc.h"

/* This main function merely instantiates the ogcalc class
   and displays its main window. */
int
main (int argc, char *argv[])
{
  /* Initialise GTK+. */
  gtk_init(&argc, &argv);

  /* Create an Ogcalc object. */
  Ogcalc *ogcalc = ogcalc_new();
  /* When the widget is hidden, quit the GTK+ main loop. */
  g_signal_connect(G_OBJECT (ogcalc), "hide",
                   G_CALLBACK (gtk_main_quit), NULL);

  /* Show the object. */
  gtk_widget_show(GTK_WIDGET (ogcalc));

  /* Enter the GTK Event Loop.  This is where all the events
     are caught and handled.  It is exited with
     gtk_main_quit(). */
  gtk_main();

  /* Clean up. */
  gtk_widget_destroy(GTK_WIDGET (ogcalc));

  return 0;
}

// Local Variables:
// mode:C
// fill-column:60
// End:
