#ifndef CURVESCENE_H
#define CURVESCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QColor>
#include <QTimer>
#include "curvedata.h"
#define QX_MIN_X_PIXEL 341
#define QX_MAX_X_PIXEL 1058
#define QX_MIN_Y_PIXEL 117
#define QX_MAX_Y_PIXEL 717

class curvescene : public QGraphicsScene
{
public:
    curvescene();
    QVector<QGraphicsTextItem*> haxisTextList;//纵轴坐标轴
    QVector<QGraphicsTextItem*> btAxisTextList;//底部时间轴
    void initback();
    void initHeightAxis();

    QColor textColor;
    QColor curveColor;

    int     zero_y_pixel;
    int     zero_x_pixel;

    void drawCurve(QList<CurvePoint> &datalist);

public slots:
    void initTimeAxis();
    void testtimetout();
};

#endif // CURVESCENE_H
