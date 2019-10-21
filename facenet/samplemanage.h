#ifndef SAMPLEMANAGE_H
#define SAMPLEMANAGE_H

#include <QDialog>

namespace Ui {
class samplemanage;
}

class samplemanage : public QDialog
{
    Q_OBJECT

public:
    explicit samplemanage(QWidget *parent = nullptr);
    ~samplemanage();

private:
    Ui::samplemanage *ui;
};

#endif // SAMPLEMANAGE_H
