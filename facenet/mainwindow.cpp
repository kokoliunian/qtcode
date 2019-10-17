#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplashScreen>
#include <QDebug>
#include <QDateTime>
#include <QPixmap>
#include <QFont>
#include <QCryptographicHash>
#include <QImage>
#include <QBuffer>
#include <QImageReader>
MainWindow* mW=NULL;

cv::Mat ncnn2cv(ncnn::Mat img)
{
    unsigned char pix[img.h * img.w * 3];
    img.to_pixels(pix, ncnn::Mat::PIXEL_BGR);
    cv::Mat cv_img(img.h, img.w, CV_8UC3);
    for (int i = 0; i < cv_img.rows; i++)
    {
        for (int j = 0; j < cv_img.cols; j++)
        {
            cv_img.at<cv::Vec3b>(i,j)[0] = pix[3 * (i * cv_img.cols + j)];
            cv_img.at<cv::Vec3b>(i,j)[1] = pix[3 * (i * cv_img.cols + j) + 1];
            cv_img.at<cv::Vec3b>(i,j)[2] = pix[3 * (i * cv_img.cols + j) + 2];
        }
    }
    return cv_img;
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QPixmap pixmap(getsrcpath()+"\\start.jpg");
    QSplashScreen splash(pixmap);
    splash.show();
    QFont ft;
    ft.setFamily("宋体");
    ft.setPixelSize(20);
    ft.setBold(true);

    splash.setFont(ft);
    mW=this;
    splash.showMessage(QStringLiteral("正在初始化菜单，请稍后……"), Qt::AlignHCenter|Qt::AlignBottom, Qt::red);
    initmenu();
    splash.showMessage(QStringLiteral("正在加载样本资源，请稍后……"), Qt::AlignHCenter|Qt::AlignBottom, Qt::red);
    getpicturelist();
    splash.showMessage(QStringLiteral("正在加载数据库，请稍后……"), Qt::AlignHCenter|Qt::AlignBottom, Qt::red);
    inits();
    splash.showMessage(QStringLiteral("正在初始化udp服务，请稍后……"), Qt::AlignHCenter|Qt::AlignBottom, Qt::red);
    init_udpserver();

    splash.showMessage(QStringLiteral("正在初始化tcp服务，请稍后……"), Qt::AlignHCenter|Qt::AlignBottom, Qt::red);
    inittcpserver();

    m_pmtcnndectctor=new MtcnnDetector(getmodelspath().toStdString());
    m_parcface=new Arcface(getmodelspath().toStdString());



    splash.finish(this);

    showMaximized();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::inits()
{
    ui->textEdit->setReadOnly(true);

    initdb();


}

SAMPPHOTO *MainWindow::getfeaturebyindex(int index)
{
    if(index<m_featurelist.count())
        return m_featurelist[index];
    return NULL;
}

bool MainWindow::isphotoexits(QString filename)
{
    bool ret=false;
    for(int i=0;i<m_picturelist.count();i++)
    {
        if(m_picturelist[i]->picture_name==filename)
            return true;
    }

    return ret;
}

void MainWindow::getpicturelist()
{
    m_picturelist.clear();
    QDir dir(getimagepath());

    QStringList ImageList;

    ImageList << "*.jpg"<<"*.jpeg";

    dir.setNameFilters(ImageList);
    int ImageCount = dir.count();
    for (int i=0;i < ImageCount;i++)
    {
        QString ImageName  = dir[i];
        FILENAME* nf=new FILENAME;
        nf->picture_name=ImageName;
        m_picturelist.append(nf);

    }
}

void MainWindow::savefeaturelist()
{
    cv::Mat img1;


    img1 = cv::imread("F:\\code\\qtcode\\build-qtncnn-Desktop_Qt_5_13_0_MinGW_64_bit-Debug\\debug\\image\\zyc1.jpg");


    ncnn::Mat ncnn_img1 = ncnn::Mat::from_pixels(img1.data, ncnn::Mat::PIXEL_BGR, img1.cols, img1.rows);

    MtcnnDetector detector("F:\\code\\qtcode\\build-qtncnn-Desktop_Qt_5_13_0_MinGW_64_bit-Debug\\debug\\models");

    double start = (double)cv::getTickCount();
    vector<FaceInfo> results1 = detector.Detect(ncnn_img1);
    cout << "Detection Time: " << (cv::getTickCount() - start) / cv::getTickFrequency() << "s" << std::endl;

    ncnn::Mat det1 = preprocess(ncnn_img1, results1[0]);





    Arcface arc("F:\\code\\qtcode\\build-qtncnn-Desktop_Qt_5_13_0_MinGW_64_bit-Debug\\debug\\models");

    start = (double)cv::getTickCount();
    vector<float> feature1 = arc.getFeature(det1);
    cout << "Extraction Time: " << (cv::getTickCount() - start) / cv::getTickFrequency() << "s" << std::endl;


    for(int i=0;i<m_featurelist.count();i++)
    {
        std::cout << "Similarity: " << calcSimilar(feature1, m_featurelist[i]->feature) << std::endl;;
    }


}

void MainWindow::addonesamp(SAMPPHOTO p)
{
    m_sqlitehelp->addfeature(p.picture_name,p.desc_name,p.strfeature);
}

void MainWindow::initdb()
{
    m_sqlitehelp=new SQLiteHelper;
}

void MainWindow::init_udpserver()
{
    addlog("init udp server");
    m_psocket=new QUdpSocket;

    m_psocket->bind(QHostAddress::AnyIPv4,UDP_SERVER_PORT);


    connect(m_psocket,SIGNAL(readyRead()),this,SLOT(readudp()));

}

void MainWindow::processudpmsg(QByteArray ba,bool *result)
{

    *result=true;

}

void MainWindow::inittcpserver()
{
    m_ptcpsrv=new QTcpServer;

    if(m_ptcpsrv->listen(QHostAddress::Any,TCP_SERVER_PORT))
    {
        addlog("tcp server listening");
        connect(m_ptcpsrv,SIGNAL(newConnection()),this,SLOT(onServerNewConnection()));

    }
    else
    {
        addlog("tcp server error!");
    }


}

void MainWindow::addlog(QString str)
{
#ifdef USE_LOG
    ui->textEdit->append(QDateTime::currentDateTime().toString("[yyyy/MM/dd hh:mm:ss] ")+str);
#endif
}



QByteArray MainWindow::getchecksum(cv::Mat mat)
{
    QByteArray ba;
    int size=mat.total()*mat.elemSize();
    ba.resize(size);

    memcpy(ba.data(),mat.data,size*sizeof(BYTE));

    return QCryptographicHash::hash(ba,QCryptographicHash::Md5);

}

QString MainWindow::savesamp(cv::Mat mat)
{
    QByteArray ba;
    ba=getchecksum(mat);
    QString filename,fullpath;
    filename=ba.toHex()+".jpg";
    addlog("filename="+filename);
    fullpath=getimagepath()+"\\"+filename;
    cv::imwrite(fullpath.toStdString(), mat);
    return filename;
}

recognizeresult MainWindow::dectedface(QByteArray ba)
{
    recognizeresult result;

    result.name="";
    result.similar=-1;
    result.result=false;

    QBuffer buff(&ba);
    buff.open(QIODevice::ReadOnly);
    QImageReader reader(&buff,"JPG");
    QImage img = reader.read();

    ui->label_2->setPixmap(QPixmap::fromImage(img));
    ui->label_2->show();


    //img.save("d:\\test.jpg");

    cv::Mat img1=QImage2cvMat(img);


    ncnn::Mat ncnn_img1 = ncnn::Mat::from_pixels(img1.data, ncnn::Mat::PIXEL_BGR, img1.cols, img1.rows);
    QString mdpath=getmodelspath();

    MtcnnDetector detector(mdpath.toStdString());

    vector<FaceInfo> results1 = m_pmtcnndectctor->Detect(ncnn_img1);
    if(results1.size()>0)
    {
        ncnn::Mat det1 = preprocess(ncnn_img1, results1[0]);

        vector<float> feature1 = m_parcface->getFeature(det1);

        float similar=-1;
        int index=-1;

        for(int i=0;i<m_featurelist.count();i++)
        {
            float temp=calcSimilar(m_featurelist[i]->feature,feature1);

            if(temp>similar)
            {
                similar=temp;
                index=i;
            }
        }

        if(similar>SIMILAR_LEVEL)
        {

            ui->label_similar->setText("相似度:"+QString::number(similar));
            SAMPPHOTO* p=getfeaturebyindex(index);
            if(p!=NULL)
            {
                ui->label_result->setText(QString(p->desc_name));

                if(isphotoexits(p->picture_name))
                {
                    QString path=getimagepath()+"\\"+p->picture_name;
                    QImage face(path);

                    ui->label_ori->setPixmap(QPixmap::fromImage(face));
                    ui->label_ori->show();
                }
            }
            result.similar=similar;
            result.result=true;
            result.name=p->desc_name;
            return result;
        }
        else
        {
             ui->label_result->setText("识别结果:未知");
             ui->label_similar->setText("相似度:"+QString::number(similar));
             QString path=getsrcpath()+"\\unknow.jpg";
             QImage face(path);

             ui->label_ori->setPixmap(QPixmap::fromImage(face));
             ui->label_ori->show();

             result.similar=similar;
             result.result=false;
             result.name=QString("未知");
             return result;
        }

    }
    return result;
}

QImage MainWindow::dectedface(QImage img)
{
    QImage im;
    cv::Mat img1=QImage2cvMat(img);
    ncnn::Mat ncnn_img1 = ncnn::Mat::from_pixels(img1.data, ncnn::Mat::PIXEL_BGR, img1.cols, img1.rows);
    QString mdpath=getmodelspath();
    MtcnnDetector detector(mdpath.toStdString());

    double start = (double)cv::getTickCount();
    vector<FaceInfo> results1 = detector.Detect(ncnn_img1);
    if(results1.size()>0)
    {
        ncnn::Mat det1 = preprocess(ncnn_img1, results1[0]);
        Arcface arc(mdpath.toStdString());
        vector<float> feature1 = arc.getFeature(det1);
    }
    return im;
}




void MainWindow::initmenu()
{
    m_pmainM=ui->menuBar->addMenu(tr("菜单"));

    m_pactadd=m_pmainM->addAction(tr("样本采集"));

    connect(m_pactadd,SIGNAL(triggered()),this,SLOT(on_action_addsample()));
}



void MainWindow::readudp()
{
    addlog("recived udp msg");
    QByteArray datagram;
    QHostAddress ip;
    QString recvText;
    bool result;
    while (m_psocket->hasPendingDatagrams())
    {
        datagram.resize(m_psocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        m_psocket->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
        //processTheDatagram(datagram);
        recvText="Peer ip: "+sender.toString()+" port: "+QString::number(senderPort);
        addlog(recvText);
        processudpmsg(datagram,&result);

        if(result)
        {
            QJsonObject rectJson;
            rectJson.insert("company","yisuwangluo");
            rectJson.insert("Answer","join please!");
            //rectJson.insert("tcpserverip",m_psocket->multicastInterface());
            rectJson.insert("tcpserverport",TCP_SERVER_PORT);
            QJsonDocument rectJsonDoc;
            rectJsonDoc.setObject(rectJson);
            QByteArray byteArray = rectJsonDoc.toJson(QJsonDocument::Compact);

            m_psocket->writeDatagram(byteArray,sender,senderPort);

        }
    }
}

void MainWindow::onServerNewConnection()
{
    addlog("new tcp client connection");
    QTcpSocket* tcp = m_ptcpsrv->nextPendingConnection();     //获取新的客户端信息
    clientsession* news=new clientsession;
    news->m_clientskt=tcp;
    QHostAddress address6=news->m_clientskt->peerAddress();
    bool ok=false;

    QHostAddress address4(address6.toIPv4Address(&ok));

    QString info=QString("%1").arg(news->m_clientskt->peerPort());
    addlog("client info:"+info);

    news->m_clientskt->setObjectName(info);       //设置名称,方便查找
    connect(news->m_clientskt, SIGNAL(connected()), news, SLOT(onServerConnected()));
    connect(news->m_clientskt, SIGNAL(disconnected()), news, SLOT(onServerDisconnected()));
    connect(news->m_clientskt, SIGNAL(readyRead()), news, SLOT(onServerDataReady()));
    connect(news->m_clientskt, SIGNAL(bytesWritten(qint64)), news, SLOT(onServerBytesWritten(qint64)));

    m_pClientsocketlst.append(tcp);
}

void MainWindow::on_action_addsample()
{
    m_psmpdlg =new sample;
    m_psmpdlg->show();
}

void MainWindow::on_pushButton_clicked()
{
    savefeaturelist();

}
