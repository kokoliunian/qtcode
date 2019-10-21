#include "samplemanage.h"
#include "ui_samplemanage.h"

samplemanage::samplemanage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::samplemanage)
{
    ui->setupUi(this);
}

samplemanage::~samplemanage()
{
    delete ui;
}
