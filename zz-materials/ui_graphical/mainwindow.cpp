/****************************************************************************
**
** Copyright (C) 2015 sergeiudris
** Contact: sergei.udris@gmail.com
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
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QVector>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    connect(ui->pushButtonNow,SIGNAL(clicked(bool)),this,SLOT(onButtonNowClicked()));
    connect(ui->pushButtonStart,SIGNAL(clicked(bool)),this,SLOT(onButtonStartClicked()));
    connect(ui->pushButtonClearDisplay,SIGNAL(clicked(bool)),this,SLOT(onClearDisplayClicked()));
    connect(ui->pushButtonClearLog,SIGNAL(clicked(bool)),this,SLOT(onClearLogClicked()));

    connect(this,SIGNAL(start(QStringList,bool,int,int)),&background,SLOT(onStart(QStringList,bool,int,int)));
    connect(this,SIGNAL(stop()),&background,SLOT(onStop()));

    qRegisterMetaType<QVector<iproc::message>>("QVector<iproc::message>");
    connect(&background,SIGNAL(message(QVector<iproc::message>,int,int)),this,SLOT(onMessage(QVector<iproc::message>,int,int)));
    connect(&background,SIGNAL(message(QVector<iproc::message>,int,int)),&scene,SLOT(draw(QVector<iproc::message>,int,int)));
    connect(&background,SIGNAL(stopped()),this,SLOT(onStopped()));
    connect(&background,SIGNAL(calculating()),this,SLOT(onCalculating()));

    connect(&scene,SIGNAL(itemUnderMouse(QString)),this,SLOT(onItemUnderMouse(QString)));

    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsView->setScene(&scene);
    scene.init(ui->graphicsView->width(),ui->graphicsView->height());

    ui->progressBar->setVisible(false);
    ui->labelProgressBar->setVisible(false);

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonNowClicked(){

    if(ui->lineEditProcessName->text().trimmed().isEmpty()){
        ui->plainTextEditLog->appendPlainText("Enter process names...");
        return;
    }

    QStringList qlist = ui->lineEditProcessName->text().split(" ",QString::SkipEmptyParts);
    emit start(qlist,ui->checkBox->isChecked());
    ui->plainTextEditLog->appendPlainText("--taking one measurement...");
    ui->pushButtonStart->setEnabled(false);
    ui->pushButtonNow->setEnabled(false);
}


void MainWindow::onButtonStartClicked(){

    if(ui->pushButtonStart->text() == "start"){
        if(ui->lineEditProcessName->text().trimmed().isEmpty()){
            ui->plainTextEditLog->appendPlainText("Enter process names...");
            return;
        }
        ui->pushButtonNow->setEnabled(false);
        QStringList qlist = ui->lineEditProcessName->text().split(" ",QString::SkipEmptyParts);
        emit start(qlist,ui->checkBox->isChecked(),ui->spinBoxInterval->value(),ui->spinBoxPeriod->value());
        ui->plainTextEditLog->appendPlainText("--starting calculation (period: "+QString::number(ui->spinBoxPeriod->value())+ " sec)...");
    }else{
        emit stop();
    }


}

void MainWindow::onClearLogClicked(){
    ui->plainTextEditLog->clear();
}

void MainWindow::onClearDisplayClicked(){
    ui->plainTextEditDisplay->clear();
}
void MainWindow::onMessage(QVector<iproc::message> messages,int steps,int step){

    ui->progressBar->setVisible(false);
    ui->labelProgressBar->setVisible(false);

    auto msg = messages.back();
    if(!msg.msg.empty()){
        ui->plainTextEditLog->appendPlainText(QString::fromStdString(msg.msg));
        return;
    }

    ui->plainTextEditDisplay->appendPlainText(QString::fromStdString( msg.toString() ));
    ui->plainTextEditLog->appendPlainText(" step "+QString::number(step)+ " of "+ QString::number(steps));

}

void MainWindow::onStopped(){
    ui->pushButtonNow->setEnabled(true);
    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonStart->setText("start");
    ui->plainTextEditLog->appendPlainText("--finished calculation");

}
void MainWindow::onCalculating(){
    ui->progressBar->setVisible(true);
    ui->labelProgressBar->setVisible(true);
    ui->pushButtonStart->setText("stop");
}
void MainWindow::onItemUnderMouse(QString s){
    ui->plainTextEditLog->appendPlainText(s);
}
