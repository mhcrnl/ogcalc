#include "ogcalc.h"
#include <QApplication>
#include <cstdlib>

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath(".");
    QApplication a(argc, argv);

    ogcalc w;
    w.show();

    return a.exec();
}
