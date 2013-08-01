#ifndef OGCALC_H
#define OGCALC_H

#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMainWindow>

#include "SpinBoxEntry.h"

class ogcalc : public QMainWindow
{
    Q_OBJECT

public:
    explicit ogcalc(QWidget *parent = 0);
    ~ogcalc();

public slots:
    void calculate();

    void reset();

private:
    SpinBoxEntry *pg_entry;
    SpinBoxEntry *ri_entry;
    SpinBoxEntry *cf_entry;
    QLabel *og_result;
    QLabel *abv_result;
    QPushButton *quit_button;
    QPushButton *reset_button;
    QPushButton *calculate_button;
};

#endif // OGCALC_H

/*
 * Local Variables:
 * mode:C++
 * fill-column:60
 * End:
 */
