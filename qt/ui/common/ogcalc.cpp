#include <QtUiTools/QUiLoader>
#include <QtWidgets/QVBoxLayout>

#include <sstream>
#include <iomanip>

#include "ogcalc.h"

ogcalc::ogcalc(QWidget *parent):
  QMainWindow(parent)
{
  // Load user interface from file.
  QUiLoader loader;
  QFile file("ogcalc.ui");
  file.open(QFile::ReadOnly);
  QWidget *ui = loader.load(&file, this);
  file.close();

  // Set up signal handlers.
  QMetaObject::connectSlotsByName(this);

  // Find the toplevel widget and add this to ourself.
  QWidget *toplevel = findChild<QWidget *>("toplevel_layout");
  setCentralWidget(toplevel);

  // Find widgets needed by name from the widget hierarchy.
  pg_entry = findChild<SpinBoxEntry *>("pg_entry");
  ri_entry = findChild<SpinBoxEntry *>("ri_entry");
  cf_entry = findChild<SpinBoxEntry *>("cf_entry");
  og_result = findChild<QLabel *>("og_result");
  abv_result = findChild<QLabel *>("abv_result");
  quit_button = findChild<QPushButton *>("quit_button");
  reset_button = findChild<QPushButton *>("reset_button");
  calculate_button = findChild<QPushButton *>("calculate_button");

  // Connect signals to ourself.  Due to connecting to slots
  // implemented by ourself, these need to be connected by hand.  The
  // signal autoconnection above can't connect to these slots.
  QObject::connect(reset_button, SIGNAL(clicked()), this, SLOT(reset()));
  QObject::connect(quit_button, SIGNAL(clicked()), this, SLOT(close()));
  QObject::connect(calculate_button, SIGNAL(clicked()), this, SLOT(calculate()));
  QObject::connect(calculate_button, SIGNAL(clicked()), reset_button, SLOT(setFocus()));

  // Set interface to initial state.
  reset();
}

ogcalc::~ogcalc()
{
}

void
ogcalc::calculate()
{
  // PG, RI, and CF values.
  double pg = pg_entry->value();
  double ri = ri_entry->value();
  double cf = cf_entry->value();

  // Calculate OG.
  double og = (ri * 2.597) - (pg * 1.644) - 34.4165 + cf;

  // Calculate ABV.
  double abv;
  if (og < 60)
    abv = (og - pg) * 0.130;
  else
    abv = (og - pg) * 0.134;

  // Display the results.
  std::ostringstream output;
  // Use the user's locale for this stream.
  output.imbue(std::locale(""));
  output << std::fixed << std::setprecision(2) << og;
  og_result->setText(QString::fromStdString(output.str()));
  output.str("");
  output << std::fixed << std::setprecision(2) << abv;
  abv_result->setText(QString::fromStdString(output.str()));

  // Reset is the default action after calculation
  reset_button->setDefault(true);
  calculate_button->setDefault(false);
}

void
ogcalc::reset()
{
  // Reset entry widgets to default state.
  pg_entry->setValue(0.0);
  ri_entry->setValue(0.0);
  cf_entry->setValue(0.0);

  // Clear results.
  og_result->setText("");
  abv_result->setText("");

  // Move focus back to the PG entry.
  pg_entry->setFocus();
  pg_entry->selectAll();

  // Calculate is the default action during entry.
  reset_button->setDefault(false);
  calculate_button->setDefault(true);
}
