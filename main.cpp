#include <QtGui/QApplication>
#include "tippeligaen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tippeligaen w;
    w.show();
    return a.exec();
}
