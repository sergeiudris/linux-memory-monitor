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
#include "scene.h"

void Scene::init(float width, float height){
    //    this->width_ = width;
    //    this->height_ = height;
    this->setSceneRect(0,0,width,height);

    this->setBackgroundBrush(QBrush(QColor(255,255,255,255)));
}

void Scene::addGraph(){
    //    QPixmap map(view_->width(),view_->height());
    //    QPainter painter(&map);

    //    painter.setPen(color);
    //    painter.drawLine(0,0,100,100);
    //    // scene_.addPixmap(map);
    //  QLine line(0,0,this->width(),this->height());
    //  QPen pen(color);
    //   pen.setWidth(this->height()*0.03);
    //   this->addLine(line,pen);

}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

//    for(auto i :this->items()){
//        i->setToolTip("");
//    }

//    QPointF p = event->scenePos();
//    QGraphicsItem* item = this->itemAt(p,this->views().at(0)->transform());

//    if(item){

//        item->data(1);
//        item->setToolTip();
//        emit itemUnderMouse("yep");
//    }

}

void Scene::draw(QVector<iproc::message> msgs, int steps, int step){

    if(!msgs.back().msg.empty()){
        return;
    }

    this->clear();
    float startX = this->width()*0.1;
    float endX = this->width()*0.9;
    float width = this->width()*0.8 / (float)steps;
    float max = (float)msgs.back().meminf.MemTotal;
    QPolygonF p;

    p << QPoint(0,this->height());
    for(int i = 0;i< msgs.size();i++){
        float x = startX+width*i;
        float ratio = msgs[i].distinctRss/max;
        float y = (1-ratio)*this->height();
        QPoint pos(x,y);
        p << pos;
        QRectF r(x - 4,y - 4,8,8);
        QGraphicsRectItem* ritem =  this->addRect(r,QPen(),QBrush(QColor(0,220,0,255)));
        ritem->setZValue(1);
       // ritem->setData(1,QVariant(ratio));
        ritem->setToolTip(QString::fromStdString(msgs[i].toString()));
        QGraphicsTextItem* ti = this->addText(QString::number((int)(ratio*100)) + " %");
        ti->setZValue(2);
        ti->setPos(x-2,y-18);
    }
    p << QPoint(this->width(),this->height());
    QGraphicsPolygonItem* pitem = this->addPolygon(p);
    pitem->setZValue(0);
    pitem->setToolTip(QString::fromStdString( msgs.back().titles));
  //  QColor color(qrand()%255,qrand()%255,qrand()%255);
    QColor color(101,156,239,125);
    QBrush b(color);
    pitem->setBrush(b);

}


