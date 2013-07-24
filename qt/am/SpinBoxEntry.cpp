#include "SpinBoxEntry.h"

SpinBoxEntry::SpinBoxEntry(QWidget *parent) :
    QDoubleSpinBox(parent)
{
}

void
SpinBoxEntry::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        emit enterPressed();
        break;
    default:
        QDoubleSpinBox::keyPressEvent(event);
    }
}
