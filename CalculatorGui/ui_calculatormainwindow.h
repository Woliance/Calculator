/********************************************************************************
** Form generated from reading UI file 'calculatormainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATORMAINWINDOW_H
#define UI_CALCULATORMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalculatorMainWindow
{
public:
    QWidget *centralwidget;
    QTextBrowser *outputTextEdit;
    QLineEdit *inputLineEdit;
    QMenuBar *menubar;
    QMenu *menuColour;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CalculatorMainWindow)
    {
        if (CalculatorMainWindow->objectName().isEmpty())
            CalculatorMainWindow->setObjectName("CalculatorMainWindow");
        CalculatorMainWindow->resize(489, 425);
        centralwidget = new QWidget(CalculatorMainWindow);
        centralwidget->setObjectName("centralwidget");
        outputTextEdit = new QTextBrowser(centralwidget);
        outputTextEdit->setObjectName("outputTextEdit");
        outputTextEdit->setGeometry(QRect(0, 50, 491, 91));
        inputLineEdit = new QLineEdit(centralwidget);
        inputLineEdit->setObjectName("inputLineEdit");
        inputLineEdit->setGeometry(QRect(0, 280, 491, 51));
        CalculatorMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CalculatorMainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 489, 21));
        menuColour = new QMenu(menubar);
        menuColour->setObjectName("menuColour");
        CalculatorMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(CalculatorMainWindow);
        statusbar->setObjectName("statusbar");
        CalculatorMainWindow->setStatusBar(statusbar);

        menubar->addAction(menuColour->menuAction());

        retranslateUi(CalculatorMainWindow);

        QMetaObject::connectSlotsByName(CalculatorMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CalculatorMainWindow)
    {
        CalculatorMainWindow->setWindowTitle(QCoreApplication::translate("CalculatorMainWindow", "CalculatorMainWindow", nullptr));
        menuColour->setTitle(QCoreApplication::translate("CalculatorMainWindow", "Colour", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CalculatorMainWindow: public Ui_CalculatorMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATORMAINWINDOW_H
