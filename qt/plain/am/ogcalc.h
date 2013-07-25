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

  ~ogcalc ();

  public slots:
  void calculate ();

  void reset ();

 private:
  void setupUi ();
  void retranslateUi ();

  QLabel       *pg_label;
  SpinBoxEntry *pg_entry;
  QLabel       *ri_label;
  SpinBoxEntry *ri_entry;
  QLabel       *cf_label;
  SpinBoxEntry *cf_entry;
  QLabel       *og_label;
  QLabel       *og_result;
  QLabel       *abv_entry;
  QLabel       *abv_result;
  QPushButton  *quit_button;
  QPushButton  *reset_button;
  QPushButton  *calculate_button;
};

#endif // OGCALC_H
