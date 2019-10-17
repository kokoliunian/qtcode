#ifndef SQLITEHELPER_H
#define SQLITEHELPER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QHostAddress>
#include <QDir>
class SQLiteHelper:public QObject
{
    Q_OBJECT
private:
    QSqlDatabase db;
    QDir    *dbDir;
public:
    SQLiteHelper();
    ~SQLiteHelper();

    void getfeaturelist();
    void addfeature(QString pic_name,QString desc_name,QString feature);

};

#endif // SQLITEHELPER_H
