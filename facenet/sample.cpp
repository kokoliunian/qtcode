#include "sample.h"
#include "ui_sample.h"
#include <QImage>
#include <QDebug>
#include "mainwindow.h"
#include <QLineEdit>

sample::sample(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sample)
{
    ui->setupUi(this);


    m_pcamthread=new camthread(0);
    connect(m_pcamthread,SIGNAL(imgReady(QImage)),this,SLOT(updaterect(QImage)));
    m_pcamthread->setCameIndex(0);
    m_pcamthread->start();

    m_pdetecthread=new detectthread(m_pcamthread);
    m_pdetecthread->start();



}

sample::~sample()
{
    delete ui;
}



void sample::keyReleaseEvent(QKeyEvent *event)
{

    qDebug()<<event->key();
    if(event->key()==Qt::Key_Return)
    {

       m_face=m_pcamthread->getFace();


       m_facefeature=m_pcamthread->getFeaturstring();


       if(!m_face.empty())
       {
         cv::imwrite("D:\\sample.jpg",m_face);
         m_image=cvMat2QImage(m_face);

         ui->label_2->setPixmap(QPixmap::fromImage(m_image.scaled(ui->label_2->size())));
         ui->label_2->show();
       }
    }

}

void sample::updaterect(QImage img)
{
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->show();

}



void sample::on_pushButton_clicked()
{
    //md5,writefile,writedb
    QString name=ui->lineEdit->text().toLocal8Bit();
    if(name.isEmpty())
        return;

    QByteArray filename=getchecksum(m_image);
    QString filepath=getimagepath()+"\\"+filename.toHex()+".jpg";
    m_image.save(filepath);

    //db

    SAMPPHOTO* p=new SAMPPHOTO;
    p->desc_name=name;
    p->picture_name=filename.toHex()+".jpg";
    p->strfeature=m_facefeature;

    mW->addonesamp(*p);
    mW->m_sqlitehelp->getfeaturelist();
    mW->getpicturelist();



   // vector<float> feature1 = m_parc->getFeature(det1);







}
