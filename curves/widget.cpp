#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <time.h>

#define VIEW_HEIGHT 886
#define VIEW_WIDTH  553
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    resize(1024,768);
    setFixedSize(1024,768);
    initview();

    testtimer = new QTimer;
    connect(testtimer,SIGNAL(timeout()),this,SLOT(testtimeout()));
    testtimer->start(1000);
    qsrand(time(NULL));


}

Widget::~Widget()
{
    delete ui;
}

void Widget::initview()
{
    qDebug()<<"1111111111111";


    qDebug()<<"22222222";
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->resize(VIEW_HEIGHT, VIEW_WIDTH);
    width=ui->graphicsView->width();
    height=ui->graphicsView->height();


    m_prealscene=new curvescene();
    m_prealscene->setSceneRect(-2/width,-height/2,width,height);

    ui->graphicsView->setScene(m_prealscene);
    ui->graphicsView->update();

    m_prealscene->update();
    qDebug()<<"width="<<width<<",height="<<height;
//    m_prealscene->addLine(0,0,100,-200,QPen(Qt::DotLine));
}

void Widget::initAxis()
{


}

void Widget::testtimeout()
{

    int n = qrand() % 100;


    /*
    int n = qrand() % 100;
    //int pos=m_prealscene->m_pcurvedata->m_painterpath[0].length()
    int xpos=m_prealscene->m_pcurvedata->x_pos;
    qDebug()<<"xpos=="<<xpos;

   // m_prealscene->m_pcurvedata->m_painterpath[0].lineTo(n,xpos);

    qDebug()<<n;
    m_prealscene->clear();

    if(m_prealscene->m_pcurvedata->m_painterpath==0)
    {
        qDebug()<<"init";
        m_prealscene->m_pcurvedata->m_painterpath=new QPainterPath;
        m_prealscene->m_pcurvedata->m_painterpath->moveTo(xpos,n);
    }
    else
    {
        qDebug()<<"add";
        m_prealscene->m_pcurvedata->m_painterpath->lineTo(xpos,n);
    }

    qDebug()<<"set path";
    m_prealscene->m_pcurvedata->m_pathItem->setPath(*(m_prealscene->m_pcurvedata->m_painterpath));
    qDebug()<<"add item to scene";
    m_prealscene->addItem(m_prealscene->m_pcurvedata->m_pathItem);
    //m_prealscene->update();
    m_prealscene->m_pcurvedata->x_pos+=X_SETP;
    */

}
