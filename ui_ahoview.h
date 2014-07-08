/********************************************************************************
** Form generated from reading UI file 'ahoview.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AHOVIEW_H
#define UI_AHOVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ahoview
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *ahoview)
    {
        if (ahoview->objectName().isEmpty())
            ahoview->setObjectName(QStringLiteral("ahoview"));
        ahoview->resize(800, 600);
        centralWidget = new QWidget(ahoview);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ahoview->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ahoview);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        ahoview->setMenuBar(menuBar);

        retranslateUi(ahoview);

        QMetaObject::connectSlotsByName(ahoview);
    } // setupUi

    void retranslateUi(QMainWindow *ahoview)
    {
        ahoview->setWindowTitle(QApplication::translate("ahoview", "ahoview", 0));
    } // retranslateUi

};

namespace Ui {
    class ahoview: public Ui_ahoview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AHOVIEW_H
