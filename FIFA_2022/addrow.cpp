#include "addrow.h"
#include "ui_addrow.h"

addRow::addRow(QWidget* parent) :
        QDialog(parent),
        ui(new Ui::addRow)
{
    ui->setupUi(this);

    QObject::connect(ui->ButtonCancel, SIGNAL(clicked()), this, SLOT(reject()));
    QObject::connect(ui->ButtonOK, SIGNAL(clicked()), this, SLOT(saveAddedRow()));
}

void addRow::saveAddedRow()
{
    newRow.push_back("");
    newRow.push_back(ui->lineName->text());
    newRow.push_back("");
    newRow.push_back(ui->spinBoxOverall->value());
    newRow.push_back(ui->spinBoxAge->value());
    newRow.push_back(ui->spinBoxDate->text());
    newRow.push_back(ui->spinBoxHeight->value());
    newRow.push_back("");
    newRow.push_back("");
    newRow.push_back("");
    newRow.push_back(ui->lineClubName->text());

    if (ui->lineName->text() == "")
    {
        QMessageBox::warning(this, "Warning", "Name is empty");
        newRow.clear();
    } else if (ui->lineClubName->text() == "")
    {
        newRow.clear();
        QMessageBox::warning(this, "Warning", "Club name is empty");
    } else
    {
        accept();
    }
}

const QList <QVariant>& addRow::getNewRow()
{
    return newRow;
}

addRow::~addRow()
{
    delete ui;
}
