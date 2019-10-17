#ifndef SAMPLE_H
#define SAMPLE_H

#include <QDialog>
#include <opencv2/core/core.hpp>
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/videoio/videoio_c.h"
#include <QTimer>
#include <QKeyEvent>
#include <QImage>
#include "camthread.h"
#include "detectthread.h"
#include "ncnn/net.h"
#include "arcface.h"
namespace Ui {
class sample;
}

class sample : public QDialog
{
    Q_OBJECT

public:
    explicit sample(QWidget *parent = nullptr);
    ~sample();

    detectthread* m_pdetecthread;
    camthread* m_pcamthread;
    void keyReleaseEvent(QKeyEvent *event);




public slots:
    void updaterect(QImage img);
private slots:
    void on_pushButton_clicked();

private:
    Ui::sample *ui;
    cv::Mat m_face;
    QImage m_image;
    QString m_facefeature;
};

#endif // SAMPLE_H
