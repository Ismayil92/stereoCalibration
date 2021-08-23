/********************************************************************************
** Form generated from reading UI file 'calibrationX18346.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CALIBRATIONX18346_H
#define CALIBRATIONX18346_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalibrationWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *leftFrame;
    QGraphicsView *rightFrame;
    QPushButton *btnCalibrate;
    QPushButton *btnSave;
    QLabel *label;
    QTextEdit *textErrorMetrics;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *btnAdd;
    QLabel *label_4;
    QLabel *lblNumber;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CalibrationWindow)
    {
        if (CalibrationWindow->objectName().isEmpty())
            CalibrationWindow->setObjectName(QStringLiteral("CalibrationWindow"));
        CalibrationWindow->resize(1319, 628);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CalibrationWindow->sizePolicy().hasHeightForWidth());
        CalibrationWindow->setSizePolicy(sizePolicy);
        CalibrationWindow->setMinimumSize(QSize(1319, 628));
        CalibrationWindow->setMaximumSize(QSize(1319, 628));
        centralwidget = new QWidget(CalibrationWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        leftFrame = new QGraphicsView(centralwidget);
        leftFrame->setObjectName(QStringLiteral("leftFrame"));
        leftFrame->setGeometry(QRect(10, 30, 640, 480));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(leftFrame->sizePolicy().hasHeightForWidth());
        leftFrame->setSizePolicy(sizePolicy1);
        leftFrame->setMinimumSize(QSize(640, 480));
        leftFrame->setMaximumSize(QSize(640, 480));
        rightFrame = new QGraphicsView(centralwidget);
        rightFrame->setObjectName(QStringLiteral("rightFrame"));
        rightFrame->setGeometry(QRect(650, 30, 640, 480));
        sizePolicy1.setHeightForWidth(rightFrame->sizePolicy().hasHeightForWidth());
        rightFrame->setSizePolicy(sizePolicy1);
        rightFrame->setMinimumSize(QSize(640, 480));
        rightFrame->setMaximumSize(QSize(640, 480));
        btnCalibrate = new QPushButton(centralwidget);
        btnCalibrate->setObjectName(QStringLiteral("btnCalibrate"));
        btnCalibrate->setGeometry(QRect(390, 530, 89, 31));
        btnSave = new QPushButton(centralwidget);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setGeometry(QRect(500, 530, 89, 31));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(630, 540, 151, 17));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(11);
        label->setFont(font);
        textErrorMetrics = new QTextEdit(centralwidget);
        textErrorMetrics->setObjectName(QStringLiteral("textErrorMetrics"));
        textErrorMetrics->setGeometry(QRect(780, 530, 141, 41));
        QFont font1;
        font1.setPointSize(14);
        textErrorMetrics->setFont(font1);
        textErrorMetrics->setReadOnly(true);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(250, 10, 121, 17));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(930, 10, 121, 17));
        btnAdd = new QPushButton(centralwidget);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        btnAdd->setGeometry(QRect(280, 530, 91, 31));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(70, 530, 171, 20));
        QFont font2;
        font2.setFamily(QStringLiteral("Dyuthi"));
        font2.setPointSize(12);
        label_4->setFont(font2);
        lblNumber = new QLabel(centralwidget);
        lblNumber->setObjectName(QStringLiteral("lblNumber"));
        lblNumber->setGeometry(QRect(70, 550, 121, 31));
        QFont font3;
        font3.setFamily(QStringLiteral("aakar"));
        font3.setPointSize(14);
        font3.setBold(true);
        font3.setWeight(75);
        lblNumber->setFont(font3);
        lblNumber->setTextFormat(Qt::PlainText);
        CalibrationWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CalibrationWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1319, 22));
        CalibrationWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(CalibrationWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        CalibrationWindow->setStatusBar(statusbar);

        retranslateUi(CalibrationWindow);

        QMetaObject::connectSlotsByName(CalibrationWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CalibrationWindow)
    {
        CalibrationWindow->setWindowTitle(QApplication::translate("CalibrationWindow", "CalibrationWindow", Q_NULLPTR));
        btnCalibrate->setText(QApplication::translate("CalibrationWindow", "Calibrate", Q_NULLPTR));
        btnSave->setText(QApplication::translate("CalibrationWindow", "Save", Q_NULLPTR));
        label->setText(QApplication::translate("CalibrationWindow", "Reprojection Error:", Q_NULLPTR));
        textErrorMetrics->setPlaceholderText(QString());
        label_2->setText(QApplication::translate("CalibrationWindow", "Left Camera", Q_NULLPTR));
        label_3->setText(QApplication::translate("CalibrationWindow", "Right Camera", Q_NULLPTR));
        btnAdd->setText(QApplication::translate("CalibrationWindow", "Add", Q_NULLPTR));
        label_4->setText(QApplication::translate("CalibrationWindow", "Number of taken images:", Q_NULLPTR));
        lblNumber->setText(QApplication::translate("CalibrationWindow","0", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CalibrationWindow: public Ui_CalibrationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CALIBRATIONX18346_H

