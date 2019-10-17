#ifndef CLIENTSESSION_H
#define CLIENTSESSION_H

#include <QObject>
#include <QTcpSocket>
#include "global.h"
#include "ncnn/net.h"
class clientsession : public QObject
{
    Q_OBJECT
public:
    explicit clientsession(QObject *parent = nullptr);

    QTcpSocket *m_clientskt;
    QByteArray m_imgArray;



public slots:
    void onServerConnected();
    void onServerDisconnected();
    void onServerDataReady();
    void onServerBytesWritten(qint64 bytes);
signals:

public slots:
};

#endif // CLIENTSESSION_H
