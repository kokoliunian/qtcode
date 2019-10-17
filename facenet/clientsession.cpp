#include "clientsession.h"
#include "mainwindow.h"
#include <QPixmap>
#include <QDateTime>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QImage>
clientsession::clientsession(QObject *parent) : QObject(parent)
{
    m_clientskt=new QTcpSocket;
}


void clientsession::onServerConnected()
{

}

void clientsession::onServerDisconnected()
{
    mW->addlog("disconnected");

    deleteLater();
    /*
    QByteArray ba=m_imgArray.fromBase64(m_imgArray);
    if(ba.count()>2)
    {
        if((ba[0]=0xFF)&&(ba[1]=0xD8))
        {
            mW->addlog("new image saved!");

            QString str=QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz")+".jpg";

            QString filepath=getuploadspath()+"\\"+str;

            QFile file(filepath);
            file.open(QFile::ReadWrite);
            file.write(ba.data(),ba.size());
            file.flush();
            file.close();




        }

    }*/



}

void clientsession::onServerDataReady()
{

    QByteArray ba=m_clientskt->readAll();
    m_imgArray.append(ba);

    if(m_imgArray.count()==0)
        return;

    if(m_imgArray[0]!='{')
    {
        int index=m_imgArray.indexOf('{');

        if(index<0)
            m_imgArray.clear();
        else
            m_imgArray.remove(0,index-1);
    }
    int count=m_imgArray.count();

    int startcnt=m_imgArray.count('{');
    int endcnt=m_imgArray.count('}');

    if(startcnt>endcnt)
    {
        return;
    }
    else if(startcnt<endcnt)
    {
        m_imgArray.clear();
        return;
    }
    else
    {
        qDebug()<<"len: "<<m_imgArray.count();
      //  qDebug()<<m_imgArray;
        QJsonParseError parseError;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(m_imgArray,&parseError));
        if(parseError.error==QJsonParseError::NoError)
        {
            mW->addlog("收到正确的json帧");
           // qDebug()<<"json:"<<m_imgArray;

            if(jsonDoc.isObject())
            {
                QJsonObject obj=jsonDoc.object();
                if(obj.contains("IMGDATA"))
                {
                    QJsonValue name_value=obj.take("IMGDATA");
                    qDebug()<<"IMGDATA";
                    QByteArray ba=name_value.toString().toLocal8Bit();
                    //qDebug()<<ba;
                    QByteArray baa=ba.fromBase64(ba);

                    //QImage img(baa);
                   // mW->QImage2cvMat(img);
                    recognizeresult ret=mW->dectedface(baa);

                    QJsonObject rectJson;
                    rectJson.insert("company","yisuwangluo");
                    if(ret.result)
                        rectJson.insert("Recognition","true");
                    else
                        rectJson.insert("Recognition","false");

                    rectJson.insert("similar",ret.similar);
                    rectJson.insert("name",ret.name);
                    QJsonDocument rectJsonDoc;
                    rectJsonDoc.setObject(rectJson);
                    QByteArray byteArray = rectJsonDoc.toJson(QJsonDocument::Compact);

                    m_clientskt->write(byteArray);

                   // m_psocket->writeDatagram(byteArray,sender,senderPort);


/*
                    QString str=QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz")+".jpg";

                    QString filepath=getuploadspath()+"\\"+str;

                    QFile file(filepath);
                    file.open(QFile::ReadWrite);
                    file.write(baa.data(),baa.size());
                    file.flush();
                    file.close();
                    */
                    //图片读取,分析，对比，给识别结果



                }
            }



            m_imgArray.clear();
        }
        else
        {
            m_imgArray.clear();
        }


    }










}

void clientsession::onServerBytesWritten(qint64 bytes)
{

}
