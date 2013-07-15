#include "ogcalc.h"
#include "ui_ogcalc.h"

#include <sstream>
#include <iomanip>

ogcalc::ogcalc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ogcalc)
{
    ui->setupUi(this);

    reset();
}

ogcalc::~ogcalc()
{
    delete ui;
}

void
ogcalc::calculate()
{
    // PG, RI, and CF values.
    double pg = ui->pg_entry->value();
    double ri = ui->ri_entry->value();
    double cf = ui->cf_entry->value();

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
    ui->og_result->setText(QString::fromStdString(output.str()));
    output.str("");
    output << std::fixed << std::setprecision(2) << abv;
    ui->abv_result->setText(QString::fromStdString(output.str()));
}

void
ogcalc::reset()
{
    ui->pg_entry->setValue(0.0);
    ui->ri_entry->setValue(0.0);
    ui->cf_entry->setValue(0.0);
    ui->og_result->setText("");
    ui->abv_result->setText("");
}
