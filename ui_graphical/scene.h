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
