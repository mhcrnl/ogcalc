#ifndef OGCALC_H
#define OGCALC_H

#include <QtWidgets/QMainWindow>

namespace Ui {
class ogcalc;
}

class ogcalc : public QMainWindow
{
  Q_OBJECT;

public:
  explicit ogcalc(QWidget *parent = 0);
  ~ogcalc();

public slots:
  // Calculation signal handler.
  void calculate();

  // Reset signal handler.
  void reset();

private:
  // The code-generated user interface.
  Ui::ogcalc *ui;
};

#endif // OGCALC_H

/*
 * Local Variables:
 * mode:C++
 * fill-column:60
 * End:
 */
