#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QObject>
#include <QWidget>

class titlebar : public QWidget
{
    Q_OBJECT
public:
    explicit titlebar(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // TITLEBAR_H
