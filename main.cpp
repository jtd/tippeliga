#include <QtGui/QApplication>
#include "tippeligaen.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!createConnection()){
        return 1;
    }

    Tippeligaen w;
    w.setWindowState(Qt::WindowMaximized);
    w.setWindowIcon(QIcon(":/bilder/tippeliga.png"));
    w.show();
    return a.exec();
}
