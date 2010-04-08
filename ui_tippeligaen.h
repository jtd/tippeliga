/********************************************************************************
** Form generated from reading UI file 'tippeligaen.ui'
**
** Created: Thu 8. Apr 14:08:39 2010
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
    QAction *actionUkens_lag;
    QAction *actionLaginfo;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuO;
    QMenu *menuVis;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Tippeligaen)
    {
        if (Tippeligaen->objectName().isEmpty())
            Tippeligaen->setObjectName(QString::fromUtf8("Tippeligaen"));
        Tippeligaen->resize(600, 400);
        actionAvslutt = new QAction(Tippeligaen);
        actionAvslutt->setObjectName(QString::fromUtf8("actionAvslutt"));
        actionUkens_lag = new QAction(Tippeligaen);
        actionUkens_lag->setObjectName(QString::fromUtf8("actionUkens_lag"));
        actionUkens_lag->setCheckable(true);
        actionUkens_lag->setChecked(true);
        actionLaginfo = new QAction(Tippeligaen);
        actionLaginfo->setObjectName(QString::fromUtf8("actionLaginfo"));
        actionLaginfo->setCheckable(true);
        centralWidget = new QWidget(Tippeligaen);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Tippeligaen->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Tippeligaen);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuO = new QMenu(menuBar);
        menuO->setObjectName(QString::fromUtf8("menuO"));
        menuVis = new QMenu(menuBar);
        menuVis->setObjectName(QString::fromUtf8("menuVis"));
        Tippeligaen->setMenuBar(menuBar);
        statusBar = new QStatusBar(Tippeligaen);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Tippeligaen->setStatusBar(statusBar);

        menuBar->addAction(menuO->menuAction());
        menuBar->addAction(menuVis->menuAction());
        menuO->addAction(actionAvslutt);
        menuVis->addAction(actionUkens_lag);
        menuVis->addAction(actionLaginfo);
        menuVis->addSeparator();

        retranslateUi(Tippeligaen);

        QMetaObject::connectSlotsByName(Tippeligaen);
    } // setupUi

    void retranslateUi(QMainWindow *Tippeligaen)
    {
        Tippeligaen->setWindowTitle(QApplication::translate("Tippeligaen", "Tippeligaen", 0, QApplication::UnicodeUTF8));
        actionAvslutt->setText(QApplication::translate("Tippeligaen", "Avslutt", 0, QApplication::UnicodeUTF8));
        actionUkens_lag->setText(QApplication::translate("Tippeligaen", "Ukens lag", 0, QApplication::UnicodeUTF8));
        actionLaginfo->setText(QApplication::translate("Tippeligaen", "Laginfo", 0, QApplication::UnicodeUTF8));
        menuO->setTitle(QApplication::translate("Tippeligaen", "Fil", 0, QApplication::UnicodeUTF8));
        menuVis->setTitle(QApplication::translate("Tippeligaen", "Vis", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Tippeligaen: public Ui_Tippeligaen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIPPELIGAEN_H
