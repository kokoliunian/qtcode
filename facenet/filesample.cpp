#include "filesample.h"
#include "ui_filesample.h"

filesample::filesample(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filesample)
{
    ui->setupUi(this);
}

filesample::~filesample()
{
    delete ui;
}
