#ifndef OGCALC_H
#define OGCALC_H

#include <QMainWindow>

namespace Ui {
class ogcalc;
}

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
    Ui::ogcalc *ui;
};

#endif // OGCALC_H
