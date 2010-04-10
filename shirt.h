#ifndef SHIRT_H
#define SHIRT_H

#include <QtGui>
#include <QLabel>
#include <QWidget>
#include <QDragMoveEvent>
//#include "tippeligaen.h"

class Shirt : public QWidget
{
    Q_OBJECT
    public:
        explicit Shirt(QWidget *parent = 0);
        void addLabel(QLabel* label);
        QLabel* label;

    signals:

    public slots:

    protected:
        void dragMoveEvent(QDragMoveEvent *event);
        void mousePressEvent(QMouseEvent *event);
};

#endif // SHIRT_H
