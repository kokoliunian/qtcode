#include "sqlitehelper.h"
#include <mainwindow.h>
#include <QSqlQuery>
#include <QStringList>
SQLiteHelper::SQLiteHelper()
{
     dbDir = new QDir;

    if(!dbDir->exists(getdbpath()))
    {
        dbDir->mkdir(getdbpath());
        mW->addlog("mkdir: "+getdbpath());
    }
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(getdbnamepath());

    if(db.open())
    {
        mW->addlog("db open success:!");
        getfeaturelist();
    }
}

SQLiteHelper::~SQLiteHelper()
{
    delete dbDir;
}

void SQLiteHelper::getfeaturelist()
{
    mW->m_featurelist.clear();
    QString str="create table if not exists feature(pic_name CHAR(64),desc_name CHAR(64),feature VARCHAR(2048))";
    QSqlQuery query;
    query.exec(str);
    str="select * from feature";
    query.exec(str);
    while(query.next())
    {
        SAMPPHOTO* ns=new SAMPPHOTO;
        QString temp;
        ns->picture_name=query.value(0).toString();
        ns->desc_name=query.value(1).toString();
        temp=query.value(2).toString();
        QStringList list=temp.split(",");
        for(int i=0;i<list.count()-1;i++)
        {
            ns->feature.push_back(list[i].toFloat());
        }

        mW->m_featurelist.append(ns);


       // mainWindow->setZHZMAC(query.value(1).toString());
      //  mainWindow->zhzInofList.insert(query.value(1).toULongLong(),query.value(0).toString());
    }
}

void SQLiteHelper::addfeature(QString pic_name, QString desc_name, QString feature)
{
    QString str=QObject::tr("INSERT INTO feature (pic_name,desc_name,feature)VALUES('%1','%2','%3')").arg(pic_name).arg(desc_name).arg(feature);

    QSqlQuery query;
    query.exec(str);
}
