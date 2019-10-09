#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "curvescene.h"
#include <QTimer>
#include <QPainterPath>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    curvescene* m_prealscene;

    int height,width;
    void initview();
    void initAxis();

    QTimer* testtimer;
public slots:
    void testtimeout();
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
