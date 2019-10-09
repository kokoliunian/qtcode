#include "curvescene.h"
#include <QPainter>
#include <QDebug>
#include <QTime>
#define QX_TIME_PIXEL  100
#define QX_VALUE_PIXEL 27
curvescene::curvescene()
{
    initback();


    //addLine(0,0,100,100);
   // addRect(100,100,50,80);

    textColor.setRgb(119,201,219);
    curveColor.setRgb(255,0,0);

    initHeightAxis();

    initTimeAxis();

    qDebug()<<"init curvescene done";


    QList<CurvePoint> ptlst;
    drawCurve(ptlst);

}
//网格背景
void curvescene::initback()
{
        QPolygonF myPolygon1;
        myPolygon1 << QPointF(0,10) << QPointF(20,10);
        QPolygonF myPolygon2;
        myPolygon2 << QPointF(10,0) << QPointF(10,20);
        QPixmap pixmap(20, 20);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        QVector<qreal> dashes;//line style--虚线
        qreal space = 2;
        dashes << 2 << space << 2 <<space;
        QPen pen(Qt::lightGray,1);
        pen.setDashPattern(dashes);
        pen.setWidth(1);
        painter.setPen(pen);
        painter.translate(0, 0);
        painter.drawPolyline(myPolygon1);
        painter.drawPolyline(myPolygon2);
        setBackgroundBrush(pixmap);
}

void curvescene::initHeightAxis()
{
    for(int i=0;i<haxisTextList.size();++i)
        {
            removeItem(haxisTextList[i]);
            delete haxisTextList[i];
        }
        haxisTextList.clear();
        for(int i=0;i<19;i++)
        {
            QGraphicsTextItem* text=new QGraphicsTextItem;
            text->setPlainText(QObject::tr("%1").arg(9-i));
            text->setFont(QFont("Arial",13,QFont::Normal));
            text->setDefaultTextColor(textColor);
//#define VIEW_HEIGHT 886
//#define VIEW_WIDTH  553
            text->setPos(0,-277+(i+1)*QX_VALUE_PIXEL-13/2);

            haxisTextList.append(text);
            addItem(text);
        }
}

void curvescene::drawCurve(QList<CurvePoint> &datalist)
{
    if(datalist.size()==0)
        ;
 //       return;

    QPainterPath *paintpath=0;

    paintpath=new QPainterPath;
    paintpath->moveTo(0,0);

    paintpath->lineTo(100,200);

    paintpath->lineTo(100,-200);
     paintpath->lineTo(150,-250);

     paintpath->lineTo(180,300);
     paintpath->lineTo(190,220);
      paintpath->lineTo(500,10);

      QPen p;
      p.setColor(curveColor);
      p.setWidthF(2);


    QGraphicsPathItem* pathItem=new QGraphicsPathItem;

    pathItem->setPen(p);

    pathItem->setPath(*paintpath);


    addItem(pathItem);


}

void curvescene::initTimeAxis()
{
    //#define VIEW_HEIGHT 886
    //#define VIEW_WIDTH  553
        QTime ct=QTime::currentTime();

       for(int i=0;i<btAxisTextList.size();++i)
       {
           removeItem(btAxisTextList[i]);
           delete btAxisTextList[i];
       }
       btAxisTextList.clear();

       for(int i=0;i<10;i++)
       {
           QGraphicsTextItem *item1=new QGraphicsTextItem;
           QTime t=ct.addSecs(i*10);
           item1->setPlainText(t.toString("hh:mm:ss"));
           item1->setFont(QFont("Arial",13,QFont::Normal));
           item1->setDefaultTextColor(textColor);
           item1->setPos(i*QX_TIME_PIXEL,553/2-26);
           addItem(item1);
           btAxisTextList.append(item1);
       }

}

void curvescene::testtimetout()
{

}
