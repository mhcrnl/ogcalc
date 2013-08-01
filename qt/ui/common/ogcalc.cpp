#include <QtUiTools/QUiLoader>
#include <QtWidgets/QVBoxLayout>

#include <sstream>
#include <iomanip>

#include "ogcalc.h"

ogcalc::ogcalc(QWidget *parent) :
    QMainWindow(parent)
{
    QUiLoader loader;
    QFile file("ogcalc.ui");
    file.open(QFile::ReadOnly);
    QWidget *ui = loader.load(&file, this);
    file.close();

    QMetaObject::connectSlotsByName(this);

    QWidget *toplevel = findChild<QWidget *>("toplevel_layout");
    setCentralWidget(toplevel);

    pg_entry = findChild<SpinBoxEntry *>("pg_entry");
    ri_entry = findChild<SpinBoxEntry *>("ri_entry");
    cf_entry = findChild<SpinBoxEntry *>("cf_entry");
    og_result = findChild<QLabel *>("og_result");
    abv_result = findChild<QLabel *>("abv_result");
    quit_button = findChild<QPushButton *>("quit");
    reset_button = findChild<QPushButton *>("reset");
    calculate_button = findChild<QPushButton *>("calculate");

    QObject::connect(reset_button, SIGNAL(clicked()), this, SLOT(reset()));
    QObject::connect(quit_button, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(calculate_button, SIGNAL(clicked()), this, SLOT(calculate()));
    QObject::connect(calculate_button, SIGNAL(clicked()), reset_button, SLOT(setFocus()));

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

    std::ostringstream output;
    // Use the user's locale for this stream.
    output.imbue(std::locale(""));
    output << std::fixed << std::setprecision(2) << og;
    og_result->setText(QString::fromStdString(output.str()));
    output.str("");
    output << std::fixed << std::setprecision(2) << abv;
    abv_result->setText(QString::fromStdString(output.str()));

    reset_button->setDefault(true);
    calculate_button->setDefault(false);
}

void
ogcalc::reset()
{
    pg_entry->setValue(0.0);
    ri_entry->setValue(0.0);
    cf_entry->setValue(0.0);
    og_result->setText("");
    abv_result->setText("");
    pg_entry->setFocus();
    pg_entry->selectAll();
    reset_button->setDefault(false);
    calculate_button->setDefault(true);
}
