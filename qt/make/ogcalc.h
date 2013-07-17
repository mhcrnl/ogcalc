#ifndef OGCALC_H
#define OGCALC_H

#include <QtWidgets/QMainWindow>

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
    QIcon icon;
};

#endif // OGCALC_H
