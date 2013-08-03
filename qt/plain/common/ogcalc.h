#ifndef OGCALC_H
#define OGCALC_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "SpinBoxEntry.h"

class ogcalc : public QMainWindow
{
  Q_OBJECT;

public:
  explicit ogcalc (QWidget *parent = 0);
  virtual ~ogcalc ();

public slots:
  // Calculation signal handler.
  void calculate ();

  // Reset signal handler.
  void reset ();

private:
  // Initialise the UI
  void setupUi ();
  // Translate the UI text.
  void retranslateUi ();

  // The widgets that are manipulated.
  QLabel       *pg_label;
  SpinBoxEntry *pg_entry;
  QLabel       *ri_label;
  SpinBoxEntry *ri_entry;
  QLabel       *cf_label;
  SpinBoxEntry *cf_entry;
  QLabel       *og_label;
  QLabel       *og_result;
  QLabel       *abv_label;
  QLabel       *abv_result;
  QPushButton  *quit_button;
  QPushButton  *reset_button;
  QPushButton  *calculate_button;
};

#endif // OGCALC_H

/*
 * Local Variables:
 * mode:C++
 * fill-column:60
 * End:
 */
