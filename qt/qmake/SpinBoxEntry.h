#ifndef SPINBOXENTRY_H
#define SPINBOXENTRY_H

#include <QDoubleSpinBox>
#include <QKeyEvent>

class SpinBoxEntry : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit SpinBoxEntry(QWidget *parent = 0);

protected:
    void
    keyPressEvent(QKeyEvent *event);

signals:
    void
    enterPressed();

public slots:
    
};

#endif // SPINBOXENTRY_H
