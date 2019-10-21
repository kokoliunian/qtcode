#ifndef FILESAMPLE_H
#define FILESAMPLE_H

#include <QDialog>

namespace Ui {
class filesample;
}

class filesample : public QDialog
{
    Q_OBJECT

public:
    explicit filesample(QWidget *parent = nullptr);
    ~filesample();

private:
    Ui::filesample *ui;
};

#endif // FILESAMPLE_H
