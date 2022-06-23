#include "dialogaboutteams.h"
#include "ui_dialogaboutteams.h"

DialogAboutTeams::DialogAboutTeams(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAboutTeams)
{
    ui->setupUi(this);
}

DialogAboutTeams::~DialogAboutTeams()
{
    delete ui;
}
