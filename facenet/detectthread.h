#ifndef DETECTTHREAD_H
#define DETECTTHREAD_H

#include <QObject>
#include "camthread.h"
#include "mtcnn.h"
#include "arcface.h"
class detectthread : public QThread
{
public:
    detectthread(camthread *camtrd);
    void run();
    camthread* m_pcamt;
    MtcnnDetector* m_pmtcnn;
    Arcface* m_parc;
    QString m_strfeature;
};

#endif // DETECTTHREAD_H
