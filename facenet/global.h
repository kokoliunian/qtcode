#ifndef GLOBAL_H
#define GLOBAL_H
#include <QString>
#include <vector>
#include <QDir>
#include <QCoreApplication>
#include <opencv2/core/core.hpp>
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/videoio/videoio_c.h"
#include <QImage>
#include <QByteArray>
#include <QCryptographicHash>
#include <QDataStream>
#define UDP_SERVER_PORT 8888
#define TCP_SERVER_PORT 9999
#define SIMILAR_LEVEL  0.6
#define USE_LOG
using namespace std;
typedef struct tagrecognizeresult
{
    QString name;
    float similar;
    bool result;
}recognizeresult;
typedef struct tagSAMPPHOTO
{
    QString desc_name;
    QString picture_name;
    vector<float> feature;
    QString strfeature;

}SAMPPHOTO;
typedef struct tagFILENAME
{
    QString picture_name;
}FILENAME;
static QString getexepath()
{
    return QCoreApplication::applicationDirPath();
}
static QString getdbpath()
{
    return getexepath()+"\\db";
}
static QString getdbnamepath()
{
    return getdbpath()+"\\facenet.db";
}
static QString getimagepath()
{
    return getexepath()+"\\image";
}
static QString getlogpath()
{
    return getexepath()+"\\log";
}
static QString getmodelspath()
{
    return getexepath()+"\\models";
}
static QString getsrcpath()
{
    return getexepath()+"\\src";
}
static QString getuploadspath()
{
    return getexepath()+"\\imageupload";
}

static QImage cvMat2QImage(const cv::Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {

        return QImage();
    }
}

static QByteArray getchecksum(cv::Mat mat)
{
    QByteArray ba;
    int size=mat.total()*mat.elemSize();
    ba.resize(size);

    memcpy(ba.data(),mat.data,size*sizeof(char));

    return QCryptographicHash::hash(ba,QCryptographicHash::Md5);

}
static QByteArray getchecksum(QImage img)
{
    QByteArray ba;
    QDataStream ds(&ba,QIODevice::WriteOnly);
    ds<<img;
    // int size=img
    // ba.resize(size);

    // memcpy(ba.data(),mat.data,size*sizeof(char));
    return QCryptographicHash::hash(ba,QCryptographicHash::Md5);

}
static cv::Mat QImage2cvMat(const QImage &image)
{
    switch(image.format())
    {
    // 8-bit, 4 channel
    case QImage::Format_ARGB32:
        break;
    case QImage::Format_ARGB32_Premultiplied:
    {
        cv::Mat mat(image.height(), image.width(),
                    CV_8UC4,
                    (void*)image.constBits(),
                    image.bytesPerLine());
        return mat.clone();
    }

        // 8-bit, 3 channel
    case QImage::Format_RGB32:
    {
        cv::Mat mat(image.height(),image.width(),
                    CV_8UC4,
                    (void*)image.constBits(),
                    image.bytesPerLine());

        // drop the all-white alpha channel
        cv::cvtColor(mat, mat, cv::COLOR_BGRA2BGR);
        return mat.clone();
    }
    case QImage::Format_RGB888:
    {
        QImage swapped = image.rgbSwapped();
        cv::Mat mat(swapped.height(), swapped.width(),
                    CV_8UC3,
                    (void*)image.constBits(),
                    image.bytesPerLine());
        return mat.clone();
    }

        // 8-bit, 1 channel
    case QImage::Format_Indexed8:
    {
        cv::Mat mat(image.height(),image.width(),
                    CV_8UC1,
                    (void*)image.constBits(),
                    image.bytesPerLine());
        return mat.clone();
    }

        // wrong
    default:
        break;
    }
    return cv::Mat();

}
#endif // GLOBAL_H
