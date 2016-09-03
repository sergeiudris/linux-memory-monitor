/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonStart;
    QPlainTextEdit *plainTextEditLog;
    QLineEdit *lineEditProcessName;
    QSpinBox *spinBoxPeriod;
    QPushButton *pushButtonNow;
    QSpinBox *spinBoxInterval;
    QPlainTextEdit *plainTextEditDisplay;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButtonClearLog;
    QPushButton *pushButtonClearDisplay;
    QGraphicsView *graphicsView;
    QProgressBar *progressBar;
    QLabel *labelProgressBar;
    QCheckBox *checkBox;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(662, 507);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButtonStart = new QPushButton(centralWidget);
        pushButtonStart->setObjectName(QStringLiteral("pushButtonStart"));
        pushButtonStart->setGeometry(QRect(10, 40, 99, 27));
        plainTextEditLog = new QPlainTextEdit(centralWidget);
        plainTextEditLog->setObjectName(QStringLiteral("plainTextEditLog"));
        plainTextEditLog->setGeometry(QRect(10, 230, 241, 201));
        QFont font;
        font.setPointSize(8);
        plainTextEditLog->setFont(font);
        plainTextEditLog->setReadOnly(true);
        lineEditProcessName = new QLineEdit(centralWidget);
        lineEditProcessName->setObjectName(QStringLiteral("lineEditProcessName"));
        lineEditProcessName->setGeometry(QRect(10, 10, 231, 27));
        spinBoxPeriod = new QSpinBox(centralWidget);
        spinBoxPeriod->setObjectName(QStringLiteral("spinBoxPeriod"));
        spinBoxPeriod->setGeometry(QRect(10, 110, 101, 31));
        spinBoxPeriod->setMinimum(1);
        spinBoxPeriod->setMaximum(604800);
        spinBoxPeriod->setValue(1);
        pushButtonNow = new QPushButton(centralWidget);
        pushButtonNow->setObjectName(QStringLiteral("pushButtonNow"));
        pushButtonNow->setGeometry(QRect(140, 40, 99, 27));
        spinBoxInterval = new QSpinBox(centralWidget);
        spinBoxInterval->setObjectName(QStringLiteral("spinBoxInterval"));
        spinBoxInterval->setGeometry(QRect(10, 150, 101, 31));
        spinBoxInterval->setMinimum(1);
        spinBoxInterval->setMaximum(604800);
        spinBoxInterval->setValue(1);
        plainTextEditDisplay = new QPlainTextEdit(centralWidget);
        plainTextEditDisplay->setObjectName(QStringLiteral("plainTextEditDisplay"));
        plainTextEditDisplay->setGeometry(QRect(260, 130, 371, 301));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(120, 120, 67, 17));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(120, 160, 67, 17));
        pushButtonClearLog = new QPushButton(centralWidget);
        pushButtonClearLog->setObjectName(QStringLiteral("pushButtonClearLog"));
        pushButtonClearLog->setGeometry(QRect(10, 430, 88, 27));
        pushButtonClearDisplay = new QPushButton(centralWidget);
        pushButtonClearDisplay->setObjectName(QStringLiteral("pushButtonClearDisplay"));
        pushButtonClearDisplay->setGeometry(QRect(260, 430, 88, 27));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(260, 10, 371, 111));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 190, 101, 21));
        progressBar->setMaximum(0);
        progressBar->setValue(-1);
        labelProgressBar = new QLabel(centralWidget);
        labelProgressBar->setObjectName(QStringLiteral("labelProgressBar"));
        labelProgressBar->setGeometry(QRect(120, 190, 91, 17));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(10, 80, 111, 22));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 662, 19));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "linux memory monitor", 0));
#ifndef QT_NO_TOOLTIP
        MainWindow->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>this program calculates total RAM usage for a group of processes (no shared memory duplication)</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        pushButtonStart->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>take measurements over time period</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        pushButtonStart->setText(QApplication::translate("MainWindow", "start", 0));
#ifndef QT_NO_TOOLTIP
        plainTextEditLog->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>program log</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        lineEditProcessName->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>enter process name(s) separated by whitespace</p><p>(e.g.: chrome firefox skype oracle)</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        lineEditProcessName->setPlaceholderText(QApplication::translate("MainWindow", "enter app name...", 0));
#ifndef QT_NO_TOOLTIP
        spinBoxPeriod->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>for how long to work (seconds)</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        spinBoxPeriod->setSuffix(QApplication::translate("MainWindow", " sec", 0));
#ifndef QT_NO_TOOLTIP
        pushButtonNow->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>take one measurement</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        pushButtonNow->setText(QApplication::translate("MainWindow", "once", 0));
#ifndef QT_NO_TOOLTIP
        spinBoxInterval->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>how often to take measurements (seconds)</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        spinBoxInterval->setSuffix(QApplication::translate("MainWindow", " sec", 0));
#ifndef QT_NO_TOOLTIP
        plainTextEditDisplay->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>measurements are shown here (and saved to files in  directory with program's .exe)</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("MainWindow", "period", 0));
        label_2->setText(QApplication::translate("MainWindow", "interval", 0));
#ifndef QT_NO_TOOLTIP
        pushButtonClearLog->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>clear log</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        pushButtonClearLog->setText(QApplication::translate("MainWindow", "Clear", 0));
#ifndef QT_NO_TOOLTIP
        pushButtonClearDisplay->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>clear log</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        pushButtonClearDisplay->setText(QApplication::translate("MainWindow", "Clear", 0));
#ifndef QT_NO_TOOLTIP
        graphicsView->setToolTip(QApplication::translate("MainWindow", "charts", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        progressBar->setToolTip(QApplication::translate("MainWindow", "accessing files in /proc...", 0));
#endif // QT_NO_TOOLTIP
        labelProgressBar->setText(QApplication::translate("MainWindow", "calculating...", 0));
#ifndef QT_NO_TOOLTIP
        checkBox->setToolTip(QApplication::translate("MainWindow", "folder with data will be created in the directory where program was started ", 0));
#endif // QT_NO_TOOLTIP
        checkBox->setText(QApplication::translate("MainWindow", "save to files", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
