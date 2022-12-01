/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gui
{
public:
    QWidget *centralwidget;
    QLabel *Title;
    QPushButton *addBlock;
    QPushButton *deleteRecord;
    QPushButton *editBlock;
    QPushButton *mineBlock;
    QPushButton *verifyExplot;
    QPushButton *showBlockchain;
    QTextBrowser *textBrowser;

    void setupUi(QMainWindow *gui)
    {
        if (gui->objectName().isEmpty())
            gui->setObjectName("gui");
        gui->resize(593, 592);
        gui->setStyleSheet(QString::fromUtf8("QMainWindow{\n"
"	background-color:  teal;\n"
"}"));
        centralwidget = new QWidget(gui);
        centralwidget->setObjectName("centralwidget");
        Title = new QLabel(centralwidget);
        Title->setObjectName("Title");
        Title->setGeometry(QRect(0, 0, 941, 21));
        Title->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	background-color:  black;\n"
"	border: 1px solid black;\n"
"	color: white;\n"
"}"));
        addBlock = new QPushButton(centralwidget);
        addBlock->setObjectName("addBlock");
        addBlock->setGeometry(QRect(390, 30, 181, 41));
        deleteRecord = new QPushButton(centralwidget);
        deleteRecord->setObjectName("deleteRecord");
        deleteRecord->setGeometry(QRect(390, 90, 181, 41));
        editBlock = new QPushButton(centralwidget);
        editBlock->setObjectName("editBlock");
        editBlock->setGeometry(QRect(390, 150, 181, 41));
        mineBlock = new QPushButton(centralwidget);
        mineBlock->setObjectName("mineBlock");
        mineBlock->setGeometry(QRect(390, 210, 181, 41));
        verifyExplot = new QPushButton(centralwidget);
        verifyExplot->setObjectName("verifyExplot");
        verifyExplot->setGeometry(QRect(390, 270, 181, 41));
        showBlockchain = new QPushButton(centralwidget);
        showBlockchain->setObjectName("showBlockchain");
        showBlockchain->setGeometry(QRect(390, 330, 181, 41));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(0, 20, 381, 571));
        gui->setCentralWidget(centralwidget);

        retranslateUi(gui);

        QMetaObject::connectSlotsByName(gui);
    } // setupUi

    void retranslateUi(QMainWindow *gui)
    {
        gui->setWindowTitle(QCoreApplication::translate("gui", "gui", nullptr));
        Title->setText(QCoreApplication::translate("gui", "Blockchain GUI", nullptr));
        addBlock->setText(QCoreApplication::translate("gui", "Add Block ", nullptr));
        deleteRecord->setText(QCoreApplication::translate("gui", "Delete Record", nullptr));
        editBlock->setText(QCoreApplication::translate("gui", "Edit Block", nullptr));
        mineBlock->setText(QCoreApplication::translate("gui", "Mine Blockchain", nullptr));
        verifyExplot->setText(QCoreApplication::translate("gui", "Verify exploit", nullptr));
        showBlockchain->setText(QCoreApplication::translate("gui", "Show Blockchain", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gui: public Ui_gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
