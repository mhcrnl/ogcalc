#include "ogcalc.h"
#include <QApplication>
#include <cstdlib>

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("/home/rleigh/code/ogcalc/git/qt/ui/cmake");
    QApplication a(argc, argv);

    ogcalc w;
    w.show();

    return a.exec();
}
