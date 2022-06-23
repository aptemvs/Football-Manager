#include "info.h"
#include "ui_info.h"

Info::Info(QWidget* parent) :
        QDialog(parent),
        ui(new Ui::Info)
{
    ui->setupUi(this);
}

void Info::setData(QString name, int number)
{
    ui->textName->setText(name);
    ui->numberBox->display(number);
}

Info::~Info()
{
    delete ui;
}
