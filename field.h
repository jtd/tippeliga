#ifndef FIELD_H
#define FIELD_H

#include <QtGui>
#include <QLabel>
#include <QWidget>
#include <QDragMoveEvent>

class Field : public QWidget
{
Q_OBJECT
public:
    explicit Field(QWidget *parent = 0);
    void addLabel(QLabel* label);
    QLabel* label;
    QLabel *keeperLabel;


signals:

public slots:

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);

};

#endif // FIELD_H
