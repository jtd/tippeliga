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
    w.show();
    return a.exec();
}
