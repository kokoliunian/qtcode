#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostAddress>
#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include "global.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QVector>
#include "sqlitehelper.h"
#include "mtcnn.h"
#include <opencv2/core/core.hpp>
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/videoio/videoio_c.h"
#include "ncnn/net.h"
#include "arcface.h"
#include "clientsession.h"
#include <QMenu>
#include <QAction>
#include "sample.h"
//using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void inits();

    QVector<SAMPPHOTO*> m_featurelist;
    QVector<FILENAME*>  m_picturelist;
    SAMPPHOTO* getfeaturebyindex(int index);
    bool isphotoexits(QString filename);
    void getpicturelist();


    SQLiteHelper *m_sqlitehelp;
    void initdb();
    void savefeaturelist();
    void addonesamp(SAMPPHOTO p);

    QUdpSocket *m_psocket; /*udp服务socket，用于客户端的自动上线*/
    QVector<QTcpSocket*> m_pClientsocketlst;

    void init_udpserver();
    void processudpmsg(QByteArray ba,bool *result);


    QTcpServer* m_ptcpsrv;
    void inittcpserver();


    void addlog(QString str);


    QByteArray getchecksum(cv::Mat mat);
    QString savesamp(cv::Mat mat);

    recognizeresult dectedface(QByteArray ba);
    QImage dectedface(QImage img);
    MtcnnDetector* m_pmtcnndectctor;
    Arcface* m_parcface;

    void initmenu();
    QMenu *m_pmainM;
    QAction *m_pactadd;

    sample* m_psmpdlg;

public slots:
    void readudp();
    void onServerNewConnection();
    void on_action_addsample();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
extern MainWindow* mW;
#endif // MAINWINDOW_H
