/****************************************************************************
**
** Copyright (C) 2016 sergeiudris
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
#ifndef SCENE_H
#define SCENE_H
#include <QString>
#include <QPixmap>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QVector>
#include <iproc/message.hpp>

class Scene :public QGraphicsScene
{
    Q_OBJECT
private:
    QGraphicsView* view_;
    QPixmap pixmap;
   // float width_;
  //  float height_;
public:

    //using QGraphicsScene::QGraphicsScene;
    Scene(){}
    virtual ~Scene(){}

    void init(float width,float height);


    void addGraph();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void draw(QVector<iproc::message> msgs,int steps,int step);
signals:
    void itemUnderMouse(QString data);
};

#endif // SCENE_H
