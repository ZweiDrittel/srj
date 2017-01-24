/********************************************************************************
** Form generated from reading UI file 'datainput.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAINPUT_H
#define UI_DATAINPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataInput
{
public:
    QWidget *centralWidget;
    QPushButton *Button;
    QLineEdit *Result;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DataInput)
    {
        if (DataInput->objectName().isEmpty())
            DataInput->setObjectName(QStringLiteral("DataInput"));
        DataInput->resize(400, 300);
        centralWidget = new QWidget(DataInput);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Button = new QPushButton(centralWidget);
        Button->setObjectName(QStringLiteral("Button"));
        Button->setGeometry(QRect(110, 140, 75, 23));
        Result = new QLineEdit(centralWidget);
        Result->setObjectName(QStringLiteral("Result"));
        Result->setGeometry(QRect(100, 190, 113, 20));
        DataInput->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DataInput);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        DataInput->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DataInput);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DataInput->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DataInput);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DataInput->setStatusBar(statusBar);

        retranslateUi(DataInput);

        QMetaObject::connectSlotsByName(DataInput);
    } // setupUi

    void retranslateUi(QMainWindow *DataInput)
    {
        DataInput->setWindowTitle(QApplication::translate("DataInput", "DataInput", 0));
        Button->setText(QApplication::translate("DataInput", "klappts?", 0));
    } // retranslateUi

};

namespace Ui {
    class DataInput: public Ui_DataInput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAINPUT_H
