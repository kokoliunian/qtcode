#ifndef CURVEDATA_H
#define CURVEDATA_H

struct CurvePoint
{
    float height;
    int offsettime;
    char  type;//0x01正常,0x02报警
    CurvePoint()
    {
        height=0.0;
        offsettime=0;
        type=0x01;
    }
    CurvePoint(float height,int offsettime,char state)
    {
        this->height=height;
        this->offsettime=offsettime;
        this->type=state;
    }
    CurvePoint  &operator= (const CurvePoint &item)
    {
        this->height=item.height;
        this->offsettime=item.offsettime;
        this->type=item.type;
        return *this;
    }

};
#include <QList>
class curvedata
{
public:
    curvedata();
    QList<CurvePoint> heightList;


};

#endif // CURVEDATA_H
