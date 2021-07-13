#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "scene.h"
#include "bg.h"
//#include <iproc/message.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Bg background;
    Scene scene;
signals:
    void start(QStringList qlist,bool isSaveToFile,int interval = 1,int duration = 1);
    void stop();
private slots:
    void onStopped();
    void onCalculating();
    void onButtonNowClicked();
    void onButtonStartClicked();
    void onClearLogClicked();
    void onClearDisplayClicked();
    void onMessage(QVector<iproc::message> msgs,int steps,int step);
    void onItemUnderMouse(QString data);

};

#endif // MAINWINDOW_H
