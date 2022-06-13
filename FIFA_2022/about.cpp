#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
}

void About::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter.drawEllipse(190, 120, 150, 150);

    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
    painter.drawEllipse(210, 150, 20, 20);
    painter.drawEllipse(290, 150, 20, 20);
    painter.drawEllipse(230, 190, 20, 20);
    painter.drawEllipse(270, 210, 20, 20);
    painter.drawEllipse(250, 140, 20, 20);
}

About::~About()
{
    delete ui;
}

