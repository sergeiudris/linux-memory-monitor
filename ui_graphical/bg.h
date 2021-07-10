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
#ifndef BG_H
#define BG_H

#include <QObject>
#include <vector>
#include <string>
#include <iproc/procinterface.hpp>
#include <iproc/message.hpp>
#include <QThread>
#include <QTimer>
#include <QDateTime>
#include <QLocale>
#include <QVector>
#include <cstdint>

class Bg : public QObject
{
    Q_OBJECT
public:
    Bg(){
        this->moveToThread(&thread);
        thread.start();
    }
    virtual ~Bg(){
        thread.quit();
        if(!thread.wait(2000)){
            thread.terminate();;
        }

    }
private:
    QThread thread;
    QVector<iproc::message> messages;
    QTimer* timerInterval = nullptr;
    std::vector<std::string> titles;
    QString directory;
    int steps;
    int step;
signals:
    void message(QVector<iproc::message> msgs,int steps,int step);
    void stopped();
    void calculating();
public slots:

    inline void onStop(){

        if(timerInterval){
            timerInterval->stop();
            delete timerInterval;
        }

        directory = "";
        emit stopped();
    }

    inline void onStart(QStringList qtitles,bool isSaveToFile,int interval = 1,int duration = 1){

        QDateTime cdt = QDateTime::currentDateTime().toLocalTime();
        QLocale l(QLocale::English);
        QString cdtstr = l.toString(cdt);

        messages.clear();
        messages.resize(0);

        directory = isSaveToFile ? cdtstr : "";
        titles.clear();
        titles.resize(0);
        for(auto& qs: qtitles ){
            titles.push_back(qs.toStdString());
        }

        step = 0;
        steps = duration/interval;
        //QTimer::singleShot(duration*1000, this, SLOT(onStop()));
        timerInterval = new QTimer();
        timerInterval->moveToThread(&this->thread);
        connect(timerInterval,SIGNAL(timeout()),this,SLOT(calculate()));
        timerInterval->start(interval*1000);

        QTimer::singleShot(0, this, SLOT(calculate()));

    }

    inline void calculate(){
        iproc::ProcInterface p;
        uint_least32_t count = p.getPids(titles);
        if(!count){

            iproc::message m;
            m.msg = "No such processes...";
            messages.push_back(m);
            emit message(messages,steps,step);
            onStop();
            return;
        }

        step++;
        emit calculating();

        iproc::message msg = p.calculateForTitles(titles,directory.toStdString());
        messages.push_back(msg);
        emit message(messages,steps,step);
        if(step >= steps){
            onStop();
        }
    }



};

#endif // BG_H
