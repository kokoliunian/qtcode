#include "camthread.h"
#include <QDebug>
cv::Mat camthread::getImage()
{
    cv::Mat image;
    m_imglocker.lock();
    image = m_imgdata2;
    m_imglocker.unlock();
    return image;
}

void camthread::setCameIndex(int index)
{
    m_camindex=index;
}

void camthread::setDetRect(int x, int y, int w, int h)
{
    m_imglocker.lock();
    m_dectrect[0] = x;
    m_dectrect[1] = y;
    m_dectrect[2] = w;
    m_dectrect[3] = h;
    m_imglocker.unlock();
}

void camthread::run()
{
    QImage Img;
    cv::Mat tmppic;
    m_pvideocap=new cv::VideoCapture(m_camindex);

    if(m_pvideocap->isOpened())
    {
        qDebug()<<"open camera sucess";
    }
    else {
        qDebug()<<"open camera failed";
    }

    for (;;)
    {
         m_imglocker.lock();
        *m_pvideocap>>m_imgdata1;
         m_imgdata2=m_imgdata1;

         m_imglocker.unlock();

         if(m_imgdata1.empty())
             continue;
         cv::resize(m_imgdata1, m_imgdata1, cv::Size(m_imgdata1.cols, m_imgdata1.rows),0,0);

         cv::cvtColor(m_imgdata1, tmppic, CV_BGR2RGB);

         m_imglocker.lock();
        if (m_dectrect[2] != 0)
            rectangle(tmppic, cv::Rect(m_dectrect[0], m_dectrect[1], m_dectrect[2], m_dectrect[3]), cv::Scalar(0, 255, 0), 2);
        m_dectrect[2] = 0;
        m_imglocker.unlock();

        Img = QImage((const uchar*)(tmppic.data), tmppic.cols, tmppic.rows, tmppic.cols * tmppic.channels(), QImage::Format_RGB888);
        emit imgReady(Img);
    }
}

void camthread::setface(cv::Mat face,QString feature)
{
    m_imglocker.lock();

    m_face=face;
    m_strfeature=feature;
    m_imglocker.unlock();
}

camthread::camthread(QObject *obj)
{

}

cv::Mat camthread::getFace()
{
    cv::Mat face;
    m_imglocker.lock();
    face=m_face;
    m_imglocker.unlock();
    return face;
}

QString camthread::getFeaturstring()
{
    QString str;
    m_imglocker.lock();
    str=m_strfeature;
    m_imglocker.unlock();
    return str;

}
