/****************************************************************************
**
** Copyright (C) 2016 Serge Joggen.
** Contact: serge.joggen@gmail.com
**
** This file is part of Linux Memory Monitor
** Program uses /proc interface to calculate precise RAM usage for a group of processes,
** e.g. browser,database etc., excluding shared and not present(swapped out) memory pages
**
**
** Linux Memory Monitor is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.

** Linux Memory Monitor is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with Linux Memory Monitor.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/
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
