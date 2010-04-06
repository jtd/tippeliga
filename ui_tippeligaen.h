/********************************************************************************
** Form generated from reading UI file 'tippeligaen.ui'
**
** Created: Tue 6. Apr 10:19:21 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIPPELIGAEN_H
#define UI_TIPPELIGAEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tippeligaen
{
public:
    QAction *actionAvslutt;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuO;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Tippeligaen)
    {
        if (Tippeligaen->objectName().isEmpty())
            Tippeligaen->setObjectName(QString::fromUtf8("Tippeligaen"));
        Tippeligaen->resize(600, 400);
        actionAvslutt = new QAction(Tippeligaen);
        actionAvslutt->setObjectName(QString::fromUtf8("actionAvslutt"));
        centralWidget = new QWidget(Tippeligaen);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Tippeligaen->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Tippeligaen);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuO = new QMenu(menuBar);
        menuO->setObjectName(QString::fromUtf8("menuO"));
        Tippeligaen->setMenuBar(menuBar);
        statusBar = new QStatusBar(Tippeligaen);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Tippeligaen->setStatusBar(statusBar);

        menuBar->addAction(menuO->menuAction());
        menuO->addAction(actionAvslutt);

        retranslateUi(Tippeligaen);

        QMetaObject::connectSlotsByName(Tippeligaen);
    } // setupUi

    void retranslateUi(QMainWindow *Tippeligaen)
    {
        Tippeligaen->setWindowTitle(QApplication::translate("Tippeligaen", "Tippeligaen", 0, QApplication::UnicodeUTF8));
        actionAvslutt->setText(QApplication::translate("Tippeligaen", "Avslutt", 0, QApplication::UnicodeUTF8));
        menuO->setTitle(QApplication::translate("Tippeligaen", "Fil", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Tippeligaen: public Ui_Tippeligaen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIPPELIGAEN_H
