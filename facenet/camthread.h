#ifndef CAMTHREAD_H
#define CAMTHREAD_H

#include <QObject>
#include <QThread>
#include <QImage>
#include <QMutex>
//#include <opencv2/core/core.hpp>
#include "opencv2/opencv.hpp"
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/imgproc/imgproc_c.h"
//#include "opencv2/videoio/videoio_c.h"

#include <vector>
#include "base.h"
using namespace std;
class camthread : public QThread
{
    Q_OBJECT
public:

    cv::Mat getImage();
    void setCameIndex(int index);
    void setDetRect(int x, int y , int w , int h);
    void run();
    void setface(cv::Mat face,QString feature);
    camthread(QObject *obj);
    cv::Mat getFace();
    QString getFeaturstring();
signals:
    void imgReady(QImage img);
private:
    int m_camindex;
    cv::VideoCapture* m_pvideocap;
    QMutex m_imglocker;
    cv::Mat m_imgdata1;
    cv::Mat m_imgdata2;

    cv::Mat m_face;
    QString m_strfeature;

    int m_dectrect[4];

};

#endif // CAMTHREAD_H
