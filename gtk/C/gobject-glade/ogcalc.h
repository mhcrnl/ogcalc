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

#ifndef OGCALC_H
#define OGCALC_H

#include <gtk/gtk.h>
#include <glade/glade.h>

/* The following macros are GObject boilerplate. */

/* Return the GType of the Ogcalc class. */
#define OGCALC_TYPE \
           (ogcalc_get_type ())

/* Cast an object to type Ogcalc.  The object must be of
   type Ogcalc, or derived from Ogcalc for this to work.
   This is similar to a C++ dynamic_cast<>. */
#define OGCALC(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
                               OGCALC_TYPE, \
                               Ogcalc))

/* Cast a derived class to an OgcalcClass. */
#define OGCALC_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), \
                            OGCALC_TYPE, \
                            OgcalcClass))

/* Check if an object is an Ogcalc. */
#define IS_OGCALC(obj) \
  (G_TYPE_CHECK_TYPE ((obj), \
                      OGCALC_TYPE))

/* Check if a class is an OgcalcClass. */
#define IS_OGCALC_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), \
                            OGCALC_TYPE))

/* Get the OgcalcClass class. */
#define OGCALC_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
                              OGCALC_TYPE, \
                              OgcalcClass))

/* The Ogcalc object instance type. */
typedef struct _Ogcalc Ogcalc;
/* The Ogcalc class type. */
typedef struct _OgcalcClass OgcalcClass;

/* The definition of Ogcalc. */
struct _Ogcalc
{
  GtkWindow parent; /* The object derives from GtkWindow. */
  GladeXML *xml;    /* The XML interface. */
  /* Widgets contained within the window. */
  GtkSpinButton *pg_val;
  GtkSpinButton *ri_val;
  GtkSpinButton *cf_val;
  GtkLabel *og_result;
  GtkLabel *abv_result;
  GtkButton* quit_button;
  GtkButton* reset_button;
  GtkButton* calculate_button;
};

struct _OgcalcClass
{
  /* The class derives from GtkWindowClass. */
  GtkWindowClass parent;
  /* No other class properties are required (e.g. virtual
     functions). */
};

/* The following functions are described in ogcalc.c */

GType ogcalc_get_type (void);

Ogcalc *
ogcalc_new (void);

gboolean
ogcalc_on_delete_event( Ogcalc   *ogcalc,
                        GdkEvent *event,
                        gpointer  data );

void
ogcalc_reset( Ogcalc    *ogcalc,
              gpointer   data );

void
ogcalc_calculate( Ogcalc    *ogcalc,
                  gpointer   data );

#endif /* OGCALC_H */

/*
 * Local Variables:
 * mode:C
 * fill-column:60
 * End:
 */
